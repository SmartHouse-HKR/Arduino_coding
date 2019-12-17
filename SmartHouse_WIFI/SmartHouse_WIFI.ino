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
                        for(int i = 0; i < 1000; i++){
                              arduinoMessageCheck();
                          delay(5);
                        }
                }
        }
}

void arduinoMessageCheck(){

                                  if(unoMessager.available()) {
                                         
                                         String receivedData = receivedArduinoData();
                                         Serial.println("message from arduino: " + receivedData);
                                         String topic = getSubstring(receivedData, ' ', 0);
                                         String message = getSubstring(receivedData, ' ', 1);
                                         handleReceivedData(topic, message);
                              }
}
void subscribeToTopics(){
  
        client.subscribe("echo");
        
        client.subscribe("smarthouse/indoor_light/state"); //done
        client.subscribe("smarthouse/outdoor_light/state"); //done
        
        client.subscribe("smarthouse/heater_1/state"); 
        client.subscribe("smarthouse/heater_2/state");
        client.subscribe("smarthouse/heater_1/value");
        client.subscribe("smarthouse/heater_1/value");
        
        client.subscribe("smarthouse/fan/speed");
        
        client.subscribe("smarthouse/outdoor_temperature/value");
        client.subscribe("smarthouse/indoor_temperature/value");
        
        client.subscribe("smarthouse/voltage/value");
        client.subscribe("smarthouse/voltage/overview");
        client.subscribe("smarthouse/power/state");
        
        client.subscribe("smarthouse/burglar_alarm/state");
        client.subscribe("smarthouse/burglar_alarm/trigger");
        
        client.subscribe("smarthouse/fire_alarm/state");
        client.subscribe("smarthouse/fire_alarm/trigger");
        client.subscribe("smarthouse/water_leak/trigger");
        
        client.subscribe("smarthouse/oven/state");
        client.subscribe("smarthouse/window_alarm/state");
        client.subscribe("smarthouse/window_alarm/trigger");
        
        client.subscribe("smarthouse/window_alarm/state");
        client.subscribe("smarthouse/window_alarm/state");
        
        
}

void wifiConnect(){
  
        WiFi.disconnect();
        delay(3000);
        Serial.println("START");
        WiFi.begin(networkSSL,networkPassword);
        while ((!(WiFi.status() == WL_CONNECTED))) {
                for(int i = 0; i<60; i++){
                  arduinoMessageCheck();
                  delay(5);
                }
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

void sendToArduino(String topic, String message){

        char* messageArray = (char*) malloc(sizeof(char)*message.length()+1);
        char* topicArray = (char*) malloc(sizeof(char)*topic.length()+1);
        message.toCharArray(messageArray, message.length()+1);
        topic.toCharArray(topicArray, topic.length()+1);
        unoMessager.write(topicArray);
        unoMessager.write(' ');
        unoMessager.write(messageArray);
        unoMessager.write('\n');
        free(messageArray);
        free(topicArray);
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

String receivedArduinoData(){
  
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

        arduinoMessageCheck();
}

void handleReceivedData(String topic, String message){
                if(topic.equals("ip")){
                  Serial.println("ip changed to: "+ message);
                  message.toCharArray(ipAddress, 16);
                  wifiConnect();
                  client.setCallback(callback);
                }else if(topic.equals("wifi")){
                  Serial.println("wifi changed to: "+ message);
                  networkSSL = message;
                  wifiConnect();
                  client.setCallback(callback);
                }else if(topic.equals("wifi_pass")){
                  Serial.println("wifi_pass changed to: "+ message);
                  networkPassword = message;
                  wifiConnect();
                  client.setCallback(callback);
                }else if(topic.equals("status")){
                  Serial.println("sending status to arduino");
                  sendToArduino("reply",((String)("wifi: "+getWifiStatus()+", MQTT-client: "+getMQTTClientStatus())));
                }else if(WiFi.status() == WL_CONNECTED && client.connected()){
                Serial.println("sending to MQTT, topic: " + topic + ", message: " + message);
                sendToMQTT(topic, message);
}
}

String getWifiStatus(){
  if(WiFi.status() == WL_CONNECTED)
  return "connected";
  else return "not connected";
}

String getMQTTClientStatus(){
  if(client.connected())
  return "connected";
  else return "not connected";
}
