int windowPin=6;
int windowState;
int windowLastState=LOW;

unsigned long windowLastDebounceTime = 0;
unsigned long debounceDelay = 50;


void setup() {
  
pinMode(windowPin, INPUT);
Serial.begin(9600);

}

void loop() {
  
int windowState = digitalRead(windowPin);

if (windowState != windowLastState) {
    // reset the debouncing timer
    windowLastDebounceTime = millis();
}

if ((millis() - windowLastDebounceTime) > debounceDelay) {
    
    if (windowState != windowState) {
      
    if(windowState == HIGH){
       Serial.println("Window opened");
    }if(windowState == LOW){
       Serial.println("Window closed");
     }
  }

  windowLastState = windowState;
}

  
  
  }
