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
  else if(topic == "smarthouse/outdoor_light/state"){
    if(message == "true"){
      outdoorLightOn();
      }
      else if(message == "false"){
        outdoorLightOff();
        }
      }  

//Heater one
  else if(topic == "Smarthome/livingRoom/heater"){




//Fan

  else if(topic == "smarthouse/fan/speed"){
    if(message == "0"){
      digitalWrite(fan, LOW);
      }
      else if(message == "50"){
        digitalWrite(fan, HIGH);
        delayMicroseconds(500); // Approximately 50% duty cycle @ 1KHz
        digitalWrite(fan, LOW);
        delayMicroseconds(1000 - 500);
        }
        else if(message == "75"){
        digitalWrite(fan, HIGH);
        delayMicroseconds(750); // Approximately 75% duty cycle @ 1KHz
        digitalWrite(fan, LOW);
        delayMicroseconds(1000 - 750);
        }
        else if(message == "100"){
        digitalWrite(fan, HIGH);
        }  
  } 
}
