#include <SoftwareSerial.h>

#define DEBUG true

SoftwareSerial esp8266(2,3); // muda o RX Arduino para pino 2, TX para pino 3.
                             
void setup()
{
  Serial.begin(9600);
  esp8266.begin(9600); 
  
  pinMode(11,OUTPUT);
  digitalWrite(11,LOW);
  
   
  sendData("AT+RST\r\n",2000,DEBUG); // reseta o modulo
  sendData("AT+CWMODE=3\r\n",1000,DEBUG); // configura como ponto de acesso e cliente
  sendData("AT+CWJAP=\"Divino Borges 1\",\"90521212\"\r\n", 3000, DEBUG);
  sendData("AT+CIFSR\r\n",2000,DEBUG); // obtem o IP
  sendData("AT+CIPMUX=1\r\n",1000,DEBUG); // configura para multiplas conexoes
  sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG); // liga o server na porta 90
}
 
void loop()
{

  if(esp8266.available()) // check if the esp is sending a message 
  {
 
    
    if(esp8266.find("+IPD,"))
    {
     delay(1000); 
     
     int connectionId = esp8266.read()-48; // subtrair 48 porque a função read () retorna 
                                           // o valor decimal ASCII e 0 (o primeiro número decimal) começa em 48
          
     esp8266.find("pin="); 
     
     int pinNumber = (esp8266.read()-48)*10; 
     pinNumber += (esp8266.read()-48);
     
     digitalWrite(pinNumber, !digitalRead(pinNumber)); // alterna o pino    
     Serial.println(pinNumber);

     servidor(connectionId); 
     
     String closeCommand = "AT+CIPCLOSE="; 
     closeCommand+=connectionId; 
     closeCommand+="\r\n";
     
     sendData(closeCommand,1000,DEBUG); 
    }
  }
}
 

String sendData(String command, const int timeout, boolean debug)
{
    String response = "";
    
    esp8266.print(command); 
    
    long int time = millis();
    
    while( (time+timeout) > millis())
    {
      while(esp8266.available())
      {
        
        
        char c = esp8266.read(); 
        response+=c;
      }  
    }
    
    if(debug)
    {
      Serial.print(response);
    }
    
    return response;
}

void servidor(int connectionId){
  String webpage = "<h1>Testando</h1>";
 
     String cipSend = "AT+CIPSEND=";
     
     cipSend = "AT+CIPSEND=";
     cipSend += connectionId;
     cipSend += ",";
     cipSend +=webpage.length();
     cipSend +="\r\n";
     
     sendData(cipSend,1000,DEBUG);
     sendData(webpage,1000,DEBUG);
 
     String closeCommand = "AT+CIPCLOSE="; 
     closeCommand+=connectionId; // append connection id
     closeCommand+="\r\n";
     
     sendData(closeCommand,3000,DEBUG);
}
