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
int RETURN = 0;

void setup() {
   Serial.begin(9600);
    //WIRE SETUP ....................................................
  Wire.begin(1);                // join i2c bus with address #3
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent); // Request attention of master node
  mainIterator = 0;
  switchIterator = 0;
  SOLVED = 0;
  for(int i = 2; i < 11; i++){
    if(i != 7){
      buttonPin[i] = i;
      buttonState[i] = LOW;
      lastButtonState[i] = LOW;
      lastDebounceTime[i] = 0;
      pinMode(buttonPin[i], INPUT_PULLUP);
    }
  }

  // initialize the LED pin as an output:
 // pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  //pinMode(buttonPin, INPUT_PULLUP);

  pinMode(7, OUTPUT);
  digitalWrite(7, 0);//linear actuator
  pinMode(13, OUTPUT);
  digitalWrite(13, 0); // low
  
}

void loop() {
  //+++++++++++++++++++++++++++++++ Switch 1++++++++++++++
// read the state of the switch into a local variable:
for(int i = 2; i < 11; i++){
  if(i == mainIterator && i != 7){
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
      if (buttonState[i] == 0) {
         //Serial.println("pressed in ");
         delay(10);
         SOLVED = 1;
         switchIterator = i;
         char l = switchIterator;
         //Serial.println(l + " aljdlf" + l); 
         if(switchIterator==2){
            digitalWrite(13, 0); // low
            //generator on is high

         }
         if(switchIterator==5){
            digitalWrite(13, 1); // 
            //generator off is high

         }
         delay(9);
      }else{
        switchIterator = i;
         if(switchIterator==2){
            switchIterator = 1;
            delay(10);
         SOLVED = 1;
            //generator goes from high to off

         }
      }
    }
  }
  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState[i] = reading;
  }
}
  mainIterator++;
  if(mainIterator > 11 ){
    mainIterator = 2;
  }

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
}
// SEND DATA TO MASTER WHEN POLLED ***********************************************************
void requestEvent(){
  if(SOLVED == 1){
    // int l = switchIterator;
    
      //Serial.println(l);
      //digitalWrite(LED_BUILTIN, HIGH); // flash the LED to show data was sent. 
      //Wire.write(1); // what slave it was sent from ( may not be used ) 
      Wire.write(switchIterator);  // send off the data to the master.
      //Serial.println("DATA sent to MASTER:"); 
      SOLVED = 0;
      delay(10);
     
  }
}




//RECEIVE DATA FROM MASTER ***********************************************************
void receiveEvent(int howMany) {
 // digitalWrite(13, !digitalRead(13)); // Toggle Light 1
  RETURN = Wire.read();
  //Serial.println(RETURN);
  checkComms();
   //  while(1 < Wire.available()) // loop through all but the last
   // {
   //   digitalWrite(13, !digitalRead(13)); // Toggle Light 1
   //    RETURN = Wire.read();           // receive byte as an integer
   //    Serial.print("DATA from MASTER:");         // print the integer
   //    Serial.println(RETURN);         // print the integer
      //char c = Wire.read(); // receive byte as a character
      //Serial.print(c);         // print the character
   //    checkComms();
   // }
      //int x = Wire.read();    // receive byte as an integer
      //Serial.println(x);         // print the integer
}// end of function


void checkComms(){
    if(RETURN == 2){
      digitalWrite(7,1);
      digitalWrite(13, 1); // high
    }
    if(RETURN == 19){
      digitalWrite(7,0);
      digitalWrite(13, 0); // high
    }
    RETURN = 0; // RESET RETURN
}
