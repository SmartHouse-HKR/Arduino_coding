void alarmOff(){
   digitalWrite(8, LOW); 
   digitalWrite(11, LOW); 
   digitalWrite(12, LOW); 
   digitalWrite(13, LOW); 
   delay(100);
}
 
void alarmOn(){
   digitalWrite(8, LOW); 
   digitalWrite(11, LOW); 
   digitalWrite(12, HIGH); 
   digitalWrite(13, LOW); 
   delay(100);
}
 
void burglarAlarmLampOff(){
   digitalWrite(8, HIGH); 
   digitalWrite(11, HIGH ); 
   digitalWrite(12, HIGH); 
   digitalWrite(13, LOW ); 
   delay(100);
}
    
void burglarAlarmLampOn(){
   digitalWrite(8, HIGH); 
   digitalWrite(11, HIGH ); 
   digitalWrite(12, LOW); 
   digitalWrite(13, LOW ); 
   delay(100);
}    
 
void heatingElementOneOff(){
   digitalWrite(8, HIGH); 
   digitalWrite(11, LOW); 
   digitalWrite(12, HIGH); 
   digitalWrite(13, HIGH); 
   delay(100);
}    

void heatingElementOneOn(){
   digitalWrite(8, HIGH); 
   digitalWrite(11, LOW); 
   digitalWrite(12, LOW); 
   digitalWrite(13, HIGH); 
   delay(100);
}
 
void heatingElementTwoOff(){
   digitalWrite(8, LOW); 
   digitalWrite(11, HIGH); 
   digitalWrite(12, HIGH); 
   digitalWrite(13, HIGH); 
   delay(100);
}
    
void heatingElementTwoOn(){
   digitalWrite(8, LOW); 
   digitalWrite(11, HIGH); 
   digitalWrite(12, LOW); 
   digitalWrite(13, HIGH); 
   delay(100);
}    

void indoorLightOff(){
   digitalWrite(8, LOW); 
   digitalWrite(11, HIGH); 
   digitalWrite(12, HIGH); 
   digitalWrite(13, LOW); 
   delay(100);
}    
 
void indoorLightOn(){
   digitalWrite(8, LOW); 
   digitalWrite(11, HIGH); 
   digitalWrite(12, LOW); 
   digitalWrite(13, LOW); 
   delay(100);
}    
 
void outdoorLightOff(){
   digitalWrite(8, HIGH); 
   digitalWrite(11, HIGH); 
   digitalWrite(12, HIGH); 
   digitalWrite(13, HIGH); 
   delay(100);
}    
 
void outdoorLightOn(){
   digitalWrite(8, HIGH); 
   digitalWrite(11, HIGH); 
   digitalWrite(12, LOW); 
   digitalWrite(13, HIGH); 
   delay(100);
}
    
void timerOneOff(){
   digitalWrite(8, LOW); 
   digitalWrite(11, LOW); 
   digitalWrite(12, HIGH); 
   digitalWrite(13, HIGH); 
   delay(100);
}
    
void timerOneOn(){
   digitalWrite(8, LOW); 
   digitalWrite(11, LOW); 
   digitalWrite(12, LOW); 
   digitalWrite(13, HIGH);
   delay(100);
}
    
void timerTwoOff(){
   digitalWrite(8, HIGH); 
   digitalWrite(11, LOW); 
   digitalWrite(12, HIGH); 
   digitalWrite(13, LOW); 
   delay(100);
}    

void timerTwoOn(){
   digitalWrite(8, HIGH); 
   digitalWrite(11, LOW); 
   digitalWrite(12, LOW); 
   digitalWrite(13, LOW); 
   delay(100);
}
