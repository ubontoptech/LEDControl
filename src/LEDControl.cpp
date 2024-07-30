#include "LEDControl.h"

LEDControl::LEDControl(const char* ssid, const char* password, const char* serverName) {
  _ssid = ssid;
  _password = password;
  _serverName = serverName;
}

void LEDControl::begin() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);  // ปิด LED เริ่มต้น

  WiFi.begin(_ssid, _password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void LEDControl::updateLED() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(_serverName);

    int httpCode = http.GET();

    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println(httpCode);
      Serial.println(payload);

      if (payload.indexOf("ON") != -1) {
        digitalWrite(LED_BUILTIN, LOW);  // เปิด LED
      } else if (payload.indexOf("OFF") != -1) {
        digitalWrite(LED_BUILTIN, HIGH);  // ปิด LED
      }
    } else {
      Serial.println("Error on HTTP request");
    }

    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }

  delay(10000);  // ตรวจสอบทุก 10 วินาที
}
