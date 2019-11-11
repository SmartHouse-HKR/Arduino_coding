int elecConsumption = A0;
int tempFirstSens = A1;
int tempSecondSens = A2;
int lightSensor = A3;

const byte fireAlarmSwitch = 2;
const byte burglarAlarmSensor = 3;
const byte waterLeakSwitch = 4; 
const byte ovenSwitch = 5;
const byte windowOpenSwitch = 6;
const byte powerCut = 7;
const byte tempSensorOutside = 9;
const byte fan = 10;

//int switchStateFA = 0;
//int sensorStateBA = 0;
int switchStateWL = 0;
int switchStateO = 0;
int switchStateW = 0;
int sensorStatePC = 0;

char rx_byte = 0;

volatile boolean burglarArmInterrupt;
volatile boolean fireAlarmInterrupt;

float tempAirFirst;
float tempAirSecond; 

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

  attachInterrupt(digitalPinToInterrupt(fireAlarmSwitch), alarmOnSubRoutine, CHANGE);

  attachInterrupt(digitalPinToInterrupt(burglarAlarmSensor), burglarsAfoot, FALLING);

  digitalWrite(fireAlarmSwitch, LOW);
  digitalWrite(burglarAlarmSensor, HIGH);

  Serial.begin(9600);
}  

void loop() {
  
//  switchStateFA = digitalRead(fireAlarmSwitch);
//  sensorStateBA = digitalRead(burglarAlarmSensor);
  switchStateWL = digitalRead(waterLeakSwitch);
  switchStateO = digitalRead(ovenSwitch);
  switchStateW = digitalRead(windowOpenSwitch);
  sensorStatePC = digitalRead(powerCut);

  

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

  if(Serial.available()  > 0){
    rx_byte = Serial.read();
  }

//  sensorValue = analogRead(lightSensor); // read the value from the sensor
//  Serial.println(sensorValue); //prints the values coming from the sensor on the screen

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

  if(fireAlarmInterrupt){
alarmOn();
    }else {
      alarmOff();
      }

  digitalWrite(fan, HIGH);
  delayMicroseconds(500); // Approximately 50% duty cycle @ 1KHz
  digitalWrite(fan, LOW);
  delayMicroseconds(1000 - 500);

}

void alarmOff(){
   digitalWrite(8, LOW); 
   digitalWrite(11, LOW); 
   digitalWrite(12, LOW); 
   digitalWrite(13, LOW); 
}
 
void alarmOn(){
   digitalWrite(8, LOW); 
   digitalWrite(11, LOW); 
   digitalWrite(12, HIGH); 
   digitalWrite(13, LOW); 
}
 
void burglarAlarmLampOff(){
   digitalWrite(8, HIGH); 
   digitalWrite(11, HIGH ); 
   digitalWrite(12, HIGH); 
   digitalWrite(13, LOW ); 
}
    
void burglarAlarmLampOn(){
   digitalWrite(8, HIGH); 
   digitalWrite(11, HIGH ); 
   digitalWrite(12, LOW); 
   digitalWrite(13, LOW ); 
}    
 
void heatingElementOneOff(){
   digitalWrite(8, HIGH); 
   digitalWrite(11, LOW); 
   digitalWrite(12, HIGH); 
   digitalWrite(13, HIGH); 
}    

void heatingElementOneOn(){
   digitalWrite(8, HIGH); 
   digitalWrite(11, LOW); 
   digitalWrite(12, LOW); 
   digitalWrite(13, HIGH); 
}
 
void heatingElementTwoOff(){
   digitalWrite(8, LOW); 
   digitalWrite(11, HIGH); 
   digitalWrite(12, HIGH); 
   digitalWrite(13, HIGH); 
}
    
void heatingElementTwoOn(){
   digitalWrite(8, LOW); 
   digitalWrite(11, HIGH); 
   digitalWrite(12, LOW); 
   digitalWrite(13, HIGH); 
}    

void indoorLightOff(){
   digitalWrite(8, LOW); 
   digitalWrite(11, HIGH); 
   digitalWrite(12, LOW); 
   digitalWrite(13, LOW); 
}    
 
void indoorLightOn(){
   digitalWrite(8, HIGH); 
   digitalWrite(11, LOW); 
   digitalWrite(12, HIGH); 
   digitalWrite(13, HIGH); 
}    
 
void outdoorLightOff(){
   digitalWrite(8, LOW); 
   digitalWrite(11, HIGH); 
   digitalWrite(12, LOW); 
   digitalWrite(13, LOW); 
}    
 
void outdoorLightOn(){
   digitalWrite(8, HIGH); 
   digitalWrite(11, HIGH); 
   digitalWrite(12, LOW); 
   digitalWrite(13, HIGH); 
}
    
void timerOneOff(){
   digitalWrite(8, LOW); 
   digitalWrite(11, LOW); 
   digitalWrite(12, HIGH); 
   digitalWrite(12, HIGH); 
}
    
void timerOneOn(){
   digitalWrite(8, LOW); 
   digitalWrite(11, LOW); 
   digitalWrite(12, LOW); 
   digitalWrite(12, HIGH);
}
    
void timerTwoOff(){
   digitalWrite(8, HIGH); 
   digitalWrite(11, LOW); 
   digitalWrite(12, HIGH); 
   digitalWrite(12, LOW); 
}    

void timerTwoOn(){
   digitalWrite(8, HIGH); 
   digitalWrite(11, LOW); 
   digitalWrite(12, LOW); 
   digitalWrite(12, LOW); 
}
 
void alarmOnSubRoutine(){
  fireAlarmInterrupt = !fireAlarmInterrupt;
}


void burglarsAfoot(){
  alarmOn();
  burglarAlarmLampOn();
}
