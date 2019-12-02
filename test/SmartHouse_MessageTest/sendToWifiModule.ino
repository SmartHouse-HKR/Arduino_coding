//void sendToWifiModule(String topic, String message){
//
//  char* messageArray = (char*) malloc(sizeof(char)*message.length()+1);
//  char* topicArray = (char*) malloc(sizeof(char)*topic.length()+1);
//  message.toCharArray(messageArray, message.length()+1);
//  topic.toCharArray(topicArray, topic.length()+1);
//
//  wifiMessage.write(topicArray);
//  wifiMessage.write(' ');
//  wifiMessage.write(messageArray);
//  wifiMessage.write('\n');
//
//  Serial.println("sent to wifi module: " + ((String)topicArray) + " " + ((String)messageArray));
//  free(topicArray);
//  free(messageArray);
//}
