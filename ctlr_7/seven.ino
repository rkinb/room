#include <Wire.h>

// THis code is from arduinos debounce example
const int Switch_Pin_1 = 2;    // the number of the pushbutton pin
int buttonPin[15]; 
int buttonState[15];
int lastButtonState[15];
unsigned long lastDebounceTime[15];
unsigned long debounceDelay = 80;
int SOLVED;
char switchIterator;
int mainIterator;
int RETURN;
boolean p1;
boolean p2;
boolean p3;

void setup() {
 // pinMode(13, OUTPUT); // binary mag lock
  //digitalWrite(13, 1); // start locked high
   Serial.begin(9600);
    //WIRE SETUP ....................................................
  Wire.begin(19);                // join i2c bus with address #9
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent); // Request attention of master node
  mainIterator = 0;
  switchIterator = '0';
  SOLVED = 0;
  p1 = false;
  p2 = false;
  p3 = false;
  for(int i = 2; i < 13; i++){
    if(i != 13){
      buttonPin[i] = i;
     digitalWrite(i, LOW);
    buttonState[i] = LOW;
    lastButtonState[i] = LOW;
    lastDebounceTime[i] = 0;
    pinMode(buttonPin[i], INPUT_PULLUP);
    }
  }
}

void loop() {

  //if(p1 && p2 && p3){
  //  switchIterator = '9';
  //  SOLVED = 1;
  //  p1 = false;
  //}
  //delay(100);
//  digitalWrite(13, LOW); // Toggle MagLock
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
      if (buttonState[i] == 0) {
         Serial.println("pressed in "+ (i-1));
         //SOLVED = 1;
         //  switchIterator = i+1;
         switch(i){
          case 2:
          SOLVED = 1;
switchIterator = '1';
          break;
          case 3:
          SOLVED = 1;
switchIterator = '2';
          break;
          case 4:
          SOLVED = 1;
switchIterator = '3';
          break;
          case 5:
          SOLVED = 1;
switchIterator = '4';
          break;
          case 6:
          SOLVED = 1;
switchIterator = '5';
          break;
          case 7:
          SOLVED = 1;
switchIterator = '6';
          break;
          case 8:
          SOLVED = 1;
switchIterator = '7';
         break;
        
          //Patch panel high states
          case 9:
switchIterator = '9';
SOLVED = 1;
//p1 = true;
          break;
          case 10:
switchIterator = 'A';
SOLVED = 1;
//p2 = true;
          break;
          case 11:
switchIterator = 'B';
SOLVED = 1;
//p3 = true;
          break;
          
         }
      }else if(buttonState[i] == 1){
        Serial.println("not pressed"+i);
        //switchIterator = '%';
         
         switch(i){
          //Patch low states
          case 9:
          SOLVED = 1;
switchIterator = 'C';
//p1 = false;
          break;
          case 10:
          SOLVED = 1;
switchIterator = 'D';
//p1 = false;
          break;
          case 11:
          SOLVED = 1;
switchIterator = 'E';
//p3 = false;
          break;
         }
         
      }
      //Serial.println(buttonState[i]);
      //Serial.println(switchIterator);
    }
  }
  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState[i] = reading;
  }
}
  mainIterator++;
  if(mainIterator >= 14 ){
    mainIterator = 0;
  }

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
}
// SEND DATA TO MASTER WHEN POLLED ***********************************************************
void requestEvent(){
  if(SOLVED == 1){
     //char l = switchIterator;
     //Serial.println(l);
    // digitalWrite(LED_BUILTIN, HIGH); // flash the LED to show data was sent. 
    // Wire.write(2); // what slave it was sent from ( may not be used ) 
     Wire.write(switchIterator);  // send off the data to the master.
     //Serial.println("DATA sent to MASTER:"); 
     SOLVED = 0;
    // switchIterator = "%";
    //delay(100);
  }
}

 //RECEIVE DATA FROM MASTER ***********************************************************
void receiveEvent(int howMany) {
     RETURN = Wire.read();           // receive byte as an integer
     //Serial.print("DATA from MASTER:");         // print the integer
     //Serial.println(RETURN + "loo");         // print the integer
     checkComms();
     
}// end of function

void checkComms(){
    if(RETURN == 1){//Binary Mag Lock activated
           // digitalWrite(13, LOW); // Toggle MagLock - this is actually in grid
    //  delay(100);
    }else if(RETURN == 2){ //ROOM IS BLUE
      
    }else if(RETURN == 3){// ROOM IS YELLOW

   
   }else if(RETURN == 4){ //ROOM IS RED
      
    
    }else if(RETURN == 5){//ROOM IS BLACK OUT 
     
    }
    RETURN = 0; // RESET RETURN
}
