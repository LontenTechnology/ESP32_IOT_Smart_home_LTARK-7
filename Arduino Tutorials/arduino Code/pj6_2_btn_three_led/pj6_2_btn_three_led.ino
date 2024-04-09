#include<analogWrite.h>

int greenpin =27;// select the pin for the green LED
int redpin = 14; //select the pin for the red LED
int bluepin =15; // select the pin for the  blue LED

#define btn1 16
#define btn2 4


int btn_count = 0; //Used to count the clicked button times 
void setup() {
  Serial.begin(9600);
  pinMode(redpin, OUTPUT); 
  pinMode(bluepin, OUTPUT); 
  pinMode(greenpin, OUTPUT); 
  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);
}

void loop() {
  boolean btn1_val = digitalRead(btn1);
  boolean btn2_val = digitalRead(btn2);
  if(btn1_val == 0) //If the button is pressed
  {
    delay(10);  //Delay 10ms to eliminate button jitter
    if(btn1_val == 0) //Make sure the button is pressed again  
    {
      boolean btn_state = 1;
      while(btn_state == 1) //Loop indefinitely until the button is released
      {
        boolean btn_val = digitalRead(btn1);
        if(btn_val == 1)  //If the button is released
        {
          btn_count--;    //Automatically increments by 1 to count the clicked button times
          if(btn_count <= 0)
          {
            btn_count = 0;
          }
          Serial.println(btn_count);
          btn_state = 0;  //The button is released and exits the loop
        }
      }
    }
  }
    
  if(btn2_val == 0) //If the button is pressed
  {
    delay(10);  //Delay 10ms to eliminate button jitter
    if(btn2_val == 0) //Make sure the button is pressed again  
    {
      boolean btn_state2 = 1;
      while(btn_state2 == 1) //Loop indefinitely until the button is released
      {
        boolean btn2_val = digitalRead(btn2);
        if(btn2_val == 1)  //If the button is released
        {
          btn_count++;    //Automatically increments by 1 to count the clicked button times 
          if(btn_count >= 6)
          {
            btn_count = 6;
          }
          Serial.println(btn_count);
          btn_state2 = 0;  //The button is released and exits the loop
        }
      }
    }
  }

  switch(btn_count)
  {
    case 0: analogWrite(redpin, 0); analogWrite(greenpin, 0);  analogWrite(bluepin, 0); break;        //off
    case 1: analogWrite(redpin, 255); analogWrite(greenpin, 0);  analogWrite(bluepin, 0); break;      //red
    case 2: analogWrite(redpin, 255); analogWrite(greenpin, 255); analogWrite(bluepin, 0);break;      //yellow
    case 3: analogWrite(redpin, 0); analogWrite(greenpin, 255); analogWrite(bluepin, 0);break;        //green
    case 4: analogWrite(redpin, 0); analogWrite(greenpin, 255); analogWrite(bluepin, 255);break;      //cyan
    case 5: analogWrite(redpin, 0); analogWrite(greenpin, 0); analogWrite(bluepin, 255);break;        //blue
    case 6: analogWrite(redpin, 160); analogWrite(greenpin, 32); analogWrite(bluepin, 240);break;     //purple
  }
}
