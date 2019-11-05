int elecConsumption = A0;
int tempFirstSens = A1;
int tempSecondSens = A2;
int LDR = A3;

int switchStateFA = 0;
int switchStateBA = 0;
int switchStateWL = 0;
int switchStateO = 0;
int switchStateW = 0;
int switchStatePC = 0;

char rx_byte = 0;

float tempAirFirst;
float tempAirSecond; 

void setup() {
  
  pinMode(0, INPUT); //RX
  pinMode(1, INPUT); //LX
  pinMode(2, INPUT); //Fire alarm on/off
  pinMode(3, INPUT); //Burglar alarm on/off
  pinMode(4, INPUT); //Water leakage on/off
  pinMode(5, INPUT); //Oven on/off
  pinMode(6, INPUT); //Window on/off
  pinMode(7, INPUT); //Power cut on/off
  pinMode(9, INPUT); //Temp outside
  pinMode(10, OUTPUT); //Fan

  pinMode(8, OUTPUT); //MUX1
  pinMode(11, OUTPUT); //MUX2
  pinMode(12, OUTPUT); //MUX3
  pinMode(13, OUTPUT); //MUX4

  Serial.begin(9600);
}  

void loop() {
  
  switchStateFA = digitalRead(2);
  switchStateBA = digitalRead(3);
  switchStateWL = digitalRead(4);
  switchStateO = digitalRead(5);
  switchStateW = digitalRead(6);
  switchStatePC = digitalRead(7);

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

  if(rx_byte == '1'){
    indoorLightingOn();
  }

  if(rx_byte == '2'){
    indoorLightingOff();
  }

  if(rx_byte == '3'){
    outdoorLightOn();
  }

  if(rx_byte == '4'){
    OutdoorLightOff();
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
    heatingElementOneOne();
  }

  if(rx_byte == '0'){
    heatingElementOneOff();
  }
  
  if(rx_byte == 'q'){
    heatingElementTwoOne()();
  }
  
  if(rx_byte == 'w'){
    heatingElementTwoOff());
  }
  
  if(rx_byte == 'a'){
    timerOneOne();
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

  digitalWrite(10, HIGH);
  delayMicroseconds(500); // Approximately 50% duty cycle @ 1KHz
  digitalWrite(10, LOW);
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

void indoorLightingOff(){
   digitalWrite(8, LOW); 
   digitalWrite(11, HIGH); 
   digitalWrite(12, LOW); 
   digitalWrite(13, LOW); 
}    
 
void indoorLightingOn(){
   digitalWrite(8, HIGH); 
   digitalWrite(11, LOW); 
   digitalWrite(12, HIGH); 
   digitalWrite(13, HIGH); 
}    
 
void outdoorLightingOff(){
   digitalWrite(8, LOW); 
   digitalWrite(11, HIGH); 
   digitalWrite(12, LOW); 
   digitalWrite(13, LOW); 
}    
 
void outdoorLightingOn(){
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
