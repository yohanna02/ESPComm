#include "ESPComm.h"

ESPComm::ESPComm(Stream &serial) {
  _serial = &serial;
  _callback = nullptr;
}

void ESPComm::begin(long baud) {
  if (_serial == &Serial) {
    Serial.begin(baud);
  }
#if defined(ESP8266)
  else if (_serial == &Serial1) {
    Serial1.begin(baud);
  }
#elif defined(ESP32)
  else if (_serial == &Serial1) {
    Serial1.begin(baud);
  } else if (_serial == &Serial2) {
    Serial2.begin(baud);
  }
#elif defined(ARDUINO_AVR_MEGA2560) || defined(ARDUINO_AVR_MEGA)
  else if (_serial == &Serial1) {
    Serial1.begin(baud);
  } else if (_serial == &Serial2) {
    Serial2.begin(baud);
  } else if (_serial == &Serial3) {
    Serial3.begin(baud);
  }
#endif
}

void ESPComm::loop() {
  if (_serial->available()) {
    String cmd = _serial->readStringUntil('\n');
    int sepIndex = cmd.indexOf('=');

    if (sepIndex != -1 && _callback) {
      String key = cmd.substring(0, sepIndex);
      String value = cmd.substring(sepIndex + 1);
      _callback(key, value);
    }
  }
}

void ESPComm::onCommand(void (*callback)(String key, String value)) {
  _callback = callback;
}

// -------- Sending --------
void ESPComm::send(String key, int value) {
  _serial->print(key);
  _serial->print("=");
  _serial->print(value);
  _serial->print('\n');
}

void ESPComm::send(String key, float value, int precision) {
  _serial->print(key);
  _serial->print("=");
  _serial->print(value, precision);
  _serial->print('\n');
}

void ESPComm::send(String key, String value) {
  _serial->print(key);
  _serial->print("=");
  _serial->print(value);
  _serial->print('\n');
}
