#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C mylcd(0x27,16,2);
#include <ESP32_Servo.h>
Servo myservo;
#include <Wire.h>
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN     17    // RST:17
#define SS_PIN      5    // SDA:5

MFRC522 mfrc522(SS_PIN, RST_PIN);  
#define servoPin  13
#define btnPin 16
boolean btnFlag = 0;

void setup() {
  Serial.begin(9600);           // initialize and PC's serial communication
  mylcd.init();
  mylcd.backlight();
  Wire.begin();                 // initialize I2C
  SPI.begin();                 // Initialize SPI bus
  mfrc522.PCD_Init();          // Initialize MFRC522 module
  Serial.println("Scan RFID tag to get its UID...");
  myservo.attach(servoPin);
  myservo.write(0);
  pinMode(btnPin, INPUT);
  mylcd.setCursor(0, 0);
  mylcd.print("Card");
}

void loop() {
    // close door use button
    if(btnFlag == 1)
    {
      boolean btnVal = digitalRead(btnPin);
      if(btnVal == 0)  //Swipe the card to open the door and click button 1 to close the door
      {
        Serial.println("close");
        mylcd.setCursor(0, 0);
        mylcd.print("close");
        myservo.write(0);
        btnFlag = 0;
      }
    }
  // select one of door cards. UID and SAK are mfrc522.uid.
  // save UID
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    Serial.print("UID tag :");
    String content = "";
    byte letter;
    for (byte i = 0; i < mfrc522.uid.size; i++) {
       Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
       Serial.print(mfrc522.uid.uidByte[i],HEX);
       content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
       content.concat(String(mfrc522.uid.uidByte[i],HEX));
    }
    Serial.println();
    Serial.print("Message : ");
    content.toUpperCase();
    if (content.substring(1) == "F3 C6 6F 1A") {
      Serial.println("open");
      mylcd.setCursor(0, 0);
      mylcd.clear();
      mylcd.print("open");
      myservo.write(180);
      btnFlag = 1;
    }
    else {
       mylcd.setCursor(0, 0);
       mylcd.print("error");
       btnFlag = 0;
    }
  }
}
