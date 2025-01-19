#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "Audio.h"

// Wi-Fi credentials
const char* ssid = "Sk";
const char* password = "12345678.";

// Gemini API key and parameters
const char* Gemini_Token = "YOUR_API_KEY";
const char* Gemini_Max_Tokens = "100";

// I2S pin configuration
#define I2S_DOUT 25
#define I2S_BCLK 27
#define I2S_LRC  26

Audio audio; // Audio object
String userQuestion = "";

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Initialize audio
  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(100); // Set volume to maximum
}

void loop() {
  Serial.println("\nAsk your Question: ");
  
  // Get user input from Serial Monitor
  while (!Serial.available());
  while (Serial.available()) {
    char add = Serial.read();
    userQuestion += add;
    delay(1);
  }

  userQuestion.trim(); // Remove extra spaces or newline characters

  if (userQuestion.isEmpty()) {
    Serial.println("No question entered.");
    return;
  }

  Serial.println("\nAsking Your Question: " + userQuestion);

  HTTPClient https;

  // Construct the request URL
  String url = String("https://generativelanguage.googleapis.com/v1beta/models/gemini-1.5-flash:generateContent?key=") + Gemini_Token;

  if (https.begin(url)) {  // Initialize connection
    https.addHeader("Content-Type", "application/json");

    // Construct the JSON payload
    String payload = String("{\"contents\": [{\"parts\":[{\"text\":\"") + userQuestion + "\"}]}],\"generationConfig\": {\"maxOutputTokens\": " + Gemini_Max_Tokens + "}}";

    int httpCode = https.POST(payload); // Send POST request

    if (httpCode == HTTP_CODE_OK) {
      String response = https.getString();

      // Parse the JSON response
      DynamicJsonDocument doc(2048);
      deserializeJson(doc, response);

      // Extract the answer
      String Answer = doc["candidates"][0]["content"]["parts"][0]["text"];
      Answer.trim();

      // Limit answer to 500 characters for TTS compatibility
      if (Answer.length() > 500) {
        Answer = Answer.substring(0, 500);
      }

      Serial.println("\nHere is your Answer: ");
      Serial.println(Answer);

      // Play the answer as audio
      audio.connecttospeech(Answer.c_str(), "en");

      // Ensure audio playback completes
      while (audio.isRunning()) {
        audio.loop();
      }
    } else {
      Serial.printf("[HTTPS] Request failed, error: %s\n", https.errorToString(httpCode).c_str());
    }

    https.end(); // Close connection
  } else {
    Serial.println("[HTTPS] Unable to connect");
  }

  userQuestion = ""; // Reset the user question
}
