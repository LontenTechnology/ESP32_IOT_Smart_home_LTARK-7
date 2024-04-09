#include<analogWrite.h>

int greenpin =27;// select the pin for the green LED
int redpin = 14; //select the pin for the red LED
int bluepin =15; // select the pin for the  blue LED

int val;
void setup() { 
  pinMode(redpin, OUTPUT); 
  pinMode(bluepin, OUTPUT); 
  pinMode(greenpin, OUTPUT); 
  Serial.begin(9600);
}
void loop()
{
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

