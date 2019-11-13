#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <PubSubClient.h>

SoftwareSerial unoMessager(D1,D2);
WiFiClient espClient;
PubSubClient client(espClient);

/*  Connection variables  */
String networkSSL = "Ras_the_Moose";
String networkPassword = "12345678";
char* ipAddress = "192.168.43.99";
uint16_t port = 1883;

/*  Pin variables  */
int ledPin = 13;

/*  Other variables  */

char msgmqtt[50];
        bool sendOnce = true;
        char* message = "hey";

char* toCharArr(String string){
  char charArr[50];
  string.toCharArray(charArr, 50);
  return charArr;
}

void reconnectMqttServer() {
        while (!client.connected()) {
                Serial.print("Attempting MQTT wifiConnection...");
                String clientId = "ESP8266Client-";
                clientId += String(random(0xffff), HEX);
                if (client.connect(clientId.c_str())) {
                        Serial.println("connected");
                        subscribeToTopics();
                } else {
                        Serial.print("failed, rc=");
                        Serial.print(client.state());
                        Serial.println(" try again in 5 seconds");
                        delay(5000);
                }
        }
}

void subscribeToTopics(){
  client.subscribe("/smarthouse/temp/state");
  client.subscribe("/smarthouse/light/state");
}

void wifiConnect(){
        WiFi.disconnect();
        delay(3000);
        Serial.println("START");
        WiFi.begin(networkSSL,networkPassword);
        while ((!(WiFi.status() == WL_CONNECTED))) {
                delay(300);
                Serial.print("..");
        }
        
        Serial.println("wifiConnected");
        Serial.println("Your IP is");
        Serial.println((WiFi.localIP().toString()));
        client.setServer( ipAddress, port);
}

void callback(char* topic, byte* payload, unsigned int length) {
        String MQTT_DATA;
        for (int i=0; i<length; i++) {
                MQTT_DATA += (char)payload[i];
        }
        Serial.println("message received from topic: " + MQTT_DATA + ", Topic:  " + topic);
        delay(50);
        sendToArduino(topic, MQTT_DATA);
}



void pinSetup(){
      
   
}

void sendToArduino(char* topic, String message){
          char charArr[50];
          message.toCharArray(charArr, 50);
      
        unoMessager.write(topic);
        unoMessager.write(' ');
        unoMessager.write(charArr);
        unoMessager.write('\n');
}

char** receivedArduinoMessage(){
        char part;
        char* message = "";
        char* topic = "";
        bool topicDone  = false;
        while(unoMessager.available()) {
                part = ((char)unoMessager.read());
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
        char** returnArray;
        returnArray[0] = topic;
        returnArray[1] =  message;
        return returnArray;
}

void sendToMQTT(char** topicAndMessageFromArduino){
        char* topic = topicAndMessageFromArduino[0];
        char* message = topicAndMessageFromArduino[1];
        client.publish(topic, message);
}

void setup(){

        Serial.begin(9600);
        unoMessager.begin(4800);
        pinSetup();
        wifiConnect();
        client.setCallback(callback);

}

void loop()
{

        if (!client.connected())
                reconnectMqttServer();

        client.loop();

        
//        snprintf (msgmqtt, 50, message.c_str());
        if(unoMessager.available())
                sendToMQTT(receivedArduinoMessage());

}
