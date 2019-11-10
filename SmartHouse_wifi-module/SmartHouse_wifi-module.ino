/////////////////////////////////
// Generated with a lot of love//
// with TUNIOT FOR ESP8266     //
// Website: Easycoding.tn      //
/////////////////////////////////
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <PubSubClient.h>

SoftwareSerial softSerial(D2,D3);
WiFiClient espClient;
PubSubClient client(espClient);

String networkSSL = "Ras_the_Moose";
String networkPassword = "12345678";
String ipAddress = "194.47.28.11";
uint16_t port = 1883;
String message = "HEY";
int ledPin = 13;
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
        dataHandler(MQTT_DATA);
}

void setup(){

        Serial.begin(9600);
        softSerial.begin(4800);
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
void dataHandler(String data){
        if(data.equals("ON")) {
                sendMessage("ON");
        } else if(data.equals("OFF")) {
                sendMessage("OFF");
        }

}

void sendMessage(String message){
        char charArray[50];
        message.toCharArray(charArray, 20);
        softSerial.write(charArray);
        softSerial.write('\n');
}

String receivedArduinoMessage(){
        char part;
        String message= "";
        while(softSerial.available()) {
                part = ((char)softSerial.read());
                if(part != '\n') {
                        message += part;
                }else if(message != "")
                        break;
                delay(50);

        }
        return message;
}

void arduinoHandler(String arduinoData){
        Serial.println(arduinoData);
}

void loop()
{

        if (!client.connected()) {
                reconnectmqttserver();
        }
        client.loop();
        snprintf (msgmqtt, 50, message.c_str());
        String msg = "boppa loppa";
        msg.toCharArray(msgmqtt, 50);
        client.publish("test", msgmqtt);
        delay(5000);

        if(softSerial.available())
                arduinoHandler(receivedArduinoMessage());


}
