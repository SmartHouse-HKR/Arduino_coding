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

char rx_byte = 0;
int sensorValue = 0;

int doorValue;
int doorValueLast;

// volatile boolean burglarArmInterrupt;

// Temp sensor setup
float tempAirFirst;
float tempAirSecond;
unsigned long now;
unsigned long lastSample;
unsigned int sampleSize;
unsigned int highCount;
unsigned long lastOutput;
float outdoorTemp;
float hcf, ssf;

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

//Digital temp sensor setup
  digitalWrite(9, LOW);
  lastSample = 0;
  sampleSize = 0;
  highCount = 0;
  lastOutput = 0;
  outdoorTemp = 0;  

//  attachInterrupt(digitalPinToInterrupt(fireAlarmSwitch), alarmOnSubRoutine, CHANGE);
//  digitalWrite(fireAlarmSwitch, LOW);

  Serial.begin(9600);

}  

void loop() {  

  if(Serial.available()  > 0){
    rx_byte = Serial.read();
  }
 
//___ Lights ___

  sensorValue = analogRead(lightSensor);
//  Serial.println(sensorValue); 
//  if(sensorValue < 300)

  if(rx_byte == '1'){
    indoorLightOn();
    delay(10);
  }

  if(rx_byte == '2'){
    indoorLightOff();
    delay(10);
  }

  if(rx_byte == '3'){
    outdoorLightOn();
  delay(10);
  }

  if(rx_byte == '4'){
    outdoorLightOff();
    delay(10);
  }
  
//___ Alarms ___

  doorValue=digitalRead(burglarAlarmSensor);
//  Serial.println(doorValue);
  if(doorValue != doorValueLast){
      if(doorValue == 0){
        alarmOn();
        }
        if(doorValue == 1){
          alarmOff();
        }
        doorValueLast=doorValue;
        }

  if(rx_byte == '5'){
    alarmOn();
    delay(10);
  }

  if(rx_byte == '6'){
    alarmOff();
    delay(10);
  }

  if(rx_byte == '7'){
    burglarAlarmLampOn();
    delay(10);
  }

  if(rx_byte == '8'){
    burglarAlarmLampOff();
    delay(10);
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

//Outdoor temp sensor
  now = micros();
  if (now - lastOutput > 500000){
      hcf = highCount;
      ssf = sampleSize;
      outdoorTemp = ((1.0 *hcf / ssf) -0.32)/0.0047;
//      Serial.print("Outdoor temp is: "); 
//      Serial.println(outdoorTemp);
      lastOutput = now;
      sampleSize = 0;
      highCount = 0;
    }
    if (now - lastSample > 100) {
      sampleSize++;
      highCount = highCount + digitalRead(tempSensorOutside);
      lastSample = now;
    } 
    else 
    {
    delayMicroseconds(10);
    } 

  if(rx_byte == '9'){
    heatingElementOneOn();
    delay(10);
  }

  if(rx_byte == '0'){
    heatingElementOneOff();
    delay(10);
  }
  
  if(rx_byte == 'q'){
    heatingElementTwoOn();
    delay(10);
  }
  
  if(rx_byte == 'w'){
    heatingElementTwoOff();
    delay(10);
  }

//___ Timers ___
  
  if(rx_byte == 'a'){
    timerOneOn();
    delay(10);
  }
  
  if(rx_byte == 's'){
  timerOneOff();
  delay(10);
  }

  if(rx_byte == 'z'){
  timerTwoOn();
  delay(10);
  }
  
  if(rx_byte == 'x'){
  timerTwoOff();
  delay(10);
  }  

//___ Fan ___
/*
  digitalWrite(fan, HIGH);
  delayMicroseconds(000); // Approximately 50% duty cycle @ 1KHz
  digitalWrite(fan, LOW);
  delayMicroseconds(1000 - 000);
*/
// ___ Volatge ___

  int sensorValue = analogRead(elecConsumption);
  float voltage = sensorValue * (5.0 / 1023.0);
//  Serial.print("Voltage: "); 
//  Serial.println(voltage);

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
   digitalWrite(12, HIGH); 
   digitalWrite(13, LOW); 
}    
 
void indoorLightOn(){
   digitalWrite(8, LOW); 
   digitalWrite(11, HIGH); 
   digitalWrite(12, LOW); 
   digitalWrite(13, LOW); 
}    
 
void outdoorLightOff(){
   digitalWrite(8, HIGH); 
   digitalWrite(11, HIGH); 
   digitalWrite(12, HIGH); 
   digitalWrite(13, HIGH); 
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
   digitalWrite(13, HIGH); 
}
    
void timerOneOn(){
   digitalWrite(8, LOW); 
   digitalWrite(11, LOW); 
   digitalWrite(12, LOW); 
   digitalWrite(13, HIGH);
}
    
void timerTwoOff(){
   digitalWrite(8, HIGH); 
   digitalWrite(11, LOW); 
   digitalWrite(12, HIGH); 
   digitalWrite(13, LOW); 
}    

void timerTwoOn(){
   digitalWrite(8, HIGH); 
   digitalWrite(11, LOW); 
   digitalWrite(12, LOW); 
   digitalWrite(13, LOW); 
}
