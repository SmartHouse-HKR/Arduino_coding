#include <SMT160.h>
#include <SoftwareSerial.h>
SoftwareSerial wifiMessage(A4,A5);

// Analog pin setup
const int elecConsumption = A0;
const int tempFirstSens = A1;
const int tempSecondSens = A2;
const int lightSensor = A3;

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

int outdoorLightValue;
int outdoorLightLast;

char rx_byte = 0;
int sensorValue = 0;

float tempAirFirst;
float tempAirSecond; 

bool waitingMsg = false;
int messageSent = 0;

// timer delay
unsigned long previousMillis = 0;
const long intervalWifi = 3000;  

// digital sensor
SMT160 smt160;

// heater sentinel variables
boolean isHeaterOneArmed = false;
boolean isHeaterTwoArmed = false;
int heaterOneTemp;
int heaterTwoTemp;

// outdoor light
boolean isOutdoorLightArmed = true;
boolean outdoorLightState = false; // true = on, false = off
boolean outdoorLightLastState = outdoorLightState;
// alarm
boolean isBurglarAlarmArmed = true;


// fucntion prototypes
void messageHandler(String, String);
String getWifiMessage(void);
String getSubstring(String,char,int);
void sendToWifiModule(String, String);
void alarmOff(long, long, long);
void alarmOn(long, long, long);
void burglarAlarmLampOff(void); 
void burglarAlarmLampOn(void);
void heatingElementOneOn(void);
void heatingElementOneOff(void);
void heatingElementTwoOn(void);
void heatingElementTwoOff(void);
void indroorLightOn(void);
void indroorLightOff(void);
void outdoorLightOn(void);
void outdoorLightOff(void);
void timerOneOn(void);
void timerOneOff(void);
void timerTwoOn(void);
void timerTwoOff(void);

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
 
}  

void loop() {  
  unsigned long currentMillis = millis();

  if(Serial.available()){
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
  
  if(readingWindowLast != readingWindow){
    if(readingWindow == 1){   
      sendToWifiModule("smarthouse/window_alarm/trigger", "true");
      burglarAlarmLampOn();
      alarmOn();
      }
    if(readingWindow == 0){
      sendToWifiModule("smarthouse/window_alarm/trigger", "false");
      burglarAlarmLampOff();
      alarmOff();    
      }
    readingWindowLast=readingWindow;
    }
        
  if(readingFireLast != readingFire){
    if(readingFire == 1){
      sendToWifiModule("smarthouse/fire_alarm/trigger", "true");
      alarmOn();   
      }
    if(readingFire == 0){
      sendToWifiModule("smarthouse/fire_alarm/trigger", "false");
      alarmOff();     
      }
    readingFireLast=readingFire;
    }

  if(readingStoveLast != readingStove){
    if(readingStove == 1){
      sendToWifiModule("smarthouse/oven/state", "true");
      }
    if(readingStove == 0){
      sendToWifiModule("smarthouse/oven/state", "false");    
      }
    readingStoveLast=readingStove;
    }

  if(readingWaterLast != readingWater){
    if(readingWater == 1){
      sendToWifiModule("smarthouse/water_leak/trigger", "true");
      }
    if(readingWater == 0){
      sendToWifiModule("smarthouse/water_leak/trigger", "false");
      }
    readingWaterLast=readingWater;
    }  
  
//___ Lights ___

  if(isOutdoorLightArmed){
    sensorValue = analogRead(lightSensor);
      if(sensorValue < 100){
         outdoorLightState = true;
    }else {
       outdoorLightState = false;
      }

       if(outdoorLightLastState != outdoorLightState){
        if(outdoorLightState){
          outdoorLightOn();
          }else{
          outdoorLightOff();
            }
         }
      outdoorLightLastState = outdoorLightState;   
    }
 //___ Alarms ___

if(isBurglarAlarmArmed){
  doorValue = digitalRead(burglarAlarmSensor);

if(doorValueLast != doorValue){
if(doorValue == 0){
   burglarAlarmLampOn();
          alarmOn();
        }if(doorValue == 1){
           burglarAlarmLampOff();
    alarmOff();   
    }  
    doorValueLast = doorValue;
        }
}

//___ Heating ___

  tempAirFirst = analogRead(tempFirstSens);
  tempAirFirst = (tempAirFirst / 1024.0)*5000;
  tempAirFirst =  tempAirFirst / 10;

  if(isHeaterOneArmed){
    if (tempAirFirst <= (heaterOneTemp)){
      heatingElementOneOn();
      }
    else if(tempAirFirst >= (heaterOneTemp + 3)){
      heatingElementOneOff();
      }
    }

  tempAirSecond = analogRead(tempSecondSens);
  tempAirSecond = (tempAirSecond / 1024.0)*5000;
  tempAirSecond =  tempAirSecond / 10;

  if(isHeaterTwoArmed){
    if (tempAirSecond <= (heaterTwoTemp)){
      heatingElementTwoOn();
      }
    else if(tempAirSecond >= (heaterTwoTemp + 3)){
      heatingElementTwoOff();
      }
    }

//digital temp sensor
  if (currentMillis - previousMillis >= intervalWifi){
  int temp = smt160.getTemp(tempSensorOutside);
// if sensor failed getTemp return 0xffff
  if(temp != 0xffff){
    String extTemp =  String(temp/100);
    sendToWifiModule("smarthouse/outdoor_temperature/value", "extTemp"); 
    }   
}

//___ Volatge ___
 if (currentMillis - previousMillis >= intervalWifi){
  int sensorValue = analogRead(elecConsumption);
  String voltage =  String(sensorValue * (5.0 / 1023.0));
  sendToWifiModule("smarthouse/voltage/value", "voltage");
  }

/*if(rx_byte == '1'){
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
*/
   if (currentMillis - previousMillis >= intervalWifi){
      previousMillis = currentMillis;
    }  
}
