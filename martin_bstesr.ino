int tempSensor = A2;
int tempSensorDigital = 9;
float tempAirDigital;
float tempAir; 
int mux1=12;
int mux2=13;
int mux3=11;
int mux4=8;
int window=6;
boolean lightInside=false;
boolean outsideLight=false;
boolean alarm1=false;
int fan=10;

char rx_byte = 0;

void setup() {
  pinMode(mux1, OUTPUT);
  pinMode(mux2, OUTPUT);
  pinMode(mux3, OUTPUT);
  pinMode(mux4, OUTPUT);
  pinMode(window, OUTPUT);
  pinMode(fan, OUTPUT);


  Serial.begin(9600);
  
}

void loop() {
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
