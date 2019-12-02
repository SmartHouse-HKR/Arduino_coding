boolean stringToBoolean(String);


void messageHandler(String topic, String message) {
  if(topic == "/smarthouse/temp/state"){
    if(message == "get"){
      Serial.println("will send temp");
      }
    }
        
//indoor lights on or off
  else if(topic == "smarthouse/indoor_light/state"){
    if(message == "true"){
      indoorLightOn();
      }
      else if(message == "false"){
        indoorLightOff();
        }
      }

//Outdoor light on or off    
   else if(topic == "/smarthouse/outdoor_light/state"){
      isOutdoorLightArmed =  stringToBoolean(message);
   }
//Heater One
  else if (topic == "/smarthouse/heater_1/value" ){
    heaterOneTemp = message.toInt();
    }
     
  else if(topic == "/smarthouse/heater_1/state"){
      isHeaterOneArmed =  stringToBoolean(message);
    }

//Heater Two     
  else if (topic == "/smarthouse/heater_2/value" ){
    heaterTwoTemp = message.toInt();
    } 
    
  else if(topic == "/smarthouse/heater_2/state"){
    isHeaterTwoArmed =  stringToBoolean(message);
    }
    
  else if(topic == "/smarthouse/burglar_alarm/state"){
    isBurglarAlarmArmed =  stringToBoolean(message);
    }

//Fan
  else if(topic == "/smarthouse/fan/speed"){
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

String getWifiMessage(){
        String message = "";
        char part = "";
        while(wifiMessage.available()) {
                part = ((char)wifiMessage.read());
                if(part == '\n')
                        break; 
                message += part;
                delay(5);
        }
        
        Serial.println("received: " + message);
        return message;
}

boolean  stringToBoolean(String message){
  boolean returnVal = false; 
  if(message == "on"){
    returnVal  = true;
    }
  
  return false;
  }

String  getSubstring  (String data, char separator, int index) {
        int found = 0;
        int strIndex[] = {0, -1};
        int maxIndex = data.length()-1;

        for(int i=0; i<=maxIndex && found<=index; i++){
            if(data.charAt(i)==separator || i==maxIndex){
              found++;
              strIndex[0] = strIndex[1]+1;
              strIndex[1] = (i == maxIndex) ? i+1 : i;
            }
        }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}  
