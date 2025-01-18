#include "CloudSpeechClient.h"
#include "network_param.h"
#include <base64.h>
#include <ArduinoJson.h>
CloudSpeechClient::CloudSpeechClient(Authentication authentication) 
{
  this->authentication = authentication;
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(1000);
  client.setCACert(root_ca);
  client.setInsecure();
  if (!client.connect(server, 443)) Serial.println("Connection failed!");
}

String ans;

CloudSpeechClient::~CloudSpeechClient() {
  client.stop();
  WiFi.disconnect();
}

void CloudSpeechClient::PrintHttpBody2(Audio* audio)
{
  String enc = base64::encode(audio->paddedHeader, sizeof(audio->paddedHeader));
  enc.replace("\n", "");  // delete last "\n"
  client.print(enc);      // HttpBody2
  char** wavData = audio->wavData;
  for (int j = 0; j < audio->wavDataSize / audio->dividedWavDataSize; ++j) {
    enc = base64::encode((byte*)wavData[j], audio->dividedWavDataSize);
    enc.replace("\n", "");// delete last "\n"
    client.print(enc);    // HttpBody2
  }
}

void CloudSpeechClient::Transcribe(Audio* audio) {
  String HttpBody1 = "{\"config\":{\"encoding\":\"LINEAR16\",\"sampleRateHertz\":16000,\"languageCode\":\"en-IN\"},\"audio\":{\"content\":\"";
  String HttpBody3 = "\"}}\r\n\r\n";
  int httpBody2Length = (audio->wavDataSize + sizeof(audio->paddedHeader)) * 4 / 3; // 4/3 is from base64 encoding
  String ContentLength = String(HttpBody1.length() + httpBody2Length + HttpBody3.length());
  String HttpHeader;

  HttpHeader = String("POST /v1/speech:recognize?key=") + ApiKey
               + String(" HTTP/1.1\r\nHost: speech.googleapis.com\r\nContent-Type: application/json\r\nContent-Length: ") + ContentLength + String("\r\n\r\n");

  // Send the HTTP request
  client.print(HttpHeader);
  client.print(HttpBody1);
  PrintHttpBody2(audio);
  client.print(HttpBody3);

  // Read the HTTP response
  String My_Answer = "";
  while (!client.available());  // Wait for the response
  while (client.available()) {
    My_Answer += (char)client.read();
  }

  Serial.print("My Answer: ");
  Serial.println(My_Answer);

  // Extract the JSON part of the response
  int position = My_Answer.indexOf('{'); // Find the start of the JSON data
  ans = My_Answer.substring(position);  // Store the JSON response

  // Parse the JSON to extract the transcription
  StaticJsonDocument<1024> doc;  // Adjust size as needed for large responses
  DeserializationError error = deserializeJson(doc, ans);
  if (error) {
    Serial.print("JSON Parsing failed: ");
    Serial.println(error.c_str());
    return;  // Stop if parsing failed
  }

  // Extract the transcript from the JSON response
  const char* transcript = doc["results"][0]["alternatives"][0]["transcript"];
  if (transcript) {
    ans = String(transcript);  // Store the extracted transcript
  } else {
    ans = "No transcription found.";  // Handle cases where no transcription is available
  }

  Serial.print("Transcription: ");
  Serial.println(ans);
}
