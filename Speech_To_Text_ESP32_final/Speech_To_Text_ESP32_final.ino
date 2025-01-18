#include "Audio.h"               // Include audio processing library
#include "CloudSpeechClient.h"   // Include the speech-to-text client library

// Define the Serial port for UART communication
#define UART_TX_PIN 17  // Transmit (TX) pin for UART communication
#define UART_RX_PIN 16  // Receive (RX) pin for UART communication

// Declare pointers for Audio and CloudSpeechClient objects
Audio* audio = nullptr;  
CloudSpeechClient* cloudSpeechClient = nullptr;

void setup() {
  // Initialize the primary Serial port for debugging
  Serial.begin(115200);
  delay(500);
  Serial.println("\r\nSpeech-to-Text ESP32 Project Starting...\r\n");

  // Initialize the secondary Serial port for UART communication
  Serial2.begin(9600, SERIAL_8N1, UART_RX_PIN, UART_TX_PIN);  // Baud rate: 9600, 8 data bits, no parity, 1 stop bit
  Serial.println("UART initialized for communication with another ESP32.");

  // Initialize the audio object with the chosen audio module
  audio = new Audio(ICS43434);  // Example: Using the ICS43434 microphone
  // audio = new Audio(M5STACKFIRE);  // Uncomment if using the M5Stack FIRE microphone

  // Record audio
  Serial.println("Recording audio...");
  audio->Record();
  Serial.println("Recording completed. Now processing...");

  // Initialize the CloudSpeechClient object with an API key
  cloudSpeechClient = new CloudSpeechClient(USE_APIKEY);

  // Perform transcription
  Serial.println("Transcribing audio...");
  cloudSpeechClient->Transcribe(audio);

  // Get the transcription result using the getter method
  String transcribedText = cloudSpeechClient->getTranscription();

  // Print the transcribed text to the Serial monitor
  Serial.println("Transcription Result: " + transcribedText);

  // Send the transcribed text to the other ESP32 via UART
  if (Serial2) {  // Ensure UART is ready
    Serial2.println(transcribedText);  // Send the transcription as a line
    Serial.println("Transcription sent via UART.");
  } else {
    Serial.println("Error: UART communication not initialized.");
  }

  // Clean up and delete objects to free memory
  delete cloudSpeechClient;
  delete audio;
  Serial.println("Program completed.");
}

void loop() {
  // The loop function is intentionally left empty
}
