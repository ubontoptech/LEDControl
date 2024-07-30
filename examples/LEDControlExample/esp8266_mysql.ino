//by Mr.Settapong Phalaprom | TH (Ubonratchathani) Email:Ubontoptech@gmail.com

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "your_SSID";  // ชื่อเครือข่าย Wi-Fi
const char* password = "your_PASSWORD";  // รหัสผ่าน Wi-Fi

const char* serverName = "http://your_server_ip/control_led.php";  // เปลี่ยน 'your_server_ip' เป็น IP ของเซิร์ฟเวอร์ XAMPP

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);  // ปิด LED เริ่มต้น

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName);
    
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

///////////////////////////////////////////////////////// HOW TO /////////////////////////////////////////////////////////////////////////////////////////////////
//by Mr.Settapong Phalaprom | TH (Ubbonratchathani) Email:Ubontoptech@gmail.com
//ขั้นตอนที่ 1: สร้างฐานข้อมูลและตารางใน MySQL เช่น nodemcu_db
//สร้างตารางในฐานข้อมูล เช่น led_status 
//CREATE TABLE `led_status` (
//   `id` INT(11) NOT NULL AUTO_INCREMENT,
//   `status` VARCHAR(10) NOT NULL,
//   `timestamp` TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
//   PRIMARY KEY (`id`)
// );
//
// ขั้นตอนที่ 2: เขียนโค้ด PHP สำหรับควบคุม LED และบันทึกสถานะ
// สร้างไฟล์ PHP ชื่อ control_led.php ในโฟลเดอร์ www ของ AppServ (เช่น C:\AppServ\www\control_led.php) และเพิ่มโค้ดดังนี้:
// <?php
// $servername = "localhost";
// $username = "root";
// $password = "";
// $dbname = "led_control_db";

// $conn = new mysqli($servername, $username, $password, $dbname);

// if ($conn->connect_error) {
//     die("Connection failed: " . $conn->connect_error);
// }

// if ($_SERVER["REQUEST_METHOD"] == "POST") {
//     $status = $_POST["status"];
//     $sql = "INSERT INTO led_status (status) VALUES ('$status')";

//     if ($conn->query($sql) === TRUE) {
//         echo "Status updated successfully";
//     } else {
//         echo "Error: " . $sql . "<br>" . $conn->error;
//     }

//     $conn->close();
// }
// ?>
// <!DOCTYPE html>
// <html>
// <head>
//     <title>LED Control</title>
// </head>
// <body>
//     <h1>LED Control</h1>
//     <form method="post">
//         <button name="status" value="ON">Turn ON</button>
//         <button name="status" value="OFF">Turn OFF</button>
//     </form>
//     <h2>Status Report</h2>
//     <table border="1">
//         <tr>
//             <th>ID</th>
//             <th>Status</th>
//             <th>Timestamp</th>
//         </tr>
//         <?php
//         $sql = "SELECT * FROM led_status ORDER BY id DESC";
//         $result = $conn->query($sql);

//         if ($result->num_rows > 0) {
//             while($row = $result->fetch_assoc()) {
//                 echo "<tr><td>" . $row["id"]. "</td><td>" . $row["status"]. "</td><td>" . $row["timestamp"]. "</td></tr>";
//             }
//         } else {
//             echo "<tr><td colspan='3'>No records found</td></tr>";
//         }
//         ?>
//     </table>
// </body>
// </html>
// ขั้นตอนที่ 4: เขียนโค้ดใน NodeMCU เพื่อรับคำสั่งและควบคุม LED
// อธิบายโค้ด:
// โค้ด PHP: จะรับคำสั่งเปิดหรือปิดไฟ LED จากผู้ใช้ และบันทึกสถานะลงในฐานข้อมูล พร้อมแสดงรายงานผล
// โค้ด NodeMCU: จะเชื่อมต่อกับ Wi-Fi และตรวจสอบคำสั่งจากเซิร์ฟเวอร์ทุกๆ 10 วินาทีเพื่อควบคุม LED
// หมายเหตุ:
// เปลี่ยน your_SSID และ your_PASSWORD ในโค้ด NodeMCU ให้เป็นข้อมูลจริงของ Wi-Fi ที่คุณใช้
// เปลี่ยน your_server_ip ในโค้ด NodeMCU ให้เป็น IP จริงของเซิร์ฟเวอร์ AppServ ของคุณ
// ตรวจสอบให้แน่ใจว่า NodeMCU และเซิร์ฟเวอร์ AppServ อยู่ในเครือข่ายเดียวกัน