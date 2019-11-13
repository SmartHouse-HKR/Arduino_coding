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

int mux1=12;
int mux2=13;
int mux3=11;
int mux4=8;
int fan=10;


void setup() {
  // put your setup code here, to run once:
  
pinMode(window, INPUT);
pinMode(fire, INPUT);
pinMode(stove, INPUT);
pinMode(water, INPUT);
pinMode(mux1, OUTPUT);
  pinMode(mux2, OUTPUT);
  pinMode(mux3, OUTPUT);
  pinMode(mux4, OUTPUT);
    pinMode(fan, OUTPUT);

Serial.begin(9600);
}

void loop() {
  readingWindow=digitalRead(window);
  readingFire=digitalRead(fire);
  readingStove=digitalRead(stove);
  readingWater=digitalRead(water);
  Serial.print(readingWindow);
    //Serial.print(readingFire);
      //Serial.print(readingStove);
        //Serial.print(readingWater);

        if(readingWindowLast != readingWindow){
        if(readingWindow == 1){
          alarm();
        }if(readingWindow == 0){
          alarmOff();
        }
        readingWindowLast=readingWindow;
        }

        if(readingFireLast != readingFire){
        if(readingFire == 1){
          lightOn();
        }if(readingFire == 0){
          lightOff();
        }
        readingFireLast=readingFire;

        }

        if(readingStoveLast != readingStove){
        if(readingStove == 1){
          lightOn2();
        }if(readingStove == 0){
          lightOff2();
        }
        readingStoveLast=readingStove;

        }

        if(readingWaterLast != readingWater){
        if(readingWater == 1){
          fanOn();
        }if(readingWater == 0){
          fanOff();
        }
         readingWaterLast=readingWater;

        }



  

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


void fanOn(){
  digitalWrite(fan, HIGH);
}
void fanOff(){
  digitalWrite(fan, LOW);
}
