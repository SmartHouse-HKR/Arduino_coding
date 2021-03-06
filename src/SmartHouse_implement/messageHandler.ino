boolean stringToBoolean(String);


void messageHandler(String topic, String message) {
  if(topic == "smarthouse/temp/state"){
    if(message == "get"){
      Serial.println("will send temp");
      }
    }
        
//indoor lights on or off
  else if(topic == "smarthouse/indoor_light/state"){
    if(message == "on"){
      indoorLightOn();
      }
      else if(message == "off"){
        indoorLightOff();
        }
      }

//Outdoor light on or off    
   else if(topic == "smarthouse/outdoor_light/state"){
      isOutdoorLightArmed =  stringToBoolean(message);
   }
//Heater One
  else if (topic == "smarthouse/heater_1/value" ){
    heaterOneTemp = message.toInt();
    }
     
  else if(topic == "smarthouse/heater_1/state"){
      isHeaterOneArmed =  stringToBoolean(message);
    }

//Heater Two     
  else if (topic == "smarthouse/heater_2/value" ){
    heaterTwoTemp = message.toInt();
    } 
    
  else if(topic == "smarthouse/heater_2/state"){
    isHeaterTwoArmed =  stringToBoolean(message);
    }
    
  else if(topic == "smarthouse/burglar_alarm/state"){
    isBurglarAlarmArmed =  stringToBoolean(message);
    }

//Fan
  else if(topic == "smarthouse/fan/speed"){
    if(message == "0"){
      digitalWrite(fan, LOW);
      }
      else if(message == "50"){
        analogWrite(fan, 127);
        }
        else if(message == "75"){
        analogWrite(fan, 191);
        }
        else if(message == "100"){
        analogWrite(fan, 255);
        }  
  } 
}

boolean stringToBoolean(String message){
  boolean returnVal = false; 
  if(message == "on"){
    returnVal  = true;
    }
  
  return false;
  }
