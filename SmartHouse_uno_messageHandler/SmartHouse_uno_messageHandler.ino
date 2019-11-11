#include <SoftwareSerial.h>
SoftwareSerial wifiMessage(0,1);
bool waitingMsg = false;
int messageSent = 0;
int pin1 = 8;
int pin2 = 11;
int pin3 = 12;
int pin4 = 13;
int fanPin = 13;


void sendMessage(String message){

        char charArray[50];
        message.toCharArray(charArray, 49);
        wifiMessage.write(charArray);
        wifiMessage.write('\n');
}

void messageHandler(String returnedMessage) {
        if(returnedMessage.equals("ON")) {
                turnOnLight();
                digitalWrite(fanPin, HIGH);
                Serial.println(returnedMessage);
        }else if(returnedMessage.equals("OFF")) {
                turnOffLight();
                digitalWrite(fanPin, LOW);
        }
}

String* receivedTopicAndMessage(){
        char part;
        String message = "";
        String topic = "";
        bool topicDone  = false;
        while(wifiMessage.available()) {
                part = ((char)wifiMessage.read());

                if (part == ' ')
                        topicDone = true;
                else if(part == '\n' || message != "")
                        break;

                if(topicDone)
                        topic += part;
                else
                        message += part;

                delay(50);
        }
        String* returnArray;
        returnArray[0] = topic;
        returnArray[1] =  message;
        return returnArray;
}

void turnOnLight(){
        digitalWrite(pin1, HIGH);
        digitalWrite(pin2, HIGH);
        digitalWrite(pin3, LOW);
        digitalWrite(pin4, HIGH);
}
void turnOffLight(){
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, HIGH);
        digitalWrite(pin4, HIGH);
}

void setup(){

        pinMode(pin1, OUTPUT);
        pinMode(pin2, OUTPUT);
        pinMode(pin3, OUTPUT);
        pinMode(pin4, OUTPUT);
        pinMode(fanPin, OUTPUT);

        turnOffLight();

        Serial.begin(9600);
        wifiMessage.begin(4800);

}

void loop(){


        if(wifiMessage.available()) {
          String* topicAndMessage = receivedTopicAndMessage();

                messageHandler(topicAndMessage[0]+ " " + topicAndMessage[1]);

        }
}
