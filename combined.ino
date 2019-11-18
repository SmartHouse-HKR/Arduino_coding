int window=6;
int fire=2;
int stove=5;
int water=4;
int readingWindow;
int readingFire;
int readingStove;
int readingWater;
int readingWindowLast=0;
int readingFireLast=0;
int readingStoveLast=0;
int readingWaterLast=0;
int readingLDR=0;
int readingLDRLast=0;

int mux1=12;
int mux2=13;
int mux3=11;
int mux4=8;
int fan=10;


int door=3;
int doorValue;
int doorValueLast;

int tempSensor = A2;
int tempSensorDigital = 9;
float tempAirDigital;
float tempAir; 


int ldrSensor = A1;
int sensorValue = 0;
char rx_byte = 0;





void setup() {
  
pinMode(window, INPUT);
pinMode(fire, INPUT);
pinMode(stove, INPUT);
pinMode(water, INPUT);
pinMode(mux1, OUTPUT);
  pinMode(mux2, OUTPUT);
  pinMode(mux3, OUTPUT);
  pinMode(mux4, OUTPUT);
    pinMode(fan, OUTPUT);
  pinMode(door, INPUT);


Serial.begin(9600);
}

void loop() {
  readingWindow=digitalRead(window);
  readingFire=digitalRead(fire);
  readingStove=digitalRead(stove);
  readingWater=digitalRead(water);

//doorStart
 doorValue=digitalRead(door);
  //Serial.println(doorValue);
  if(doorValue != doorValueLast){
        if(doorValue == 0){
          alarm();
        }if(doorValue == 1){
          alarmOff();
        }
        doorValueLast=doorValue;
        }

        //doorEnd
  
  //switchesStart
if(readingWindowLast != readingWindow){
        if(readingWindow == 1){
          windowOn();
        }if(readingWindow == 0){
          windowOff();
        }
        readingWindowLast=readingWindow;
        }

        if(readingFireLast != readingFire){
        if(readingFire == 1){
          fireOn();
        }if(readingFire == 0){
          fireOff();
        }
        readingFireLast=readingFire;

        }

        if(readingStoveLast != readingStove){
        if(readingStove == 1){
          stoveOn();
        }if(readingStove == 0){
          stoveOff();
        }
        readingStoveLast=readingStove;

        }

        if(readingWaterLast != readingWater){
        if(readingWater == 1){
          waterOn();
        }if(readingWater == 0){
          waterOff();
        }
         readingWaterLast=readingWater;

        }


//switchesEnd


//keyboard component test
if(Serial.available()  > 0){
    rx_byte = Serial.read();
  }



if(rx_byte == '1'){
  lightOn();
}
if(rx_byte == '2'){
  lightOff();
}
if(rx_byte == '3'){
  lightOn2();
}
if(rx_byte == '4'){
  lightOff2();
}
if(rx_byte == '7'){
  heatingWind();
}
if(rx_byte == '8'){
  heatingWindOff();
}
if(rx_byte == '9'){
  fanOn();
}
if(rx_byte == '0'){
  fanOn();
}
if(rx_byte == 'q'){
  heatingOn();
}
if(rx_byte == 'w'){
  heatingOff();
}
if(rx_byte == 'a'){
  timer1();
}
if(rx_byte == 's'){
  timer1Off();
}
if(rx_byte == 'z'){
  timer2();
}
if(rx_byte == 'x'){
  timer2Off();
}

//keyboard component test end
  
//LDR sensor start

sensorValue = analogRead(ldrSensor); // read the value from the sensor
  //Serial.println(sensorValue);

  if(sensorValue>100){
    readingLDR=0;
  }
  if(sensorValue<=100){
    readingLDR=1;
  }



        if(readingLDR != readingLDRLast){
        if(readingLDR == 1){
          lightOn2();
        }if(readingLDR == 0){
          lightOff2();
        }
         readingLDRLast=readingLDR;

        }
  

 //LDR sensor end
        
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

void lightOn2(){
  digitalWrite(mux1, LOW);
  digitalWrite(mux2, HIGH);
  digitalWrite(mux3, HIGH);
  digitalWrite(mux4, HIGH);
  
}
void lightOff2(){
  digitalWrite(mux1, HIGH);
  digitalWrite(mux2, HIGH);
  digitalWrite(mux3, HIGH);
  digitalWrite(mux4, HIGH);
  
}

void alarm(){
  digitalWrite(mux1, LOW);
  digitalWrite(mux2, LOW);
  digitalWrite(mux3, HIGH);
  digitalWrite(mux4, HIGH);
delay(50);
  digitalWrite(mux1, HIGH);
  digitalWrite(mux2, LOW);
  digitalWrite(mux3, LOW);
  digitalWrite(mux4, LOW);
  
}

void alarmOff(){
  digitalWrite(mux1, LOW);
  digitalWrite(mux2, LOW);
  digitalWrite(mux3, LOW);
  digitalWrite(mux4, LOW);
delay(50);
  digitalWrite(mux1, HIGH);
  digitalWrite(mux2, LOW);
  digitalWrite(mux3, HIGH);
  digitalWrite(mux4, HIGH);
  
}

void heatingWind(){
  digitalWrite(mux1, LOW);
  digitalWrite(mux2, HIGH);
  digitalWrite(mux3, HIGH);
  digitalWrite(mux4, LOW);
  
}
void heatingWindOff(){
  digitalWrite(mux1, HIGH);
  digitalWrite(mux2, HIGH);
  digitalWrite(mux3, HIGH);
  digitalWrite(mux4, LOW);
  
}

void fanOn(){
  digitalWrite(fan, HIGH);
}
void fanOff(){
  digitalWrite(fan, LOW);
}


void heatingOn(){
  digitalWrite(mux1, LOW);
  digitalWrite(mux2, HIGH);
  digitalWrite(mux3, LOW);
  digitalWrite(mux4, HIGH);
  
}

void heatingOff(){
  digitalWrite(mux1, HIGH);
  digitalWrite(mux2, HIGH);
  digitalWrite(mux3, LOW);
  digitalWrite(mux4, HIGH);
  
}
void timer1(){
  digitalWrite(mux1, LOW);
  digitalWrite(mux2, HIGH);
  digitalWrite(mux3, LOW);
  digitalWrite(mux4, LOW);
  
}
void timer1Off(){
  digitalWrite(mux1, HIGH);
  digitalWrite(mux2, HIGH);
  digitalWrite(mux3, LOW);
  digitalWrite(mux4, LOW);
  
}
void timer2(){
  digitalWrite(mux1, LOW);
  digitalWrite(mux2, LOW);
  digitalWrite(mux3, LOW);
  digitalWrite(mux4, HIGH);
  
}
void timer2Off(){
  digitalWrite(mux1, HIGH);
  digitalWrite(mux2, LOW);
  digitalWrite(mux3, LOW);
  digitalWrite(mux4, HIGH);
  
}


void windowOn(){
  Serial.println("window on");
}
void windowOff(){
  Serial.println("window Off");
}

void fireOn(){
  Serial.println("fire on");
}
void fireOff(){
  Serial.println("fire Off");
}
void stoveOn(){
  Serial.println("stove on");
}
void stoveOff(){
  Serial.println("stove Off");
}
void waterOn(){
  Serial.println("water on");
}
void waterOff(){
  Serial.println("water Off");
}
