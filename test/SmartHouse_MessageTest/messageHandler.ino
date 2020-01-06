boolean stringToBoolean(String message){
        if(message == "on"||message == "true")
                return true;
        return false;
}



void messageHandler(String topic, String message) {
        //for testing 
        if(topic == "echo") {
                sendToWifiModule("echo/reply",message+"_from_arduino");
        }

//indoor lights on or off
        else if(topic == "smarthouse/indoor_light/state") {
                if(stringToBoolean(message)) indoorLightOn();
                else indoorLightOff();
                
        }

//Outdoor light on or off
        else if(topic == "smarthouse/outdoor_light/state") {
                Serial.println("isOutdoorLightArmed is false");
                if(stringToBoolean(message))outdoorLightOn();
                else outdoorLightOff();
        }

        else if(topic == "smarthouse/outdoor_light/trigger") {

                if(stringToBoolean(message)) {
                   isOutdoorLightArmed = true;
                   Serial.print("is true: " );
                   
                  } else {
                    isOutdoorLightArmed = false;
                    Serial.print("is false: " );
                    }
          
          }
        
//Heater One
        else if (topic == "smarthouse/heater_1/value" ) {
                heaterOneTemp = message.toInt();
        }

        else if(topic == "smarthouse/heater_1/state") {
                isHeaterOneArmed =  stringToBoolean(message);
        }

//Heater Two
        else if (topic == "smarthouse/heater_2/value" ) {
                heaterTwoTemp = message.toInt();
        }

        else if(topic == "smarthouse/heater_2/state") {
     
                isHeaterTwoArmed =  stringToBoolean(message);
        }

        else if(topic == "smarthouse/burglar_alarm/state") {
                isBurglarAlarmArmed =  stringToBoolean(message);
        }

//Fan
        else if(topic == "smarthouse/fan/speed") {
                if(message == "0") {
                        digitalWrite(fan, LOW);
                }
                else if(message == "50") {
                        analogWrite(fan, 127);
                }
                else if(message == "75") {
                        analogWrite(fan, 191);
                }
                else if(message == "100") {
                        analogWrite(fan, 255);
                }
        }
}
