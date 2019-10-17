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
}  

void loop() {
  
  switchStateFA = digitalRead(2);
  switchStateBA = digitalRead(3);
  switchStateWL = digitalRead(4);
  switchStateO = digitalRead(5);
  switchStateW = digitalRead(6);
  switchStatePC = digitalRead(7);

  if (switchStateFA == HIGH) {
    alarmOn();
  }
  else { 
    alarmOff();
}

 if (switchStateBA == HIGH) {
    alarmOn();
    burglarAlarmLampOn();
      }
  else { 
    alarmOff();
    burglarAlarmLampOff();{
}

  if (switchStateWL == HIGH) {
    alarmOn();
      }
  else { 
    alarmOff();
}  

if (switchStateO == HIGH) {
    
      }
  else { 
    
}

if (switchStateW == HIGH) {
    alarmOn();
      }
  else { 
    alarmOff();
}  

if (switchStatePC == HIGH) {
    alarmOn();
      }
  else { 
    alarmOff();
  }

 tempAirFirst = analogRead(tempFirstSens);
 tempAirFirst = (tempAirFirst / 1024.0)*5000;
 tempAirFirst =  tempAirFirst / 10;

 if (tempAirFirst < 15.00){
  heatingElementOneOn();
 }
 else if(tempAirFirst > 20.00){
  heatingElementOneOff();
 }

 tempAirSecond = analogRead(tempSecondSens);
 tempAirSecond = (tempAirSecond / 1024.0)*5000;
 tempAirSecond =  tempAirSecond / 10;
  
if (tempAirSecond < 15.00){
  heatingElementTwoOn();
 }
 else if(tempAirSecond > 20.00){
  heatingElementTwoOff();
 }
 
 delay(1000);

}}

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
