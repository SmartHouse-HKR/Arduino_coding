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

int readingWindow;
int readingFire;
int readingStove;
int readingWater;
int readingWindowLast=0;
int readingFireLast=0;
int readingStoveLast=0;
int readingWaterLast=0;

int doorValue;
int doorValueLast

char rx_byte = 0;
int sensorValue = 0;

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

  Serial.begin(9600);

}  

void loop() {  

  if(Serial.available()  > 0){
    rx_byte = Serial.read();
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

  digitalWrite(fan, HIGH);
  delayMicroseconds(500); // Approximately 50% duty cycle @ 1KHz
  digitalWrite(fan, LOW);
  delayMicroseconds(1000 - 500);

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
   digitalWrite(12, LOW); 
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
