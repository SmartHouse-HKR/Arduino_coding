#include <SoftwareSerial.h>
SoftwareSerial wifiMessage(0,1);

//switches
int fireSwitch = 2;
int waterSwitch = 4;
int stoveSwitch = 5;
int windowSwitch = 6;

int readingWindow;
int readingFire;
int readingStove;
int readingWater;

int readingWindowLast = 0;
int readingFireLast = 0;
int readingStoveLast = 0;
int readingWaterLast = 0;
int readingLDR = 0;
int readingLDRLast = 0;


//multiplexer pins
int mux1 = 12;
int mux2 = 13;
int mux3 = 11;
int mux4 = 8;

//devices
int fan = 10;

int door = 3;
int doorValue;
int doorValueLast;

int tempSensor = A2;
int tempSensorDigital = 9;

float tempAirDigital;
float tempAir; 


int ldrSensor = A1;
int sensorValue = 0;


//general variables
bool waitingMsg = false;
int messageSent = 0;




void setup(){

        pinSetup();
        Serial.begin(9600);
        wifiMessage.begin(4800);
        Serial.println("Connection sucessful");

}

void loop(){

 if (wifiMessage.available()){
    String receivedData = getWifiMessage();
    String topic = getSubstring(receivedData, ' ', 0);
    String message = getSubstring(receivedData, ' ', 1);
    messageHandler(topic, message);
 }
       
}

//--------------------------------------------------------------------wifi methods START-------------------------------------------------------------------------------------------

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
        //get temp? from what sensor??
        if(topic == "/smarthouse/temp/state"){
          if(message == "get"){
            Serial.println("will send temp");
          }
        }
        
        //indoor lights on or off
        else if(topic == "Smarthome/livingRoom/livingRoomLamp"){
          if(message == "true"){
            indoorLightOn();
          }else if(message == "false"){
            indoorLightOff();
          }
        }

        //indoor lights on or off
        else if(topic == "Smarthome/livingRoom/heater"){
          if(message == "true"){
            heatingRoomOn();
          }else if(message == "false"){
            heatingRoomOff();
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

String getSubstring(String data, char separator, int index) {
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

//--------------------------------------------------------------------wifi methods ENDS-------------------------------------------------------------------------------------------


void pinSetup(){

  //switches
  pinMode(windowSwitch, INPUT);
  pinMode(fireSwitch, INPUT);
  pinMode(stoveSwitch, INPUT);
  pinMode(waterSwitch, INPUT);

  //multiplexer
  pinMode(mux1, OUTPUT);
  pinMode(mux2, OUTPUT);
  pinMode(mux3, OUTPUT);
  pinMode(mux4, OUTPUT);
  pinMode(fan, OUTPUT);

  //devices
  pinMode(fan, OUTPUT);
  pinMode(door, INPUT);

}

//indoor lights on
void indoorLightOn(){
  digitalWrite(mux1, LOW);
  digitalWrite(mux2, LOW);
  digitalWrite(mux3, HIGH);
  digitalWrite(mux4, LOW);
}

//indoor lights off
void indoorLightOff(){
  digitalWrite(mux1, HIGH);
  digitalWrite(mux2, LOW);
  digitalWrite(mux3, HIGH);
  digitalWrite(mux4, LOW);
}

//outdoor lights on
void outdoorLightOn(){
  digitalWrite(mux1, LOW);
  digitalWrite(mux2, HIGH);
  digitalWrite(mux3, HIGH);
  digitalWrite(mux4, HIGH);
}

//outdoor lights off  
void outdoorLightOff(){
  digitalWrite(mux1, HIGH);
  digitalWrite(mux2, HIGH);
  digitalWrite(mux3, HIGH);
  digitalWrite(mux4, HIGH);
}

//alarm on
void alarmOn(){
  digitalWrite(mux1, LOW);
  digitalWrite(mux2, LOW);
  digitalWrite(mux3, HIGH);
  digitalWrite(mux4, HIGH);
  delay(50);
  digitalWrite(mux1, HIGH);
  digitalWrite(mux2, LOW);
  digitalWrite(mux3, LOW);
  digitalWrite(mux4, LOW);
}

//alarm off
void alarmOff(){
  digitalWrite(mux1, LOW);
  digitalWrite(mux2, LOW);
  digitalWrite(mux3, LOW);
  digitalWrite(mux4, LOW);
  delay(50);
  digitalWrite(mux1, HIGH);
  digitalWrite(mux2, LOW);
  digitalWrite(mux3, HIGH);
  digitalWrite(mux4, HIGH);
}

//heating element wind on
void heatingAtticOn(){
  digitalWrite(mux1, LOW);
  digitalWrite(mux2, HIGH);
  digitalWrite(mux3, HIGH);
  digitalWrite(mux4, LOW);
}

//heating element wind on
void heatingAtticOff(){
  digitalWrite(mux1, HIGH);
  digitalWrite(mux2, HIGH);
  digitalWrite(mux3, HIGH);
  digitalWrite(mux4, LOW);
}

//fan on
void fanOn(){
  digitalWrite(fan, HIGH);
}

//fan off
void fanOff(){
  digitalWrite(fan, LOW);
}

//heating on
void heatingRoomOn(){
  digitalWrite(mux1, LOW);
  digitalWrite(mux2, HIGH);
  digitalWrite(mux3, LOW);
  digitalWrite(mux4, HIGH);
}

//heating off
void heatingRoomOff(){
  digitalWrite(mux1, HIGH);
  digitalWrite(mux2, HIGH);
  digitalWrite(mux3, LOW);
  digitalWrite(mux4, HIGH);
}

//led 1 on
void timer1(){
  digitalWrite(mux1, LOW);
  digitalWrite(mux2, HIGH);
  digitalWrite(mux3, LOW);
  digitalWrite(mux4, LOW); 
}

//led 1 off
void timer1Off(){
  digitalWrite(mux1, HIGH);
  digitalWrite(mux2, HIGH);
  digitalWrite(mux3, LOW);
  digitalWrite(mux4, LOW);
}

//led 2 on
void timer2(){
  digitalWrite(mux1, LOW);
  digitalWrite(mux2, LOW);
  digitalWrite(mux3, LOW);
  digitalWrite(mux4, HIGH);
}

//led 2 off
void timer2Off(){
  digitalWrite(mux1, HIGH);
  digitalWrite(mux2, LOW);
  digitalWrite(mux3, LOW);
  digitalWrite(mux4, HIGH);
}

//window switch on
void windowOn(){
  Serial.println("window on");
  sendToWifiModule("Smarthome/livingRoom/livingRoomWindowSensor", "true");
}

//window switch off
void windowOff(){
  Serial.println("window Off");
}

//fire alarm switch on
void fireOn(){
  Serial.println("fire on");
  
}

//fire alarm switch off
void fireOff(){
  Serial.println("fire Off");
}

//stove switch on
void stoveOn(){
  Serial.println("stove on");
}

//stove switch off
void stoveOff(){
  Serial.println("stove Off");
}

//water leakage swtich on
void waterOn(){
  Serial.println("water on");
}

//water leakage swtich off
void waterOff(){
  Serial.println("water Off");
}
