#include <ESPComm.h>

// Use Serial or SoftwareSerial depending on your setup
ESPComm esp(Serial);

void handleCommand(String key, String value) {
  if (key == "level") {
    int val = value.toInt();
    Serial.print("Received level: ");
    Serial.println(val);
  } else if (key == "gas") {
    int val = value.toInt();
    Serial.print("Received gas: ");
    Serial.println(val);
  }
}

void setup() {
  Serial.begin(9600);
  esp.onCommand(handleCommand);
}

void loop() {
  esp.loop();

  // Example: send random data
  static unsigned long lastSend = 0;
  if (millis() - lastSend > 2000) {
    esp.send("level", random(0, 100));
    esp.send("gas", random(0, 100));
    esp.send("status", "OK");
    lastSend = millis();
  }
}
