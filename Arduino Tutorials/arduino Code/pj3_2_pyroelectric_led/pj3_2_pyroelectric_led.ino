#define pyroelectric 35
#define led_y 2  //Define the yellow led pin to 2
void setup() {
  Serial.begin(9600);
  pinMode(pyroelectric, INPUT);
  pinMode(led_y, OUTPUT);  //Set pin to output mode
}

void loop() {
  boolean pyroelectric_val = digitalRead(pyroelectric);
  Serial.print("pyroelectric value = ");
  Serial.println(pyroelectric_val);
  delay(200);
  if(pyroelectric_val == 1)
  {
    digitalWrite(led_y, HIGH);
  }else{
    digitalWrite(led_y, LOW);
  }
}
