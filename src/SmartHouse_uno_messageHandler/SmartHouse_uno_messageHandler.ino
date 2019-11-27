#include <SoftwareSerial.h>
SoftwareSerial wifiMessage(4,5);

/*  Pin variables   */
int mux1=12;
int mux2=13;
int mux3=11;
int mux4=8;
int fan=10;

void setup(){

        pinSetup();
        Serial.begin(9600);
        wifiMessage.begin(4800);
        Serial.println("Connection sucessful");
}

void loop(){

        if (wifiMessage.available()) {
                String receivedData = getWifiMessage();
                String topic = getSubstring(receivedData, ' ', 0);
                String message = getSubstring(receivedData, ' ', 1);
                messageHandler(topic, message);
        }
}

void sendToWifiModule(String topic, String message){

        char* messageArray = (char*) malloc(sizeof(char)*message.length()+1);
        char* topicArray = (char*) malloc(sizeof(char)*topic.length()+1);
        message.toCharArray(messageArray, message.length()+1);
        topic.toCharArray(topicArray, topic.length()+1);

        wifiMessage.write(topicArray);
        wifiMessage.write(' ');
        wifiMessage.write(messageArray);
        wifiMessage.write('\n');

        Serial.println("sent to wifi module: " + ((String)topicArray) + " " + ((String)messageArray));
        free(topicArray);
        free(messageArray);
}

void messageHandler(String topic, String message) {

        if(topic == "/smarthouse/temp/state") {
                if(message == "get") {
                        Serial.println("will send temp... eventually");
                }
        }else if(topic == "/smarthouse/light/state") {
                if(message == "true") {
                        lightOn();
                        Serial.println("light turned on");
                        sendToWifiModule("/smarthouse/light/state/reply", "lightsOn");
                }else if(message == "false") {
                        lightOff();
                        Serial.println("light turned off");
                }
        }else if(topic == "/smarthouse/light2/state") {
                if(message == "true") {
                        light2On();
                        Serial.println("light2 turned on");
                        //sendToWifiModule("/smarthouse/light/state", "lightsOn");
                }else if(message == "false") {
                        light2Off();
                        Serial.println("light2 turned off");
                }
        }

}

String getWifiMessage(){
        String message = "";
        char part = ' ';
        while(wifiMessage.available()) {
                part = ((char)wifiMessage.read());
                if(part == '\n')
                        break;
                message += part;
                delay(5);
        }
        Serial.println("received from wifi module: " + message);
        return message;
}

String getSubstring(String data, char separator, int index)
{
        int found = 0;
        int strIndex[] = {0, -1};
        int maxIndex = data.length()-1;

        for(int i=0; i<=maxIndex && found<=index; i++) {
                if(data.charAt(i)==separator || i==maxIndex) {
                        found++;
                        strIndex[0] = strIndex[1]+1;
                        strIndex[1] = (i == maxIndex) ? i+1 : i;
                }
        }
        return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void pinSetup(){
  
        pinMode(mux1, OUTPUT);
        pinMode(mux2, OUTPUT);
        pinMode(mux3, OUTPUT);
        pinMode(mux4, OUTPUT);
        pinMode(fan, OUTPUT);

}

void lightOn(){

        digitalWrite(mux1, LOW);
        digitalWrite(mux2, LOW);
        digitalWrite(mux3, HIGH);
        digitalWrite(mux4, LOW);
}

void lightOff(){

        digitalWrite(mux1, HIGH);
        digitalWrite(mux2, LOW);
        digitalWrite(mux3, HIGH);
        digitalWrite(mux4, LOW);
}

void light2On(){
        digitalWrite(mux1, LOW);
        digitalWrite(mux2, HIGH);
        digitalWrite(mux3, HIGH);
        digitalWrite(mux4, HIGH);

}

void light2Off(){
        digitalWrite(mux1, HIGH);
        digitalWrite(mux2, HIGH);
        digitalWrite(mux3, HIGH);
        digitalWrite(mux4, HIGH);

}
