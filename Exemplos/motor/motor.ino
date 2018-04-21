#include <Servo.h>

Servo myservo;  

int val;

void setup() {
  myservo.attach(9);
}

void loop() {
  val = analogRead(A0);           
  val = map(val, 0, 1023, 0, 180);    
  myservo.write(val);                  
  delay(15);   
}
