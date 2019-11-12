int elecConsumption = A0;
int tempFirstFlr = A1;
int tempSecondFlr = A2;
int LDR = A3;

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
  // put your main code here, to run repeatedly:

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
