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
      sendToWifiModule("/smarthouse/oven/state", "true");
      }
    if(readingWater == 0){
      sendToWifiModule("/smarthouse/oven/state", "false");
      }
    readingWaterLast=readingWater;
    }  
  
//___ Lights ___


  sensorValue = analogRead(lightSensor);
  if(sensorValue < 300){
  outdoorLightOn();
  }

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
/*
  tempAirFirst = analogRead(tempFirstSens);
  tempAirFirst = (tempAirFirst / 1024.0)*5000;
  tempAirFirst =  tempAirFirst / 10;

  if (tempAirFirst < ){
  heatingElementTwoOn();
 }
 else if(tempAirSecond > 20.00){
  heatingElementTwoOff();
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

//___ Volatge ___

  int sensorValue = analogRead(elecConsumption);
  float voltage = sensorValue * (5.0 / 1023.0);
//  Serial.print("Voltage: "); 
//  Serial.println(voltage);

}

//___ Outside the Loop___
