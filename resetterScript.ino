int mux1=12;
int mux2=13;
int mux3=11;
int mux4=8;



void setup() {
  pinMode(mux1, OUTPUT);
  pinMode(mux2, OUTPUT);
  pinMode(mux3, OUTPUT);
  pinMode(mux4, OUTPUT);
}

void loop() {
  digitalWrite(mux1, LOW);
  digitalWrite(mux2, LOW);
  digitalWrite(mux3, LOW);
  digitalWrite(mux4, LOW);
  delay(50);
   digitalWrite(mux1, HIGH);
  digitalWrite(mux2, LOW);
  digitalWrite(mux3, LOW);
  digitalWrite(mux4, HIGH);
  delay(50);
  digitalWrite(mux1, HIGH);
  digitalWrite(mux2, LOW);
  digitalWrite(mux3, HIGH);
  digitalWrite(mux4, LOW);
  delay(50);
  digitalWrite(mux1, HIGH);
  digitalWrite(mux2, LOW);
  digitalWrite(mux3, HIGH);
  digitalWrite(mux4, HIGH);
  delay(50);
  digitalWrite(mux1, HIGH);
  digitalWrite(mux2, HIGH);
  digitalWrite(mux3, HIGH);
  digitalWrite(mux4, LOW);
  delay(50);
  digitalWrite(mux1, HIGH);
  digitalWrite(mux2, HIGH);
  digitalWrite(mux3, LOW);
  digitalWrite(mux4, HIGH);
  delay(50);
  digitalWrite(mux1, HIGH);
  digitalWrite(mux2, HIGH);
  digitalWrite(mux3, LOW);
  digitalWrite(mux4, LOW);
  delay(50);
  digitalWrite(mux1, HIGH);
  digitalWrite(mux2, HIGH);
  digitalWrite(mux3, HIGH);
  digitalWrite(mux4, HIGH);
  delay(50);
}
