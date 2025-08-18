#ifndef ESPComm_h
#define ESPComm_h

#include <Arduino.h>

class ESPComm {
 public:
  ESPComm(Stream& serial);  // constructor with HardwareSerial or SoftwareSerial

  void begin(long baud);  // start serial
  void loop();            // must be called in main loop()
  void onCommand(void (*callback)(String key, String value));

  // send different datatypes
  void send(String key, int value);
  void send(String key, float value, int precision = 2);
  void send(String key, String value);

 private:
  Stream* _serial;
  void (*_callback)(String, String);
};

#endif
