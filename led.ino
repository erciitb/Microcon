#include "thingProperties.h"

// Define the onboard LED pin
#define LED_PIN 2

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);
  delay(1500); // Allow time for the Serial Monitor to connect

  // Set the onboard LED pin as output
  pinMode(LED_PIN, OUTPUT);

  // Initialize properties defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  // Debug info for connection status
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  // Update the IoT Cloud connection
  ArduinoCloud.update();
}

// This function is called whenever the `led` variable changes in the IoT Cloud
void onLedChange() {
  // Update the LED state
  digitalWrite(LED_PIN, led ? HIGH : LOW);

  // Print debug info to the Serial Monitor
  Serial.print("LED State changed to: ");
  Serial.println(led ? "ON" : "OFF");
}
