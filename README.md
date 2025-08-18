# ESPComm

ESPComm is a simple Arduino library that makes it easy to communicate between an **ESP8266/ESP32** and an **Arduino Uno** (or any Arduino board) using Serial.  
It uses a `key=value` style protocol for sending and receiving commands, making the communication structured and easy to parse.

---

## ✨ Features
- Simple `key=value` protocol
- Send and receive **int**, **float**, and **String** values
- Callback system for handling incoming commands
- Works with **HardwareSerial** or **SoftwareSerial**
- Lightweight and reusable
- Compatible with ESP8266, ESP32, Arduino Uno, Mega, Nano, etc.

---

## 📂 Installation
1. Download this repository as a `.zip`
2. In Arduino IDE go to:  
   **Sketch → Include Library → Add .ZIP Library...**  
   and select the downloaded `.zip`
3. Restart the IDE (if needed)

Or manually place the folder into:
```
Documents/Arduino/libraries/ESPComm
```

---

## 🚀 Usage

### Example: Receiving and Sending Data
```cpp
#include <ESPComm.h>

// Create instance (use Serial, Serial1, or SoftwareSerial)
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

  // Example: send some data every 2 seconds
  static unsigned long lastSend = 0;
  if (millis() - lastSend > 2000) {
    esp.send("level", random(0, 100));
    esp.send("gas", random(0, 100));
    esp.send("status", "OK");
    lastSend = millis();
  }
}
```

---

## 📖 API Reference

### Initialization
```cpp
ESPComm esp(Serial);  // can also use Serial1, Serial2, or SoftwareSerial
esp.begin(9600);      // optional, starts the serial at 9600 baud
```

### Handling Commands
```cpp
esp.onCommand(callback);
```
Callback signature:
```cpp
void callback(String key, String value);
```
Example incoming command:
```
level=42
```
This will call the callback with:
- `key = "level"`
- `value = "42"`

### Sending Data
```cpp
esp.send("key", intValue);
esp.send("key", floatValue, precision);   // default precision = 2
esp.send("key", "stringValue");
```

Examples:
```cpp
esp.send("temperature", 25);         // temperature=25
esp.send("humidity", 60.5, 1);       // humidity=60.5
esp.send("status", "OK");            // status=OK
```

---

## 📂 Folder Structure
```
ESPComm/
  ├── ESPComm.h
  ├── ESPComm.cpp
  ├── library.properties
  ├── keywords.txt
  ├── README.md
  └── examples/
      └── BasicExample/
          └── BasicExample.ino
```

---

## 📝 License
This library is released under the **MIT License** – feel free to use it in your projects (personal or commercial).

---

## 👨‍💻 Author
Developed by **Yohanna Philip Abana**  
GitHub: [yohanna02](https://github.com/yohanna02)
