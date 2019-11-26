#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <PubSubClient.h>

SoftwareSerial unoMessager(4,5);
WiFiClient espClient;
PubSubClient client(espClient);

/*  Connection variables  */
String networkSSL = "Ras_the_Moose";
String networkPassword = "12345678";
char* ipAddress = "192.168.43.99";
uint16_t port = 1883;

void setup(){

        Serial.begin(9600);
        unoMessager.begin(4800);
        wifiConnect();
        client.setCallback(callback);
}

void loop(){

        if (!client.connected())
                reconnectMqttServer();


        client.loop();

        if(unoMessager.available()) {
                Serial.println("message from arduino available");
                String receivedData = receivedArduinoMessage();
                String topic = getSubstring(receivedData, ' ', 0);
                String message = getSubstring(receivedData, ' ', 1);
                Serial.println("sending to MQTT, topic: " + topic + ", message: " + message);
                sendToMQTT(topic, message);
        }
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
        client.subscribe("/smarthouse/light2/state");
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
        Serial.println("message received from MQTT, topic: " + MQTT_DATA + ", Topic:  " + topic);
        delay(5);
        sendToArduino(topic, MQTT_DATA);
}

void sendToArduino(char* topicArray, String message){

        char* messageArray = (char*) malloc(sizeof(char)*message.length()+1);
        message.toCharArray(messageArray, message.length()+1);
        unoMessager.write(topicArray);
        unoMessager.write(' ');
        unoMessager.write(messageArray);
        unoMessager.write('\n');
        free(messageArray);
        delay(5);
}

String getSubstring(String data, char separator, int index){
  
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

String receivedArduinoMessage(){
  
        String message = "";
        char part;
        while(unoMessager.available()) {
                part = unoMessager.read();
                if(part == ('\n'))
                        break;
                message.concat(part);
                delay(3);
        }
        return message;
}

void sendToMQTT(String topic,String message){

        char topicCharArray[50];
        topic.toCharArray(topicCharArray,50);
        char messageCharArray[50];
        message.toCharArray(messageCharArray,50);
        client.publish(topicCharArray, messageCharArray);
}
