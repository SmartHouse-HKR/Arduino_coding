//martin_switches
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

//debouncefix
unsigned long windowLastDebounceTime = 0;
unsigned long fireLastDebounceTime = 0;
unsigned long stoveLastDebounceTime = 0;
unsigned long waterLastDebounceTime = 0;
unsigned long debounceDelay = 50;


//martin
int tempSensor = A2;
int tempSensorDigital = 9;
float tempAirDigital;
float tempAir; 
int mux1=12;
int mux2=13;
int mux3=11;
int mux4=8;
boolean lightInside=false;
boolean outsideLight=false;
boolean alarm1=false;
int fan=10;
char rx_byte = 0;


void setup(){
pinMode(window, INPUT);
pinMode(fire, INPUT);
pinMode(stove, INPUT);
pinMode(water, INPUT);

  

//martin
pinMode(mux1, OUTPUT);
pinMode(mux2, OUTPUT);
pinMode(mux3, OUTPUT);
pinMode(mux4, OUTPUT);
pinMode(window, OUTPUT);
pinMode(fan, OUTPUT);
Serial.begin(9600);  


  
}



void loop() {

readingWindow=digitalRead(window);
readingFire=digitalRead(fire);
readingStove=digitalRead(stove);
readingWater=digitalRead(water);
 

if (readingWindow != readingWindowLast) {
// reset the debouncing timer
windowLastDebounceTime = millis();
}

if (readingFire != readingFireLast) {
// reset the debouncing timer
fireLastDebounceTime = millis();
}

if (readingStove != readingStoveLast) {
// reset the debouncing timer
stoveLastDebounceTime = millis();
}

if (readingWater != readingWaterLast) {
// reset the debouncing timer
waterLastDebounceTime = millis();
}

if(millis()- windowLastDebounceTime > debounceDelay) {
  if(readingWindowLast != readingWindow){
    if(readingWindow == 1){
      Serial.println("Window opened");
    }
    if(readingWindow == 0){
      Serial.println("Window closed");
    }
      readingWindowLast=readingWindow;
  }
}

        if(readingFireLast != readingFire){
        if(readingFire == 1){
          Serial.println("Fire Alarm On");
        }if(readingFire == 0){
          Serial.println("Fire Alarm Off");
        }
        readingFireLast=readingFire;

        }

        if(readingStoveLast != readingStove){
        if(readingStove == 1){
          Serial.println("Stove On");
        }if(readingStove == 0){
          Serial.println("Stove Off");
        }
        readingStoveLast=readingStove;

        }

        if(readingWaterLast != readingWater){
        if(readingWater == 1){
          Serial.println("Fan On");
        }if(readingWater == 0){
          Serial.println("Fan Off");
        }
         readingWaterLast=readingWater;

        }






//martin
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
if(rx_byte == '5'){
  alarm();
}
if(rx_byte == '6'){
  alarmOff();
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


}
  


void fireAlarmOn(){
  Serial.write("fire alarm on");
}
void fireAlarmOff(){
  Serial.write("fire alarm off");
}
void waterLeakageOn(){
  Serial.write("leakage on");
}
void waterLeakageOff() {
  Serial.write("leakage off");
}
void stoveOn() {
  Serial.write("stove on");
}
void stoveOff() {
  Serial.write("stove off");
}
void windowOn(){
  Serial.write("window opened");
}
void windowOff(){
  Serial.write("window closed");
}

//martin
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
  analogWrite(fan, 175);
}
void fanOff(){
  analogWrite(fan, 0);
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
  digitalWrite(mux2, HIGH);
  digitalWrite(mux3, LOW);
  digitalWrite(mux4, LOW);
  
}
