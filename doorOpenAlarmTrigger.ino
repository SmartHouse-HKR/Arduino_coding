int mux1=12;
int mux2=13;
int mux3=11;
int mux4=8;
int door=3;
int doorValue;
int doorValueLast;
void setup() {
pinMode(mux1, OUTPUT);
  pinMode(mux2, OUTPUT);
  pinMode(mux3, OUTPUT);
  pinMode(mux4, OUTPUT);
  pinMode(door, INPUT);
  Serial.begin(9600);
}

void loop() {

  doorValue=digitalRead(door);
  Serial.println(doorValue);
  if(doorValue != doorValueLast){
        if(doorValue == 0){
          alarm();
        }if(doorValue == 1){
          alarmOff();
        }
        doorValueLast=doorValue;
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
