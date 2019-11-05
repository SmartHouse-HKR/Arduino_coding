#include <SoftwareSerial.h>
SoftwareSerial softSerial(0,1);
 bool waitingMsg = false;
  int messageSent = 0;
  int pin1 = 8;
  int pin2 = 11;
  int pin3 = 12;
  int pin4 = 13;
  int fanPin = 13;


void sendMessage(String message){

  char charArray[50];
  message.toCharArray(charArray, 20);
  softSerial.write(charArray);
  softSerial.write(messageSent++);
  softSerial.write('\n');
}

String receiveMessage(){ 
  char part;
  String message= "";
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

void turnOnLight(){
   digitalWrite(pin1, HIGH);
  digitalWrite(pin2, HIGH);
  digitalWrite(pin3, LOW);
  digitalWrite(pin4, HIGH);
}
void turnOffLight(){
   digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, HIGH);
  digitalWrite(pin4, HIGH);
}

void setup(){

    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
    pinMode(pin3, OUTPUT);
    pinMode(pin4, OUTPUT);
    pinMode(fanPin, OUTPUT);
    
turnOffLight();
  
  Serial.begin(9600);
  softSerial.begin(4800);

}

void loop(){
  
  if(softSerial.available()){
    String returnedMessage = receiveMessage();
    if(returnedMessage.equals("ON")){
      turnOnLight();
        digitalWrite(fanPin, HIGH);
      Serial.println(returnedMessage);
    }else if(returnedMessage.equals("OFF")){
     turnOffLight();
     digitalWrite(fanPin, LOW);
    }
  }
  }
  
