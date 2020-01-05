void alarmOff(){
    Serial.println("Lights off ");
   digitalWrite(8, LOW); 
   digitalWrite(11, LOW); 
   digitalWrite(12, LOW); 
   digitalWrite(13, LOW); 
}
 
void alarmOn(){
  Serial.println("alarm on");
   digitalWrite(8, LOW); 
   digitalWrite(11, LOW); 
   digitalWrite(12, HIGH); 
   digitalWrite(13, LOW); 

   }
 
void burglarAlarmLampOff(){
  Serial.println("Alarm lamp off");
   digitalWrite(8, HIGH); 
   digitalWrite(11, HIGH ); 
   digitalWrite(12, HIGH); 
   digitalWrite(13, LOW ); 
   }
    
void burglarAlarmLampOn(){
    Serial.println("ALarm lamp on");
   digitalWrite(8, HIGH); 
   digitalWrite(11, HIGH ); 
   digitalWrite(12, LOW); 
   digitalWrite(13, LOW ); 
   }    
 
void RadiatorOneOff(){
    Serial.println("radiator 1 off");
   digitalWrite(8, HIGH); 
   digitalWrite(11, LOW); 
   digitalWrite(12, HIGH); 
   digitalWrite(13, HIGH); 
   }    

void RadiatorOneOn(){
   Serial.println("radiator 2 on");
   digitalWrite(8, HIGH); 
   digitalWrite(11, LOW); 
   digitalWrite(12, LOW); 
   digitalWrite(13, HIGH); 
}

 
void RadiatorTwoOff(){
  Serial.println("radiator 2 off");
   digitalWrite(8, LOW); 
   digitalWrite(11, HIGH); 
   digitalWrite(12, HIGH); 
   digitalWrite(13, HIGH); 
}
    
void RadiatorTwoOn(){
  Serial.println("heat el 2 on");
   digitalWrite(8, LOW); 
   digitalWrite(11, HIGH); 
   digitalWrite(12, LOW); 
   digitalWrite(13, HIGH); 
   }    
   
void indoorLightOff(){
  Serial.println("indoor lights off");
   digitalWrite(8, LOW); 
   digitalWrite(11, HIGH); 
   digitalWrite(12, HIGH); 
   digitalWrite(13, LOW); 

   }    
 
void indoorLightOn(){
  Serial.println("indoor lights on");
   digitalWrite(8, LOW); 
   digitalWrite(11, HIGH); 
   digitalWrite(12, LOW); 
   digitalWrite(13, LOW); 

   }    
 
void outdoorLightOff(){
  Serial.println("outdoor lights off");
   digitalWrite(8, HIGH); 
   digitalWrite(11, HIGH); 
   digitalWrite(12, HIGH); 
   digitalWrite(13, HIGH); 

   }    
 
void outdoorLightOn(){
  Serial.println("outdoor lights on");
   digitalWrite(8, HIGH); 
   digitalWrite(11, HIGH); 
   digitalWrite(12, LOW); 
   digitalWrite(13, HIGH); 

   }
    
void timerOneOff(){
  Serial.println("t1 off");
   digitalWrite(8, LOW); 
   digitalWrite(11, LOW); 
   digitalWrite(12, HIGH); 
   digitalWrite(13, HIGH); 

   }
       
void timerOneOn(){
  Serial.println("t1 on");
   digitalWrite(8, LOW); 
   digitalWrite(11, LOW); 
   digitalWrite(12, LOW); 
   digitalWrite(13, HIGH);

   }
    
void timerTwoOff(){
  Serial.println("t2 off");
   digitalWrite(8, HIGH); 
   digitalWrite(11, LOW); 
   digitalWrite(12, HIGH); 
   digitalWrite(13, LOW); 

   }    

void timerTwoOn(){
  Serial.println("t2 on");
   digitalWrite(8, HIGH); 
   digitalWrite(11, LOW); 
   digitalWrite(12, LOW); 
   digitalWrite(13, LOW); 

   }
