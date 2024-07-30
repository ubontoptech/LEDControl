#include <LEDControl.h>

const char* ssid = "your_SSID";  // ชื่อเครือข่าย Wi-Fi
const char* password = "your_PASSWORD";  // รหัสผ่าน Wi-Fi
const char* serverName = "http://your_server_ip/control_led.php";  // เปลี่ยน 'your_server_ip' เป็น IP ของเซิร์ฟเวอร์

LEDControl ledControl(ssid, password, serverName);

void setup() {
  ledControl.begin();
}

void loop() {
  ledControl.updateLED();
}
