#include <SMT160.h>
#include <SoftwareSerial.h>
SoftwareSerial wifiMessage(0,1);

// Analog pin setup
int elecConsumption = A0;
int tempFirstSens = A1;
int tempSecondSens = A2;
int lightSensor = A3;

// Digital pin setup
const byte fireAlarmSwitch = 2;
const byte burglarAlarmSensor = 3;
const byte waterLeakSwitch = 4; 
const byte ovenSwitch = 5;
const byte windowOpenSwitch = 6;
const byte powerCut = 7;
const byte tempSensorOutside = 9;
const byte fan = 10;

// Variables setup
int readingWindow;
int readingFire;
int readingStove;
int readingWater;
int readingWindowLast=0;
int readingFireLast=0;
int readingStoveLast=0;
int readingWaterLast=0;

int doorValue;
int doorValueLast;

char rx_byte = 0;
int sensorValue = 0;

float tempAirFirst;
float tempAirSecond; 

bool waitingMsg = false;
int messageSent = 0;

SMT160 smt160;

void setup() {
 
  pinMode(fireAlarmSwitch, INPUT);
  pinMode(burglarAlarmSensor, INPUT);
  pinMode(waterLeakSwitch, INPUT);
  pinMode(ovenSwitch, INPUT);
  pinMode(windowOpenSwitch, INPUT); 
  pinMode(powerCut, INPUT);
  pinMode(tempSensorOutside, INPUT);
  pinMode(fan, OUTPUT); 

  pinMode(8, OUTPUT); //MUX1
  pinMode(11, OUTPUT); //MUX2
  pinMode(12, OUTPUT); //MUX3
  pinMode(13, OUTPUT); //MUX4

  Serial.begin(9600);

  wifiMessage.begin(4800);
  
  Serial.println("Connection sucessful");

}  

void loop() {  

  if(Serial.available()  > 0){
    rx_byte = Serial.read();
  } 

//___WiFi setup___
  if (wifiMessage.available()){
    String receivedData = getWifiMessage();
    String topic = getSubstring(receivedData, ' ', 0);
    String message = getSubstring(receivedData, ' ', 1);
    messageHandler(topic, message);
    }     

//___Switches___  

  readingWindow=digitalRead(windowOpenSwitch);
  readingFire=digitalRead(fireAlarmSwitch);
  readingStove=digitalRead(ovenSwitch);
  readingWater=digitalRead(waterLeakSwitch);
  
/*  if(readingWindowLast != readingWindow){
    if(readingWindow == 1){
     
         }
    if(readingWindow == 0){
          
        }
        readingWindowLast=readingWindow;
        }
        
  if(readingFireLast != readingFire){
    if(readingFire == 1){
      
      }
      if(readingFire == 0){
          
        }
        readingFireLast=readingFire;

        }

  if(readingStoveLast != readingStove){
    if(readingStove == 1){
          
        }if(readingStove == 0){
          
        }
        readingStoveLast=readingStove;
        }

  if(readingWaterLast != readingWater){
    if(readingWater == 1){
          
        }if(readingWater == 0){
          
        }
         readingWaterLast=readingWater;
        }  
*/

  
//___ Lights ___

  sensorValue = analogRead(lightSensor);
//  Serial.println(sensorValue); 
//  if(sensorValue < 300)

  if(rx_byte == '1'){
    indoorLightOn();
  }

  if(rx_byte == '2'){
    indoorLightOff();
  }

  if(rx_byte == '3'){
    outdoorLightOn();
  }

  if(rx_byte == '4'){
    outdoorLightOff();
  }
  
//___ Alarms ___

  doorValue=digitalRead(burglarAlarmSensor);
  Serial.println(doorValue);
  if(doorValue != doorValueLast){
        if(doorValue == 0){
          alarmOn();
          burglarAlarmLampOn();
        }if(doorValue == 1){
          alarmOff();
          burglarAlarmLampOff();
        }
        doorValueLast=doorValue;
        }

  if(rx_byte == '5'){
    alarmOn();
  }

  if(rx_byte == '6'){
    alarmOff();
  }

  if(rx_byte == '7'){
    burglarAlarmLampOn();
  }

  if(rx_byte == '8'){
    burglarAlarmLampOff();
  }

//___ Heating ___

  tempAirFirst = analogRead(tempFirstSens);
  tempAirFirst = (tempAirFirst / 1024.0)*5000;
  tempAirFirst =  tempAirFirst / 10;

/* if (tempAirFirst < 15.00){
  heatingElementOneOn();
 }
 else if(tempAirFirst > 20.00){
  heatingElementOneOff();
 }
*/

 tempAirSecond = analogRead(tempSecondSens);
 tempAirSecond = (tempAirSecond / 1024.0)*5000;
 tempAirSecond =  tempAirSecond / 10;
  
/*if (tempAirSecond < 15.00){
  heatingElementTwoOn();
 }
 else if(tempAirSecond > 20.00){
  heatingElementTwoOff();
 }
*/ 

//digital thermometer 
  int temp = smt160.getTemp(tempSensorOutside);
// if sensor failed getTemp return 0xffff
  if(temp != 0xffff){
    Serial.println(temp/100);
  }
  
  if(rx_byte == '9'){
    heatingElementOneOn();
  }

  if(rx_byte == '0'){
    heatingElementOneOff();
  }
  
  if(rx_byte == 'q'){
    heatingElementTwoOn();
  }
  
  if(rx_byte == 'w'){
    heatingElementTwoOff();
  }

//___ Timers ___
  
  if(rx_byte == 'a'){
    timerOneOn();
  }
  
  if(rx_byte == 's'){
  timerOneOff();
  }

  if(rx_byte == 'z'){
  timerTwoOn();
  }
  
  if(rx_byte == 'x'){
  timerTwoOff();
  }  

//___ Fan ___

/*  digitalWrite(fan, HIGH);
  delayMicroseconds(500); // Approximately 50% duty cycle @ 1KHz
  digitalWrite(fan, LOW);
  delayMicroseconds(1000 - 500);
*/

//___ Volatge ___

  int sensorValue = analogRead(elecConsumption);
  float voltage = sensorValue * (5.0 / 1023.0);
//  Serial.print("Voltage: "); 
//  Serial.println(voltage);

}

//___ Outside the Loop___

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
      }
      else if(message == "false"){
        indoorLightOff();
        }
      }

//Outdoor light on or off    
  else if(topic == "Smarthome/outside/outsideSecuirtyLight"){
    if(message == "true"){
      outdoorLightOn();
      }
      else if(message == "false"){
        outdoorLightOff();
        }
      }  

//Heater one on or off
  else if(topic == "Smarthome/livingRoom/heater"){
    if(message == "true"){
      heatingElementOneOn();
      }
      else if(message == "false"){
        heatingElementOneOff();
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

void alarmOff(){
   digitalWrite(8, LOW); 
   digitalWrite(11, LOW); 
   digitalWrite(12, LOW); 
   digitalWrite(13, LOW); 
   delay(10);
}
 
void alarmOn(){
   digitalWrite(8, LOW); 
   digitalWrite(11, LOW); 
   digitalWrite(12, HIGH); 
   digitalWrite(13, LOW); 
   delay(10);
}
 
void burglarAlarmLampOff(){
   digitalWrite(8, HIGH); 
   digitalWrite(11, HIGH ); 
   digitalWrite(12, HIGH); 
   digitalWrite(13, LOW ); 
   delay(10);
}
    
void burglarAlarmLampOn(){
   digitalWrite(8, HIGH); 
   digitalWrite(11, HIGH ); 
   digitalWrite(12, LOW); 
   digitalWrite(13, LOW ); 
   delay(10);
}    
 
void heatingElementOneOff(){
   digitalWrite(8, HIGH); 
   digitalWrite(11, LOW); 
   digitalWrite(12, HIGH); 
   digitalWrite(13, HIGH); 
   delay(10);
}    

void heatingElementOneOn(){
   digitalWrite(8, HIGH); 
   digitalWrite(11, LOW); 
   digitalWrite(12, LOW); 
   digitalWrite(13, HIGH); 
   delay(10);
}
 
void heatingElementTwoOff(){
   digitalWrite(8, LOW); 
   digitalWrite(11, HIGH); 
   digitalWrite(12, HIGH); 
   digitalWrite(13, HIGH); 
   delay(10);
}
    
void heatingElementTwoOn(){
   digitalWrite(8, LOW); 
   digitalWrite(11, HIGH); 
   digitalWrite(12, LOW); 
   digitalWrite(13, HIGH); 
   delay(10);
}    

void indoorLightOff(){
   digitalWrite(8, LOW); 
   digitalWrite(11, HIGH); 
   digitalWrite(12, HIGH); 
   digitalWrite(13, LOW); 
   delay(10);
}    
 
void indoorLightOn(){
   digitalWrite(8, LOW); 
   digitalWrite(11, HIGH); 
   digitalWrite(12, LOW); 
   digitalWrite(13, LOW); 
   delay(10);
}    
 
void outdoorLightOff(){
   digitalWrite(8, HIGH); 
   digitalWrite(11, HIGH); 
   digitalWrite(12, HIGH); 
   digitalWrite(13, HIGH); 
   delay(10);
}    
 
void outdoorLightOn(){
   digitalWrite(8, HIGH); 
   digitalWrite(11, HIGH); 
   digitalWrite(12, LOW); 
   digitalWrite(13, HIGH); 
   delay(10);
}
    
void timerOneOff(){
   digitalWrite(8, LOW); 
   digitalWrite(11, LOW); 
   digitalWrite(12, HIGH); 
   digitalWrite(13, HIGH); 
   delay(10);
}
    
void timerOneOn(){
   digitalWrite(8, LOW); 
   digitalWrite(11, LOW); 
   digitalWrite(12, LOW); 
   digitalWrite(13, HIGH);
   delay(10);
}
    
void timerTwoOff(){
   digitalWrite(8, HIGH); 
   digitalWrite(11, LOW); 
   digitalWrite(12, HIGH); 
   digitalWrite(13, LOW); 
   delay(10);
}    

void timerTwoOn(){
   digitalWrite(8, HIGH); 
   digitalWrite(11, LOW); 
   digitalWrite(12, LOW); 
   digitalWrite(13, LOW); 
   delay(10);
}
