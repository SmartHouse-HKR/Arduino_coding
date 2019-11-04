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
  analogWrite(fan, 175);
  if(lightInside==true){
  lightOn();
  }else{
    delay(5000);
    lightInside=true;
    return;
  }

  if(outsideLight==true){
  lightOn2();
  }else{
    delay(5000);
    outsideLight=true;
    return;
  }

   if(alarm1==true){
   alarm();
   }else{
    delay(5000);
    alarm1=true;
    return;
   }

   analogWrite(fan, 175);


   digitalWrite(mux1, LOW);
   digitalWrite(mux2,HIGH);
   digitalWrite(mux3,HIGH);
   digitalWrite(mux4,HIGH);

  

  

  


  
  
}



void lightOn(){

digitalWrite(mux1, LOW);
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

void alarm(){
  digitalWrite(mux1, LOW);
  digitalWrite(mux2, LOW);
  digitalWrite(mux3, HIGH);
  digitalWrite(mux4, HIGH);
  
}
