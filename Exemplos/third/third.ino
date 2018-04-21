int valor;
void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);

}

void loop() {
  valor = analogRead(A0);
  valor = map(valor,1023,450,0,100);
  Serial.println(valor);
  Serial.print("%");
}
