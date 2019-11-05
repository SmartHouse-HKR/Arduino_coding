#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>

SoftwareSerial softSerial(D2,D3);
 bool waitingMsg = false;

void setup(){
	Serial.begin(9600);
	softSerial.begin(4800);
	pinMode(D2,INPUT);
	pinMode(D3,OUTPUT);
}

void loop(){
  
  if(softSerial.available())
    waitingMsg = true;
  if(waitingMsg){
  Serial.println(receiveMessage());
   delay(2000);
  sendMessage("confirmed");
  waitingMsg = false;
}
}

void sendMessage(String message){
  char charArray[50];
  message.toCharArray(charArray, 20);
  softSerial.write(charArray);
  softSerial.write('\n');
}

String receiveMessage(){

  char part;    String message= "";
    while(softSerial.available()){
      part = ((char)softSerial.read());
      if(part != '\n'){
      message += part;    
      }else if(message != "")
        break;

      delay(50);
}
return message;
}
