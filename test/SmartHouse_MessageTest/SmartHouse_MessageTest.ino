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
bool isWindowOpen;
bool isFireOn;
bool isStoveOn;
bool isWaterLeaking;
bool isDoorClosed;

String serial_String = " ";

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

        fireCheck();
        windowCheck();
        stoveCheck();
        waterLeakageCheck();

        if(isOutdoorLightArmed)
                outdoorLightCheck();

        //___ Alarms ___
        if(isBurglarAlarmArmed)
                doorCheck();

        //Heating
        if(isHeaterOneArmed)
                indoorTemperatureControll(heaterOneTemp, getIndoorTemperature(tempFirstSens), 1);
        if(isHeaterTwoArmed)
                indoorTemperatureControll(heaterTwoTemp, getIndoorTemperature(tempSecondSens), 2);

        if (currentMillis - previousMillis >= intervalWifi) {

                //digital temp sensor
                sendToWifiModule("smarthouse/outdoor_temperature/value", getOutsideTemperature());
                //___ Volatge ___
                sendToWifiModule("smarthouse/voltage/value/reply",getVoltage());
        }
        if (currentMillis - previousMillis >= intervalWifi) {
                previousMillis = currentMillis;
        }
}

void fireCheck(){

        if(digitalRead(fireAlarmSwitch) == isFireOn)
                return;
        isFireOn = !isFireOn;
        if(isFireOn == true) sendToWifiModule("smarthouse/fire_alarm/trigger", "true");
        else sendToWifiModule("smarthouse/fire_alarm/trigger", "false");
}
void waterLeakageCheck(){

        if(digitalRead(waterLeakSwitch) == isWaterLeaking)
                return;
        isWaterLeaking = !isWaterLeaking;
        if(isWaterLeaking == true) sendToWifiModule("/smarthouse/water_leak/trigger", "true");
        else sendToWifiModule("/smarthouse/water_leak/trigger", "false");

}
void stoveCheck(){

        if(digitalRead(ovenSwitch) == isStoveOn)
                return;
        isStoveOn = !isStoveOn;
        if(isStoveOn == true) sendToWifiModule("/smarthouse/oven/state", "true");
        else sendToWifiModule("/smarthouse/oven/state", "false");
}

void windowCheck(){

        if(digitalRead(windowOpenSwitch) == isWindowOpen)
                return;
        isWindowOpen = !isWindowOpen;
        if(isWindowOpen == true) {
                sendToWifiModule("/smarthouse/window_alarm/trigger", "true");
                burglarAlarmLampOn();
                alarmOn();
        }else {
                sendToWifiModule("/smarthouse/window_alarm/trigger", "false");
                burglarAlarmLampOff();
                alarmOff();
        }
}


void doorCheck(){
  
        if(isDoorClosed == isClosing(burglarAlarmSensor))
         return;
         isDoorClosed != isDoorClosed;
        if(isDoorClosed == false) {
                Serial.println("door is opening");
                burglarAlarmLampOn();
                alarmOn();
        }else if(isDoorClosed == true) {
                Serial.println("door is closing");
                burglarAlarmLampOff();
                alarmOff();
        }
}

bool isClosing(int pin){
        bool readValue = digitalRead(burglarAlarmSensor);
        delay(2);
        readValue = readValue || digitalRead(burglarAlarmSensor);
        delay(2);
        readValue = readValue || digitalRead(burglarAlarmSensor);
        delay(2);
        return readValue;
}

void outdoorLightCheck(){

        int sensorValue = analogRead(lightSensor);
        delay(10);
        if(sensorValue < 50&&outdoorLightState != true) {
                outdoorLightOn();
                outdoorLightState=true;
        }else if(sensorValue > 100&&outdoorLightState != false) {
                outdoorLightOff();
                outdoorLightState=false;
        }
}

String getOutsideTemperature(){
        int temp = smt160.getTemp(tempSensorOutside);
        // if sensor failed getTemp return 0xffff
        if(temp == 0xffff)
                return "null";

        return String(temp/100);
}

float getIndoorTemperature(const int pin){
        float temp = analogRead(pin);
        return ((temp / 1024.0)*500);
}

void indoorTemperatureControll(int presetTemp, float currentTemp, int element){
        if (currentTemp <= (presetTemp - 3)) {
                if(element = 1) heatingElementOneOn();
                else heatingElementTwoOn();
        }
        else if(currentTemp >= (presetTemp + 3)) {
                if(element = 1) heatingElementOneOff();
                else heatingElementTwoOff();
        }
}

String getVoltage(){
        int sensorValue = analogRead(elecConsumption);
        return String(sensorValue * (5.0 / 1023.0));
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
                Serial.println("3fromserial");
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
