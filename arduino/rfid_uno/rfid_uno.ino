#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <MFRC522.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 OLED(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(115200);
  SPI.begin();
  mfrc522.PCD_Init();
  Wire.begin();
  OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loop() {

  displayText();

  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  String content = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();

  OLED.clearDisplay();
  OLED.setCursor(0, 0);
  OLED.setTextSize(1);

  if (content.substring(1) == "7F 6C AF 29") {
    Serial.println("1");
    Serial.println();
    delay(500);
    OLED.setTextSize(1);
    OLED.println("SID: 64102080");
    OLED.println("Name: Jirakit");
    OLED.println("Position: Student");
    OLED.println();
    OLED.setTextSize(3);
    OLED.println("SUCCESS");
  } else if (content.substring(1) == "D3 24 0D 02") {
    Serial.println("2");
    Serial.println();
    delay(500);
    OLED.setTextSize(1);
    OLED.println("SID: 64125735");
    OLED.println("Name: Thanawat");
    OLED.println("Position: Student");
    OLED.println();
    OLED.setTextSize(3);
    OLED.println("SUCCESS");
  } else if (content.substring(1) == "05 81 35 5B") {
    Serial.println("3");
    Serial.println();
    delay(500);
    OLED.setTextSize(1);
    OLED.println("SID: 64110455");
    OLED.println("Name: Phakharasak");
    OLED.println("Position: Student");
    OLED.println();
    OLED.setTextSize(3);
    OLED.println("SUCCESS");
  } else {
    OLED.setTextSize(3);
    OLED.println();
    OLED.println("UNKNOWN");
  }

  OLED.display();

  delay(2000);

  OLED.clearDisplay();
}

void displayText() {
  OLED.clearDisplay();
  OLED.setTextColor(WHITE, BLACK);
  OLED.setCursor(13, 20);
  OLED.setTextSize(1); 
  OLED.println("ATTENDANCE SYSTEM");
  OLED.setCursor(13, 35);
  OLED.setTextSize(1);
  OLED.println("Please Scanning..");
  OLED.display();
}
