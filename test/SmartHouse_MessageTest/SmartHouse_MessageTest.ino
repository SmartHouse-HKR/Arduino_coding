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

String serial_String = " ";
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
void alarmOff();
void alarmOn();
void burglarAlarmLampOff(void);
void burglarAlarmLampOn(void);
void heatingElementOneOn(void);
void heatingElementOneOff(void);
void heatingElementTwoOn(void);
void heatingElementTwoOff(void);
void indoorLightOn(void);
void indoorLightOff(void);
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

        if(Serial.available())
          serialStringHandler(Serial.readString());
                


//___WiFi setup___
        if (wifiMessage.available()) {
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

        if(readingWindowLast != readingWindow) {
                if(readingWindow == 1) {
                        sendToWifiModule("/smarthouse/window_alarm/trigger", "true");
                        burglarAlarmLampOn();
                        alarmOn();
                }
                if(readingWindow == 0) {
                        sendToWifiModule("/smarthouse/window_alarm/trigger", "false");
                        burglarAlarmLampOff();
                        alarmOff();
                }
                readingWindowLast=readingWindow;
        }

        if(readingFireLast != readingFire) {
                if(readingFire == 1) {
                        sendToWifiModule("/smarthouse/fire_alarm/trigger", "true");
                        alarmOn();
                }
                if(readingFire == 0) {
                        sendToWifiModule("/smarthouse/fire_alarm/trigger", "false");
                        alarmOff();
                }
                readingFireLast=readingFire;
        }

        if(readingStoveLast != readingStove) {
                if(readingStove == 1) {
                        sendToWifiModule("/smarthouse/oven/state", "true");
                }
                if(readingStove == 0) {
                        sendToWifiModule("/smarthouse/oven/state", "false");
                }
                readingStoveLast=readingStove;
        }

        if(readingWaterLast != readingWater) {
                if(readingWater == 1) {
                        sendToWifiModule("/smarthouse/water_leak/trigger", "true");
                }
                if(readingWater == 0) {
                        sendToWifiModule("/smarthouse/water_leak/trigger", "false");
                }
                readingWaterLast=readingWater;
        }

//___ Lights ___

   if(isOutdoorLightArmed){
    sensorValue = analogRead(lightSensor);
      if(sensorValue < 17){
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
    if (tempAirFirst <= (heaterOneTemp - 3)){
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
    if (tempAirSecond <= (heaterTwoTemp - 3)){
      heatingElementTwoOn();
      }
    else if(tempAirSecond >= (heaterTwoTemp + 3)){
      heatingElementTwoOff();
      }
    }
    /*
//Heating refactored but untested
   if(isHeaterOneArmed)
      indoorTemperatureControll(heaterOneTemp, getIndoorTemperature(tempFirstSens), 1);
    
   if(isHeaterTwoArmed)
      indoorTemperatureControll(heaterTwoTemp, getIndoorTemperature(tempSecondSens), 2);
    
*/

if (currentMillis - previousMillis >= intervalWifi) {

       //digital temp sensor
  sendToWifiModule("smarthouse/outdoor_temperature/value", getOutsideTemperature());
       //___ Volatge ___
  sendToWifiModule("smarthouse/voltage/value/reply",getVoltage());
}

}

String getOutsideTemperature(){
     int temp = smt160.getTemp(tempSensorOutside);
   // if sensor failed getTemp return 0xffff
     if(temp == 0xffff)
      return "null";
   
    return  String(temp/100);
    }
    
float getIndoorTemperature(const int pin){
     float temp = analogRead(pin);
     return ((temp / 1024.0)*500);
}

void indoorTemperatureControll(int presetTemp, float currentTemp, int element){
      if (currentTemp <= (presetTemp - 3)){
      if(element = 1) heatingElementOneOn();
      else heatingElementTwoOn();
      }
    else if(tempAirFirst >= (heaterOneTemp + 3)){
      if(element = 1) heatingElementOneOff();
      else heatingElementTwoOff();
      }
}

String getVoltage(){
                int sensorValue = analogRead(elecConsumption);
                return  String(sensorValue * (5.0 / 1023.0));
        }

void serialStringHandler(String serial_String){
  
        if(serial_String != " ")
        Serial.print(serial_String);
        if(serial_String == "1\n") {
                indoorLightOn();
        }

        else if(serial_String == "2\n") {
                indoorLightOff();
        }

        else if(serial_String == "3\n") {
                outdoorLightOn();
        }

        else if(serial_String == "4\n") {
                outdoorLightOff();
        }

        else if(serial_String == "5\n") {
                alarmOn();
        }

        else if(serial_String == "6\n") {
                alarmOff();
        }

        else if(serial_String == "7\n") {
                burglarAlarmLampOn();
        }

        else if(serial_String == "8\n") {
                burglarAlarmLampOff();
        }

        else if(serial_String == "9\n") {
                heatingElementOneOn();
        }

        else if(serial_String == "0\n") {
                heatingElementOneOff();
        }

        else if(serial_String == "q\n") {
                heatingElementTwoOn();
        }

        else if(serial_String == "w\n") {
                heatingElementTwoOff();
        }

        else if(serial_String == "a\n") {
                timerOneOn();
        }

        else if(serial_String == "s\n") {
                timerOneOff();
        }
        else if(serial_String == "light\n") {
                isOutdoorLightArmed = !isOutdoorLightArmed;
                if(isOutdoorLightArmed) Serial.println("OutdoorLight Armed");
                else Serial.println("OutdoorLight Disarmed");
        }

        else if(serial_String == "z\n") {
                timerTwoOn();
        }else if(serial_String == "x\n") {
                timerTwoOff();
        }else if(serial_String.substring(0,3) == "ip ") {
                Serial.println("setting ip to: "+ serial_String.substring(3));
                sendToWifiModule("ip", serial_String.substring(3));
        }else if(serial_String.substring(0,5) == "wifi ") {
                Serial.println("setting wifi to: "+ serial_String.substring(5));
                sendToWifiModule("wifi", serial_String.substring(5));
        } else if(serial_String.substring(0,10) == "wifi_pass ") {
                Serial.println("setting wifi_pass to: "+ serial_String.substring(10));
                sendToWifiModule("wifi_pass", serial_String.substring(10));
        } else if(serial_String.substring(0,6) == "status") {
                Serial.println("getting connectivity status");
                sendToWifiModule("status", "get");
        }
                serial_String = " ";

            
}
