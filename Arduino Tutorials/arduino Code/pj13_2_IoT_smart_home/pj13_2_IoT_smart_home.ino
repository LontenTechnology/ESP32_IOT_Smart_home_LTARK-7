#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiClient.h>

String item = "0";
const char* ssid = "longvn-US";
const char* password = "llll8888";
WiFiServer server(80);

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C mylcd(0x27,16,2);
#include <analogWrite.h>
#include "xht11.h"
xht11 xht(26);
#include <ESP32_Servo.h>
Servo Wservo;
Servo Dservo;
#include <ESP32Tone.h>
#define buzzer_pin 32
#define windowServo 12
#define doorServo 13
#define waterPin 34
#define fanPinA 25
#define fanPinB 33
#define led_y 2  //Define the yellow led pin to 2

#define gasPin 39
#define pyroelectric 35

unsigned char dht[4] = {0, 0, 0, 0};//Only the first 32 bits of data are received, not the parity bits

int val;
int greenpin =27;// select the pin for the green LED
int redpin = 14; //select the pin for the red LED
int bluepin =15; // select the pin for the  blue LED



void setup() {
  Serial.begin(115200);
  mylcd.init();
  mylcd.backlight();
  pinMode(led_y, OUTPUT);
  pinMode(fanPinA, OUTPUT);
  pinMode(fanPinB, OUTPUT);
  pinMode(redpin, OUTPUT); 
  pinMode(bluepin, OUTPUT); 
  pinMode(greenpin, OUTPUT); 
  pinMode(waterPin, INPUT);
  pinMode(buzzer_pin, OUTPUT);
  pinMode(gasPin, INPUT);
  pinMode(pyroelectric, INPUT);
  Wservo.attach(windowServo);
  Dservo.attach(doorServo);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
  Serial.println("TCP server started");
  MDNS.addService("http", "tcp", 80);
  mylcd.setCursor(0, 0);
  mylcd.print("ip:");
  mylcd.setCursor(0, 1);
  mylcd.print(WiFi.localIP());  //LCD displays ip adress
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
      return;
  }
  while(client.connected() && !client.available()){
      delay(1);
  }
  String req = client.readStringUntil('\r');
  int addr_start = req.indexOf(' ');
  int addr_end = req.indexOf(' ', addr_start + 1);
  if (addr_start == -1 || addr_end == -1) {
      Serial.print("Invalid request: ");
      Serial.println(req);
      return;
  }
  req = req.substring(addr_start + 1, addr_end);
  item=req;
  Serial.println(item);
  String s;
  if (req == "/")  //Browser accesses address can read the information sent by the client.println(s);
  {
      IPAddress ip = WiFi.localIP();
      String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
      s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>ESP32 ip:";
      s += ipStr;
      s += "</html>\r\n\r\n";
      Serial.println("Sending 200");
      client.println(s);  //Send the string S, then you can read the information when visiting the address of E smart home using the browser.
  }
  if(req == "/led/on") //Browser accesses address ip address/led/on
  {
    client.println("turn on the LED");
    digitalWrite(led_y, HIGH);
  }
  if(req == "/led/off") //Browser accesses address ip address/led/off
  {
    client.println("turn off the LED");
    digitalWrite(led_y, LOW);
  }
  if(req == "/window/on")
  {
    client.println("open the window");
    Wservo.write(180);
  }
  if(req == "/window/off")
  {
    client.println("close the window");
    Wservo.write(0);
  }
  if(req == "/music/on")
  {
    client.println("play music");
    birthday();
  }
  if(req == "/music/off")
  {
    client.println("music off");
    noTone(buzzer_pin,0);
  }
  if(req == "/buz/on")
  {
    client.println("buzzer");
    tone(buzzer_pin,392,250,0);
  }
  if(req == "/buz/off")
  {
    client.println("off");
    noTone(buzzer_pin,0);
  }
  if(req == "/door/on")
  {
    client.println("open the door");
    Dservo.write(180);
  }
  if(req == "/door/off")
  {
    client.println("close the door");
    Dservo.write(0);
  }
  if(req == "/fan/on")
  {
    client.println("turn on the fan");
    digitalWrite(fanPinA, LOW); //pwm = 0
    analogWrite(fanPinB, 180);
  }
  if(req == "/fan/off")
  {
    client.println("turn off the fan");
    digitalWrite(fanPinA, LOW); //pwm = 0
    analogWrite(fanPinB, 0);
  }
  if(req == "/red/on")
  {
    client.println("red on");
    analogWrite(redpin, 255); analogWrite(greenpin, 0);  analogWrite(bluepin, 0);
  }
  if(req == "/red/off")
  {
    client.println("red off");
    analogWrite(redpin, 0); analogWrite(greenpin, 0); analogWrite(bluepin, 0);
  }
  if(req == "/oringe/on")
  {
    client.println("oringe on");
    analogWrite(redpin, 255); analogWrite(greenpin, 165); analogWrite(bluepin, 0);
  }
  if(req == "/oringe/off")
  {
    client.println("oringe off");
    analogWrite(redpin, 0); analogWrite(greenpin, 0); analogWrite(bluepin, 0);
  }
  if(req == "/yellow/on")
  {
    client.println("yellow on");
    analogWrite(redpin, 255); analogWrite(greenpin, 255); analogWrite(bluepin, 0);
  }
  if(req == "/yellow/off")
  {
    client.println("yellow off");
    analogWrite(redpin, 0); analogWrite(greenpin, 0); analogWrite(bluepin, 0);
  }
  if(req == "/green/on")
  {
    client.println("green on");
    analogWrite(redpin, 0); analogWrite(greenpin, 255); analogWrite(bluepin, 0);
  }
  if(req == "/green/off")
  {
    client.println("green off");
    analogWrite(redpin, 0); analogWrite(greenpin, 0); analogWrite(bluepin, 0);
  }
  if(req == "/black/on")
  {
    client.println("black on");
    analogWrite(redpin, 0); analogWrite(greenpin, 0); analogWrite(bluepin, 0);
  }
  if(req == "/black/off")
  {
    client.println("black off");
    analogWrite(redpin, 0); analogWrite(greenpin, 0); analogWrite(bluepin, 0);
  }
  if(req == "/cyan/on")
  {
    client.println("cyan on");
    analogWrite(redpin, 0); analogWrite(greenpin, 255); analogWrite(bluepin, 255);
  }
  if(req == "/cyan/off")
  {
    client.println("cyan off");
    analogWrite(redpin, 0); analogWrite(greenpin, 0); analogWrite(bluepin, 0);
  }
  if(req == "/blue/on")
  {
    client.println("blue on");
    analogWrite(redpin, 0); analogWrite(greenpin, 0); analogWrite(bluepin, 255);
  }
  if(req == "/blue/off")
  {
    client.println("blue off");
    analogWrite(redpin, 0); analogWrite(greenpin, 0); analogWrite(bluepin, 0);
  }
  if(req == "/purple/on")
  {
    client.println("purple on");
    analogWrite(redpin, 160); analogWrite(greenpin, 32); analogWrite(bluepin, 240);
  }
  if(req == "/purple/off")
  {
    client.println("purple off");
    analogWrite(redpin, 0); analogWrite(greenpin, 0); analogWrite(bluepin, 0);
  }
  if(req == "/white/on")
  {
    client.println("white on");
    analogWrite(greenpin, 255); analogWrite(redpin, 255); analogWrite(bluepin, 255);
  }
  if(req == "/white/off")
  {
    client.println("white off");
    analogWrite(greenpin, 0); analogWrite(redpin, 0); analogWrite(bluepin, 0);
  }
  if(req == "/sfx1/on")
  {
    client.println("sfx1 on");
    rainbow();
  }
  if(req == "/sfx1/off")
  {
    client.println("sfx1 off");
    analogWrite(greenpin, 0); analogWrite(redpin, 0); analogWrite(bluepin, 0);
  }
  if(req == "/sfx2/on")
  {
    client.println("sfx2 on");
    theaterChaseRainbow();
  }
  if(req == "/sfx2/off")
  {
    client.println("sfx2 off");
    analogWrite(greenpin, 0); analogWrite(redpin, 0); analogWrite(bluepin, 0);
  }
  
  if(req == "/rain/on")
  {
    int rainVal = analogRead(waterPin);
    client.println(rainVal);
  }
  if(req == "/rain/off")
  {
    client.println("off");
  }
  if(req == "/gas/on")
  {
    boolean gasVal = analogRead(gasPin);
    if(gasVal == 0)
    {
      client.println("dangerous");
    }
    else
    {
      client.println("safety");
    }
  }
  if(req == "/gas/off")
  {
    client.println("off");
  }
  if(req == "/body/on")
  {
    boolean pyroelectric_val = digitalRead(pyroelectric);
    if(pyroelectric_val == 1)
    {
      client.println("someone");
    }
    else
    {
      client.println("no one");
    }
  }
  if(req == "/body/off")
  {
    client.println("off");
  }
  if(req == "/temp/on")
  {
    if (xht.receive(dht)) { //Returns true when checked correctly
      Serial.print("Temp:");
      Serial.print(dht[2]); //The integral part of temperature, DHT [3] is the fractional part
      Serial.println("C");
      delay(200);
    } else {    //Read error
      Serial.println("sensor error");
    }
    client.println(dht[2]);
    delay(1000);  //It takes 1000ms to wait for the device to read
  }
  if(req == "/temp/off")
  {
    client.println("off");
  }
  if(req == "/humidity/on")
  {
    if (xht.receive(dht)) { //Returns true when checked correctly
      Serial.print("Temp:");
      Serial.print(dht[0]); //The integral part of temperature, DHT [3] is the fractional part
      Serial.println("%");
      delay(200);
    } else {    //Read error
      Serial.println("sensor error");
    }
    client.println(dht[0]);
    delay(1000);  //It takes 1000ms to wait for the device to read
  }
  if(req == "/humidity/off")
  {
    client.println("off");
  }
  //client.stop();
}


void birthday()
{
  tone(buzzer_pin,294,250,0);  //The four parameters are pin, frequency, delay and channel 
  tone(buzzer_pin,440,250,0);
  tone(buzzer_pin,392,250,0);
  tone(buzzer_pin,532,250,0);
  tone(buzzer_pin,494,250,0);
  tone(buzzer_pin,392,250,0);
  tone(buzzer_pin,440,250,0);
  tone(buzzer_pin,392,250,0);
  tone(buzzer_pin,587,250,0);
  tone(buzzer_pin,532,250,0);
  tone(buzzer_pin,392,250,0);
  tone(buzzer_pin,784,250,0);
  tone(buzzer_pin,659,250,0);
  tone(buzzer_pin,532,250,0);
  tone(buzzer_pin,494,250,0);
  tone(buzzer_pin,440,250,0);
  tone(buzzer_pin,698,250,0);
  tone(buzzer_pin,659,250,0);
  tone(buzzer_pin,532,250,0);
  tone(buzzer_pin,587,250,0);
  tone(buzzer_pin,532,500,0);
  noTone(buzzer_pin,0);  //关闭
}


// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow() {
  for(val=255; val>0; val--)
  {
    analogWrite(greenpin, val); 
    analogWrite(redpin, 255-val); 
    analogWrite(bluepin, 128-val); 
    delay(50);
  }
  for(val=0; val<255; val++)
  {
    analogWrite(greenpin, val); 
    analogWrite(redpin, 255-val); 
    analogWrite(bluepin, 128-val); 
    delay(50);
  }
}

// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void theaterChaseRainbow() {
  for(val=255; val>0; val--)
  {
    analogWrite(greenpin, val); 
    analogWrite(redpin, 128-val); 
    analogWrite(bluepin, 255-val); 
    delay(50);
  }
  for(val=0; val<255; val++)
  {
    analogWrite(greenpin, val); 
    analogWrite(redpin, 128-val); 
    analogWrite(bluepin, 255-val); 
    delay(50);
  }
}
