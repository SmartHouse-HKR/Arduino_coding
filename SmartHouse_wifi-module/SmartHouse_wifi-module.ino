#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <PubSubClient.h>

SoftwareSerial unoMessage(D2,D3);
WiFiClient espClient;
PubSubClient client(espClient);

String networkSSL = "Ras_the_Moose";
String networkPassword = "12345678";
String ipAddress = "194.47.28.11";
uint16_t port = 1883;
int ledPin = 13;
String message;
char msgmqtt[50];


void reconnectmqttserver() {
        while (!client.connected()) {
                Serial.print("Attempting MQTT connection...");
                String clientId = "ESP8266Client-";
                clientId += String(random(0xffff), HEX);
                if (client.connect(clientId.c_str())) {
                        Serial.println("connected");
                        client.subscribe("/smarthouse/temp/state");
                        client.subscribe("/smarthouse/light/state");
                } else {
                        Serial.print("failed, rc=");
                        Serial.print(client.state());
                        Serial.println(" try again in 5 seconds");
                        delay(5000);
                }
        }
}


void callback(char* topic, byte* payload, unsigned int length) {
        String MQTT_DATA = "";
        for (int i=0; i<length; i++) {
                MQTT_DATA += (char)payload[i];
        }
        Serial.println("message received from topic: " + MQTT_DATA + ", Topic:  " + topic);
        sendMessage(topic + ' ' + MQTT_DATA);
}

void setup(){

        Serial.begin(9600);
        unoMessage.begin(4800);
        pinMode(D2,INPUT);
        pinMode(D3,OUTPUT);
        pinMode(D7, OUTPUT);
        WiFi.disconnect();
        delay(3000);
        Serial.println("START");
        WiFi.begin(networkSSL,networkPassword);
        while ((!(WiFi.status() == WL_CONNECTED))) {
                delay(300);
                Serial.print("..");

        }
        Serial.println("Connected");
        Serial.println("Your IP is");
        Serial.println((WiFi.localIP().toString()));
        client.setServer( "192.168.43.109", 1883);
        client.setCallback(callback);

}

void sendMessage(String message){
        char charArray[50];
        message.toCharArray(charArray, 49);
        unoMessage.write(charArray);
        unoMessage.write('\n');
}

String receivedArduinoMessage(){
        char part;
        String message= "";
        while(unoMessage.available()) {
                part = ((char)unoMessage.read());
                if(part != '\n') {
                        message += part;
                }else if(message != "")
                        break;
                delay(50);

        }
        return message;
}

void unoMessageHandler(String arduinoData){
        Serial.println(arduinoData);
}
void publishMqtt(String topic, String message){
        char messageCharArray[50];
        message.toCharArray(messageCharArray, 50);
        char topicCharArray[50];
        topic.toCharArray(topicCharArray, 50);
        client.publish(topicCharArray, messageCharArray);
}

void loop()
{

        if (!client.connected()) {
                reconnectmqttserver();
        }
        client.loop();
        snprintf (msgmqtt, 50, message.c_str());
        publishMqtt("Topic", "MQTT_message");
        delay(5000);
        if(unoMessage.available())
                unoMessageHandler(receivedArduinoMessage());


}
