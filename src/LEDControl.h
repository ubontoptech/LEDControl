#ifndef LEDControl_h
#define LEDControl_h

#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

class LEDControl {
  public:
    LEDControl(const char* ssid, const char* password, const char* serverName);
    void begin();
    void updateLED();
  private:
    const char* _ssid;
    const char* _password;
    const char* _serverName;
};

#endif
