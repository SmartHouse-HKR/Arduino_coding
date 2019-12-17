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
