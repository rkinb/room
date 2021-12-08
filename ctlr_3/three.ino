#include <Wire.h>

// THis code is from arduinos debounce example
const int Switch_Pin_1 = 2;    // the number of the pushbutton pin
int buttonPin[15]; 
int buttonState[15];
int lastButtonState[15];
unsigned long lastDebounceTime[15];
unsigned long debounceDelay = 30;
int SOLVED;
int switchIterator;
int mainIterator;

void setup() {
   Serial.begin(9600);
    //WIRE SETUP ....................................................
  Wire.begin(2);                // join i2c bus with address #3
  //Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent); // Request attention of master node
  mainIterator = 0;
  switchIterator = 0;
  SOLVED = 0;
  for(int i = 2; i < 13; i++){
    buttonPin[i] = i;
    buttonState[i] = LOW;
    lastButtonState[i] = LOW;
    lastDebounceTime[i] = 0;
    pinMode(buttonPin[i], INPUT_PULLUP);
  }

    pinMode(13, OUTPUT);
  digitalWrite(13, 0); // low

  
}

void loop() {
  //+++++++++++++++++++++++++++++++ Switch 1++++++++++++++
// read the state of the switch into a local variable:
for(int i = 2; i < 13; i++){
  if(i == mainIterator){
    int reading = digitalRead(buttonPin[i]);
    // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState[i]) {
    // reset the debouncing timer
    lastDebounceTime[i] = millis();
  }

  if ((millis() - lastDebounceTime[i]) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:
      
    if (reading != buttonState[i]) {
      buttonState[i] = reading;
      if (buttonState[i] == 0 || buttonState[i] == 1) {
        // Serial.println("state changed ");
         SOLVED = 1;
         switchIterator = i;
         if(digitalRead(13) == HIGH){
        digitalWrite(13, LOW); // Toggle linear actuator
      }else{
        digitalWrite(13,HIGH);
      }    
        // Serial.println(buttonState[i]); 
      }
    }
  }
  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState[i] = reading;
  }
}
  mainIterator++;
  if(mainIterator >= 13 ){
    mainIterator = 0;
  }

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
}
// SEND DATA TO MASTER WHEN POLLED ***********************************************************
void requestEvent(){
  if(SOLVED == 1){
    // int l = switchIterator;
     //Serial.println(l);
     //Wire.write(2);
     Wire.write(switchIterator);  // send off the data to the master.
     //Serial.println("DATA sent to MASTER:"); 
     SOLVED = 0;
     //delay(20);
  }
}
