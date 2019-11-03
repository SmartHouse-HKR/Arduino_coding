//Analog pins
int elecConsumption = A0;
int tempFirstSens = A1;
int tempSecondSens = A2;
int LDR = A3;

//Switch setup
int switchStateFA = 0;
int switchStateBA = 0;
int switchStateWL = 0;
int switchStateO = 0;
int switchStateW = 0;
int switchStatePC = 0;

//Temp sensor setup
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

//Digital temp sensor setup
  digitalWrite(9, LOW);
  lastSample = 0;
  sampleSize = 0;
  highCount = 0;
  lastOutput = 0;
  outdoorTemp = 0;

  Serial.begin(9600);
}  

void loop() {

//Switch setup  
  switchStateFA = digitalRead(2);
  switchStateBA = digitalRead(3);
  switchStateWL = digitalRead(4);
  switchStateO = digitalRead(5);
  switchStateW = digitalRead(6);
  switchStatePC = digitalRead(7);

//Fire alarm
  if (switchStateFA == HIGH) {
    alarmOn(100);
  }
  else { 
    alarmOff();
}

//Burglar alarm
 if (switchStateBA == HIGH) {
    alarmOn(100);
    burglarAlarmLampOn(120);
      }
  else { 
    alarmOff();
    burglarAlarmLampOff();
}

//Water leak
  if (switchStateWL == HIGH) {
    alarmOn(100);
      }
  else { 
    alarmOff();
}  

//Oven
/*if (switchStateO == HIGH) {
    
      }
  else { 
    
}*/
//Window
/*if (switchStateW == HIGH) {
    alarmOn(100);
      }
  else { 
    alarmOff();
}  
*/

//Power cut
if (switchStatePC == HIGH) {
    alarmOn(100);
      }
  else { 
    alarmOff();
 }

//Indoor temp sensor #1
  tempAirFirst = analogRead(tempFirstSens);
  tempAirFirst = (tempAirFirst / 1024.0)*5000;
  tempAirFirst =  tempAirFirst / 10;

  Serial.print("tempFirst is: ");
  Serial.println(tempAirFirst); 
  delay(3000);

/* if (tempAirFirst < 15.00){
  heatingElementOneOn(120);
 }
 else if(tempAirFirst > 20.00){
  heatingElementOneOff();
 }*/

//Indoor temp sensor #2
  tempAirSecond = analogRead(tempSecondSens);
  tempAirSecond = (tempAirSecond / 1024.0)*5000;
  tempAirSecond =  tempAirSecond / 10;

  Serial.print("tempSecond is: ");
  Serial.println(tempAirSecond); 
  delay(3000);
  
/*if (tempAirSecond < 15.00){
  heatingElementTwoOn(120);
 }
 else if(tempAirSecond > 20.00){
  heatingElementTwoOff();
 }*/
 
//Outdoor temp sensor
  now = micros();
    if (now - lastOutput > 500000) {
      hcf = highCount;
      ssf = sampleSize;
      outdoorTemp = ((hcf / ssf) -0.32)/0.0047;
      Serial.print("Outdoor temp is: "); 
      Serial.println(outdoorTemp);
      lastOutput = now;
      sampleSize = 0;
      highCount = 0;
    }
    if (now - lastSample > 100) {
      sampleSize++;
      highCount = highCount + digitalRead(9);
      lastSample = now;
    } else {
    delayMicroseconds(10);
  } 

//TESTING

  indoorLightingOn(150);
//  indoorLightingOff();
  outdoorLightingOn(160);
//  outdoorLightingOff();

  timerOneOn(170);
//  timerOneOff();
  timerTwoOn(180);
//  timerTwoOff();

//  heatingElementOneOn(120);
  heatingElementOneOff();
//  heatingElementTwoOn(130);
  heatingElementOneOff();

//Fan
/*  digitalWrite(10, HIGH);
  delayMicroseconds(100); // Approximately 10% duty cycle @ 1KHz
  digitalWrite(13, LOW);
  delayMicroseconds(1000 - 100);
*/

}


void alarmOff(){
   digitalWrite(8, LOW); 
   digitalWrite(11, LOW); 
   digitalWrite(12, LOW); 
   digitalWrite(13, LOW); 
}
 
void alarmOn(int interval){
   static long prevMill = 0;
   if ((millis() - prevMill) >= interval){ 
   prevMill = millis(); 
   digitalWrite(8, LOW); 
   digitalWrite(11, LOW); 
   digitalWrite(12, HIGH); 
   digitalWrite(13, LOW); 
}}
 
void burglarAlarmLampOff(){
   digitalWrite(8, HIGH); 
   digitalWrite(11, HIGH ); 
   digitalWrite(12, HIGH); 
   digitalWrite(13, LOW ); 
}
    
void burglarAlarmLampOn(int interval){
   static long prevMill = 0;
   if ((millis() - prevMill) >= interval){ 
   prevMill = millis(); 
   digitalWrite(8, HIGH); 
   digitalWrite(11, HIGH ); 
   digitalWrite(12, LOW); 
   digitalWrite(13, LOW ); 
}}    
 
void heatingElementOneOff(){
   digitalWrite(8, HIGH); 
   digitalWrite(11, LOW); 
   digitalWrite(12, HIGH); 
   digitalWrite(13, HIGH); 
}    

void heatingElementOneOn(int interval){
   static long prevMill = 0;
   if ((millis() - prevMill) >= interval){ 
   prevMill = millis(); 
   digitalWrite(8, HIGH); 
   digitalWrite(11, LOW); 
   digitalWrite(12, LOW); 
   digitalWrite(13, HIGH); 
}}
 
void heatingElementTwoOff(){
   digitalWrite(8, LOW); 
   digitalWrite(11, HIGH); 
   digitalWrite(12, HIGH); 
   digitalWrite(13, HIGH); 
}
    
void heatingElementTwoOn(int interval){
   static long prevMill = 0;
   if ((millis() - prevMill) >= interval){ 
   prevMill = millis(); 
   digitalWrite(8, LOW); 
   digitalWrite(11, HIGH); 
   digitalWrite(12, LOW); 
   digitalWrite(13, HIGH); 
}}    

void indoorLightingOff(){
   digitalWrite(8, LOW); 
   digitalWrite(11, HIGH); 
   digitalWrite(12, LOW); 
   digitalWrite(13, LOW); 
}    
 
void indoorLightingOn(int interval){
   static long prevMill = 0;
   if ((millis() - prevMill) >= interval){ 
   prevMill = millis(); 
   digitalWrite(8, HIGH); 
   digitalWrite(11, LOW); 
   digitalWrite(12, HIGH); 
   digitalWrite(13, HIGH); 
}}   
 
void outdoorLightingOff(){
   digitalWrite(8, LOW); 
   digitalWrite(11, HIGH); 
   digitalWrite(12, LOW); 
   digitalWrite(13, LOW); 
}    
 
void outdoorLightingOn(int interval){
   static long prevMill = 0;
   if ((millis() - prevMill) >= interval){ 
   prevMill = millis(); 
   digitalWrite(8, HIGH); 
   digitalWrite(11, HIGH); 
   digitalWrite(12, LOW); 
   digitalWrite(13, HIGH); 
}}
    
void timerOneOff(){
   digitalWrite(8, LOW); 
   digitalWrite(11, LOW); 
   digitalWrite(12, HIGH); 
   digitalWrite(12, HIGH); 
}
    
void timerOneOn(int interval){
   static long prevMill = 0;
   if ((millis() - prevMill) >= interval){ 
   prevMill = millis(); 
   digitalWrite(8, LOW); 
   digitalWrite(11, LOW); 
   digitalWrite(12, LOW); 
   digitalWrite(12, HIGH);
}}
    
void timerTwoOff(){
   digitalWrite(8, HIGH); 
   digitalWrite(11, LOW); 
   digitalWrite(12, HIGH); 
   digitalWrite(12, LOW); 
}    

void timerTwoOn(int interval){
   static long prevMill = 0;
   if ((millis() - prevMill) >= interval){ 
   prevMill = millis(); 
   digitalWrite(8, HIGH); 
   digitalWrite(11, LOW); 
   digitalWrite(12, LOW); 
   digitalWrite(12, LOW); 
}}
