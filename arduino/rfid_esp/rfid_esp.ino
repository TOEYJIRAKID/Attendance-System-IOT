#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <PubSubClient.h>
#include <TridentTD_LineNotify.h>

#define WLAN_SSID       "MAIBOK"
#define WLAN_PASS       "1223334444"
#define LINE_TOKEN  "gB85gszN0tz3JjSJ2R4NDxgd6nQaReD2jiMPKfqzX9t"

const char* mqttServer = "192.168.43.248";
const int mqttPort = 1883;
const char* mqttTopic = "users";

String incomingString;

int scanCount1 = 0;  
int scanCount2 = 0; 
int scanCount3 = 0;  

WiFiClient espClient;
PubSubClient client(espClient);

const long utcOffsetInSeconds = 7 * 3600;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

void setup() {
  Serial.begin(115200);
  Serial.println(F("ESP8266 Example"));

  Serial.println(); Serial.println();
  delay(10);
  Serial.print(F("Connecting to "));
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  Serial.println();

  Serial.println(F("WiFi connected"));
  Serial.println(F("IP address: "));
  Serial.println(WiFi.localIP());

  timeClient.begin();

  client.setServer(mqttServer, mqttPort);

  LINE.setToken(LINE_TOKEN);
}

void loop() {
  if (Serial.available()) {
    incomingString = Serial.readString();
    processID(incomingString.charAt(0));
  }

  if (!client.connected()) {
    reconnect();
  }

  client.loop();
}

void processID(char id) {
  String studentid, firstname, lastname, timestamp, jobPosition, status;

  if (id == '1') {
    studentid = "64102080";
    firstname = "จิรกิตติ์";
    lastname = "เอียดเหตุ";
    jobPosition = "นักศึกษา";
    scanCount1++;
    status = (scanCount1 % 2 == 0) ? "ออก" : "เข้า";
  } else if (id == '2') {
    studentid = "64125735";
    firstname = "ธนวัฒน์";
    lastname = "กองสีสังข์";
    jobPosition = "นักศึกษา";
    scanCount2++;
    status = (scanCount2 % 2 == 0) ? "ออก" : "เข้า";
  } else if (id == '3') {
    studentid = "64110455";
    firstname = "ภัครศักดิ์";
    lastname = "ผลสนอง";
    jobPosition = "นักศึกษา";
    scanCount3++;
    status = (scanCount3 % 2 == 0) ? "ออก" : "เข้า";
  }

  timestamp = getCurrentDateTime();

  Serial.println("ID: " + String(id));
  Serial.println("StdId: " + studentid);
  Serial.println("Firstname: " + firstname);
  Serial.println("Lastname: " + lastname);
  Serial.println("Position: " + jobPosition);
  Serial.println("Timestamp: " + timestamp);
  Serial.println("Status: " + status);

  sendToMQTT(id, studentid, firstname, lastname, jobPosition, timestamp, status);
  sendToLINE(studentid, firstname, lastname, jobPosition, timestamp, status);
}

void sendToLINE(String studentid, String firstname, String lastname, String jobPosition, String timestamp, String status) {
  String lineMessage = "ระบบแจ้งเตือนเข้า-ออกมหาลัย\n\n"
                      "รหัสนักเรียน: " + studentid + "\n"
                      "ชื่อ-นามสกุล: " + firstname + " " + lastname + "\n"
                      "ตำแหน่ง: " + jobPosition + "\n"
                      "เวลา: " + timestamp + "\n"
                      "สถานะเข้า-ออกมหาลัย: " + status + "\n\n"
                      "ขอบคุณที่ให้ความสนใจในการเช็คข้อมูลนักศึกษาของท่าน";

  LINE.notify(lineMessage);
}

String getCurrentDateTime() {
  timeClient.update();

  String dateTime = timeClient.getFormattedTime();
  return dateTime;
}

void sendToMQTT(char id, String studentid, String firstname, String lastname, String jobPosition, String timestamp, String status) {
  String jsonPayload = "{\"uid\":\"" + String(id) + "\","
                      "\"studentid\":\"" + studentid + "\","
                      "\"firstname\":\"" + firstname + "\","
                      "\"lastname\":\"" + lastname + "\","
                      "\"position\":\"" + jobPosition + "\","
                      "\"timestamp\":\"" + timestamp + "\","
                      "\"status\":\"" + status + "\"}";

  client.publish(mqttTopic, jsonPayload.c_str());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print(F("Attempting MQTT connection..."));
    if (client.connect("ESP8266Client")) {
      Serial.println(F("connected"));
    } else {
      Serial.print(F("failed, rc="));
      Serial.print(client.state());
      Serial.println(F(" try again in 5 seconds"));
      delay(5000);
    }
  }
}