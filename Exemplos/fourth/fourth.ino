int led = 11;
void setup(){
  pinMode(led, OUTPUT);
}
void loop(){
  
 int i;
 for (i = 10; i <= 255; i+=50) {
   analogWrite(led, i); // Aumenta a intensidade
   delay(500);
 }
 for (i = 255; i >= 5; i-=50) {
   analogWrite(led, i); // Diminui a intensidade
   delay(500);
 }

}

