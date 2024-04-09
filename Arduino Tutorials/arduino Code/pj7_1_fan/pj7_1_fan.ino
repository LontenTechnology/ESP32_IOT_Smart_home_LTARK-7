#include <analogWrite.h>
#define fanPinA 25
#define fanPinB 33

void setup() {
  pinMode(fanPinA, OUTPUT);
  pinMode(fanPinB, OUTPUT);
}

void loop() {
  //Fan forward rotation
  digitalWrite(fanPinA, HIGH); //pwm = 255
  digitalWrite(fanPinB, LOW);
  delay(3000);
  digitalWrite(fanPinA, LOW);
  digitalWrite(fanPinB, LOW);
  delay(3000);
  //Fan reversal
  digitalWrite(fanPinA, LOW); //pwm = 0
  digitalWrite(fanPinB, HIGH);
  delay(3000);
  digitalWrite(fanPinA, LOW);
  digitalWrite(fanPinB, LOW);
  delay(3000);
}
