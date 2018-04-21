#include <Ultrasonic.h>

HC_SR04 sensor1(12,13);  // (Trigger,Echo)

void setup() {
 Serial.begin(9600); 
}

void loop() {
 Serial.print(sensor1.distance());
 Serial.println(" cm");
}
