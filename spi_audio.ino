#include <ArduinoJson.h>

void setup() {
  // Start the serial communication at 9600 baud rate
  Serial.begin(9600); // usb
  Serial1.begin(9600); // usb serial wire from C#
  while (!Serial) {
    ; // Wait for serial port to connect. Needed for native USB
  }

  Serial.println("Arduino Mega 2560 JSON receiver ready!");
}

void loop() {
  // Check if there's data available on the serial port
  if (Serial1.available()) {
    // Read the incoming data into a String
    String jsonString = Serial1.readStringUntil('\n');

    // Parse the JSON data using DynamicJsonDocument
    DynamicJsonDocument jsonDoc(1024);
    DeserializationError error = deserializeJson(jsonDoc, jsonString);

    // Check if the JSON data was parsed successfully
    if (error) {
      Serial.print(F("Failed to parse JSON: "));
      Serial.println(error.f_str());
      return;
    }

    // Print the received JSON to the console
    Serial.println("Received JSON:");
    serializeJsonPretty(jsonDoc, Serial);
    Serial.println();
  }
}
