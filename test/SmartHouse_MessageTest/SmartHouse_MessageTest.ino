#include <SMT160.h>
#include <SoftwareSerial.h>
SoftwareSerial wifiMessage(0,1);

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

char rx_byte = 0;
int sensorValue = 0;

float tempAirFirst;
float tempAirSecond; 

bool waitingMsg = false;
int messageSent = 0;


// digital sensor
SMT160 smt160;

// heater sentinel variables
boolean isHeaterOneArmed = false;
boolean isHeaterTwoArmed = false;
int heaterOneTemp;
int heaterTwoTemp;

// outdoor light
boolean isOutdoorLightArmed = true;

// alarm
boolean isBurglarAlarmArmed = true;


// fucntion prototypes
String getWifiMessage(void);
String getSubstring(String,char,int);
void sendToWifiModule(String, String);
void alarmOff(void);
void alarmOn(void);
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
  
  Serial.println("Connection sucessful");

}  

void loop() {  

  if(Serial.available()){
    rx_byte = Serial.read();
    Serial.println(rx_byte);
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
      
      sendToWifiModule("/smarthouse/window_alarm/trigger", "true");
      burglarAlarmLampOn();
      alarmOn();
      }
    if(readingWindow == 0){
      sendToWifiModule("/smarthouse/window_alarm/trigger", "false");
      burglarAlarmLampOff();
      alarmOff();    
      }
    readingWindowLast=readingWindow;
    }
        
  if(readingFireLast != readingFire){
    if(readingFire == 1){
      sendToWifiModule("/smarthouse/fire_alarm/trigger", "true");
      alarmOn();   
      }
    if(readingFire == 0){
      sendToWifiModule("/smarthouse/fire_alarm/trigger", "false");
      alarmOn();     
      }
    readingFireLast=readingFire;
    }

  if(readingStoveLast != readingStove){
    if(readingStove == 1){
      sendToWifiModule("/smarthouse/oven/state", "true");
      }
    if(readingStove == 0){
      sendToWifiModule("/smarthouse/oven/state", "false");    
      }
    readingStoveLast=readingStove;
    }

  if(readingWaterLast != readingWater){
    if(readingWater == 1){
      sendToWifiModule("/smarthouse/water_leak/trigger", "true");
      }
    if(readingWater == 0){
      sendToWifiModule("/smarthouse/water_leak/trigger", "false");
      }
    readingWaterLast=readingWater;
    }  
  
//___ Lights ___

  if(isOutdoorLightArmed){
    sensorValue = analogRead(lightSensor);
//    Serial.println(lightSensor);
      if(sensorValue < 5){
      outdoorLightOn();
      }
    else{
      outdoorLightOff();
      }
    }
//  else{
//    outdoorLightOff();
//    }

 //___ Alarms ___

if(isBurglarAlarmArmed){
  doorValue = digitalRead(burglarAlarmSensor);
  Serial.println(burglarAlarmSensor);
          if(doorValue == 0){
          alarmOn();
          burglarAlarmLampOn();
        }if(doorValue == 1){
          alarmOff();
          burglarAlarmLampOff();
        }
}
//else {
//  burglarAlarmLampOff();
//  }

//___ Heating ___

  tempAirFirst = analogRead(tempFirstSens);
  tempAirFirst = (tempAirFirst / 1024.0)*5000;
  tempAirFirst =  tempAirFirst / 10;

  if(isHeaterOneArmed){
    if (tempAirFirst <= (heaterOneTemp - 3)){
      heatingElementOneOn();
      }
    else if(tempAirFirst >= (heaterOneTemp + 3)){
      heatingElementOneOff();
      }
    }
//    else {
//      heatingElementOneOff();
//      }

  tempAirSecond = analogRead(tempSecondSens);
  tempAirSecond = (tempAirSecond / 1024.0)*5000;
  tempAirSecond =  tempAirSecond / 10;

  if(isHeaterTwoArmed){
    if (tempAirSecond <= (heaterTwoTemp - 3)){
      heatingElementTwoOn();
      }
    else if(tempAirSecond >= (heaterTwoTemp + 3)){
      heatingElementTwoOff();
      }
    }
//    else {
//      heatingElementTwoOff();
//      }

//digital temp sensor
  int temp = smt160.getTemp(tempSensorOutside);
// if sensor failed getTemp return 0xffff
  if(temp != 0xffff){
    String extTemp =  String(temp/100);
    sendToWifiModule("/smarthouse/outdoor_temperature/value", "extTemp");    
    }

//___ Volatge ___

  int sensorValue = analogRead(elecConsumption);
  String voltage =  String(sensorValue * (5.0 / 1023.0));
  sendToWifiModule("/smarthouse/voltage/value", "voltage");

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
  
}
