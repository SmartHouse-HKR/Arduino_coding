#include <SoftwareSerial.h>
SoftwareSerial wifiMessage(2,3);


/*  Pin variables   */
int pin1 = 8;
int pin2 = 11;
int pin3 = 12;
int pin4 = 13;
int fanPin = 13;

/*  general variables */
bool waitingMsg = false;
int messageSent = 0;


void sendToWifiModule(char* topic, char* message){   
        wifiMessage.write(topic);
        wifiMessage.write(' ');
        wifiMessage.write(message);
        wifiMessage.write('\n');
}
void sendToWifiModule(String topic, String message){   

        char topicArr[topic.length()];
        char messageArr[message.length()];
        topic.toCharArray(topicArr, topic.length());
        message.toCharArray(messageArr, message.length());        
        wifiMessage.write(topicArr);
        wifiMessage.write(' ');
        wifiMessage.write(messageArr);
        wifiMessage.write('\n');
}
void messageHandler(String topic, String message) {  
        
        if(topic == "/smarthouse/temp/state"){
          if(message == "get"){
            Serial.println("will send temp");
          }
        }else if(topic == "/smarthouse/light/state"){
          if(message == "true"){
            Serial.println("Turning on light");
          }else if(message == "false"){
            Serial.println("Turning off light");
          }
        }
        
}

String getWifiMessage(){
  String message = "";
  char part = "";
  while(wifiMessage.available()) {
                part = ((char)wifiMessage.read());
                if(part == '\n')
                        break; 
                message += part;
                delay(5);
        }
        
        Serial.println("received: " + message);
        return message;
}

 String getSubstring(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
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
void pinSetup(){
        pinMode(pin1, OUTPUT);
        pinMode(pin2, OUTPUT);
        pinMode(pin3, OUTPUT);
        pinMode(pin4, OUTPUT);
        pinMode(fanPin, OUTPUT);
}

void setup(){

        pinSetup();
        
        turnOffLight();

        Serial.begin(9600);
        wifiMessage.begin(4800);
        Serial.println("Connection sucessful");

}

void loop(){

 if (wifiMessage.available()){
    //Serial.println(getWifiMessage());
    String receivedData = getWifiMessage();
    
    String topic = getSubstring(receivedData, ' ', 0);
    String message = getSubstring(receivedData, ' ', 1);
    messageHandler(topic, message);
 }


  //  Serial.write(wifiMessage.read());
    
      //  if(wifiMessage.available()) 
       //         messageHandler(receivedTopicAndMessage());
        
}
