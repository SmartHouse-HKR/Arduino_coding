int elecConsumption = A0;
int tempFirstFlr = A1;
int tempSecondFlr = A2;
int LDR = A3;

void setup() {
  
  pinMode(0, INPUT); //RX
  pinMode(1, INPUT); //LX
  pinMode(2, INPUT); //Fire alarm on/off
  pinMode(3, INPUT); //Burglar alarm on/off
  pinMode(4, INPUT); //Water leakage on/off
  pinMode(5, INPUT); //Oven on/off
  pinMode(6, INPUT); //Window on/off
  pinMode(7, INPUT); //Power cut on/off
  pinMode(9, INPUT); //Temp outside
  pinMode(10, OUTPUT); //Fan

  pinMode(8, OUTPUT); //MUX1
  pinMode(11, OUTPUT); //MUX2
  pinMode(12, OUTPUT); //MUX3
  pinMode(13, OUTPUT); //MUX4


  /*
   * Alarm off:
   * digitalWrite(8, LOW); 
   * digitalWrite(11, LOW); 
   * digitalWrite(12, LOW); 
   * digitalWrite(13, LOW); 
   * 
   * Alam on:
   * digitalWrite(8, LOW); 
   * digitalWrite(11, LOW); 
   * digitalWrite(12, HIGH); 
   * digitalWrite(13, LOW); 
   * 
   * Burglar alarm lamp off:
   * digitalWrite(8, HIGH); 
   * digitalWrite(11, HIGH ); 
   * digitalWrite(12, HIGH); 
   * digitalWrite(13, LOW ); 
   * 
   * Burglar alarm lamp on:
   * digitalWrite(8, HIGH); 
   * digitalWrite(11, HIGH ); 
   * digitalWrite(12, LOW); 
   * digitalWrite(13, LOW ); 
   * 
   * Heating element 1 off:
   * digitalWrite(8, HIGH); 
   * digitalWrite(11, LOW); 
   * digitalWrite(12, HIGH); 
   * digitalWrite(13, HIGH); 
   * 
   * Heating element 1 on:
   * digitalWrite(8, HIGH); 
   * digitalWrite(11, LOW); 
   * digitalWrite(12, LOW); 
   * digitalWrite(13, HIGH); 
   * 
   * Heating element 2 off:
   * digitalWrite(8, LOW); 
   * digitalWrite(11, HIGH); 
   * digitalWrite(12, HIGH); 
   * digitalWrite(13, HIGH); 
   * 
   * Heating element 2 on:
   * digitalWrite(8, LOW); 
   * digitalWrite(11, HIGH); 
   * digitalWrite(12, LOW); 
   * digitalWrite(13, HIGH); 
   * 
   * Indoor lighting off:
   * digitalWrite(8, LOW); 
   * digitalWrite(11, HIGH); 
   * digitalWrite(12, LOW); 
   * digitalWrite(13, LOW); 
   * 
   * Indoor lighting on:
   * digitalWrite(8, HIGH); 
   * digitalWrite(11, LOW); 
   * digitalWrite(12, HIGH); 
   * digitalWrite(13, HIGH); 
   * 
   * Outdoor lighting off:
   * digitalWrite(8, LOW); 
   * digitalWrite(11, HIGH); 
   * digitalWrite(12, LOW); 
   * digitalWrite(13, LOW); 
   * 
   * Outdoor lighting on:
   * digitalWrite(8, HIGH); 
   * digitalWrite(11, HIGH); 
   * digitalWrite(12, LOW); 
   * digitalWrite(13, HIGH); 
   * 
   * Timer 1 off:
   * digitalWrite(8, LOW); 
   * digitalWrite(11, LOW); 
   * digitalWrite(12, HIGH); 
   * digitalWrite(12, HIGH); 
   * 
   * Timer 1 on:
   * digitalWrite(8, LOW); 
   * digitalWrite(11, LOW); 
   * digitalWrite(12, LOW); 
   * digitalWrite(12, HIGH);
   * 
   * Timer 2 off:
   * digitalWrite(8, HIGH); 
   * digitalWrite(11, LOW); 
   * digitalWrite(12, HIGH); 
   * digitalWrite(12, LOW); 
   * 
   * Timer 2 on:
   * digitalWrite(8, HIGH); 
   * digitalWrite(11, LOW); 
   * digitalWrite(12, LOW); 
   * digitalWrite(12, LOW); 
   *
    */
}  

void loop() {
  // put your main code here, to run repeatedly:

}
