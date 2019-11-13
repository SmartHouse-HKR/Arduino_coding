#include <SoftwareSerial.h>
SoftwareSerial wifiMessage(0,1);


/*  Pin variables   */
int mux1=12;
int mux2=13;
int mux3=11;
int mux4=8;
int fan=10;

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
            lightOn();
          }else if(message == "false"){
            lightOff();
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

void pinSetup(){
  

pinMode(mux1, OUTPUT);
  pinMode(mux2, OUTPUT);
  pinMode(mux3, OUTPUT);
  pinMode(mux4, OUTPUT);
    pinMode(fan, OUTPUT);

}
void lightOn(){

digitalWrite(mux1, LOW);
  digitalWrite(mux2, LOW);
  digitalWrite(mux3, HIGH);
  digitalWrite(mux4, LOW);
}
void lightOff(){

digitalWrite(mux1, HIGH);
  digitalWrite(mux2, LOW);
  digitalWrite(mux3, HIGH);
  digitalWrite(mux4, LOW);
}

void lightOn2(){
  digitalWrite(mux1, LOW);
  digitalWrite(mux2, HIGH);
  digitalWrite(mux3, HIGH);
  digitalWrite(mux4, HIGH);
  
}
void lightOff2(){
  digitalWrite(mux1, HIGH);
  digitalWrite(mux2, HIGH);
  digitalWrite(mux3, HIGH);
  digitalWrite(mux4, HIGH);
  
}

void setup(){

        pinSetup();

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
