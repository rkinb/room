#include <Wire.h>


// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin


// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

int lastButtonState = LOW;   // the previous reading from the input pin
int ledState = HIGH;         // the current state of the output pin

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 150;    // the debounce time; increase if the output flickers

int RETURN;
int SOLVED;
bool bo;

void setup() {
  bo = true;
   //WIRE SETUP ....................................................
  Wire.begin(21);                // join i2c bus with address #2
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent); // Request attention of master node

  // initialize the LED pin as an output:
 // pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  //pinMode(buttonPin, INPUT_PULLUP);
  for(int i = 2 ; i < 13; i++){
    pinMode(i, OUTPUT);
    digitalWrite(i, 0);
  }
  Serial.begin(9600);
}

void loop() {
  


//+++++++++++++++++LIGHT OUTPUT 1++++++++++++++++++++++++++++++
  char c;
  //Serial.println("a");
//  if(Serial.available())  
//  {  
//    c = Serial.read();  
//    //delay(100);
//    if(c == '1'){
//      digitalWrite(9, HIGH);
//    }else if(c == '2'){
//      digitalWrite(9, LOW);
//    }
//  }
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //    digitalWrite(13, !digitalRead(13)); // Toggle Light 1
//delay(1000);
//int val = digitalRead(1);
//Serial.println(val);
//if(val == 0){
//        digitalWrite(1, 1); // Toggle Light 1
//        Serial.println("LOW");
//      }else{
//        Serial.println("HIGH");
//        digitalWrite(1,0);
//      }
 delay(7);
//
//if(bo){
//  digitalWrite(1,1);
//  bo = false;
//}else{
//  digitalWrite(1,0);
//  bo = true;
//}
//Serial.println(bo);

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

// SEND DATA TO MASTER WHEN POLLED ***********************************************************
void requestEvent(){
//  if(SOLVED == 1){
//    digitalWrite(LED_BUILTIN, HIGH); // flash the LED to show data was sent. 
//    Wire.write(3); // what slave it was sent from ( may not be used ) 
//    Wire.write(3);  // send off the data to the master.
//    Serial.print("DATA sent to MASTER:"); 
//    delay(20);
//  }
}
void checkComms(){
    if(RETURN == 1){
      if(digitalRead(2) == HIGH){
        digitalWrite(2, LOW); // Toggle Light 1
      }else{
        digitalWrite(2,HIGH);
      }
    }else if(RETURN == 2){
      if(digitalRead(3) == HIGH){
        digitalWrite(3, LOW); // Toggle Light 2
      }else{
        digitalWrite(3,HIGH);
      }    
    }else if(RETURN == 3){
      if(digitalRead(4) == HIGH){
        digitalWrite(4, LOW); // Toggle Light 3
      }else{
        digitalWrite(4,HIGH);
      }
    }else if(RETURN == 4){
      if(digitalRead(5) == HIGH){
        digitalWrite(5, LOW); // Toggle Light 4
      }else{
        digitalWrite(5,HIGH);
      }
    }else if(RETURN == 5){
      if(digitalRead(6) == HIGH){
        digitalWrite(6, LOW); // Toggle Light 5
      }else{
        digitalWrite(6,HIGH);
      }
    }else if(RETURN == 6){
      if(digitalRead(7) == HIGH){
        digitalWrite(7, LOW); // Toggle Light 6
      }else{
        digitalWrite(7,HIGH);
      }
    }else if(RETURN == 7){
      if(digitalRead(8) == HIGH){
        digitalWrite(8, LOW); // Toggle Light 7
      }else{
        digitalWrite(8,HIGH);
      }
    }else if(RETURN == 8){
      if(digitalRead(10) == HIGH){
        digitalWrite(10, LOW); // Toggle Light 8
      }else{
        digitalWrite(10,HIGH);
      }
    }else if(RETURN == 9){
      if(digitalRead(9) == HIGH){
        digitalWrite(9, LOW); // Toggle Light 9
      }else{
        digitalWrite(9,HIGH);
      }
    }else if(RETURN == 10){
      if(digitalRead(11) == HIGH){
        digitalWrite(11, LOW); // Toggle Light 10
      }else{
        digitalWrite(11,HIGH);
      }
    }else if(RETURN == 11){
      for(int i = 2 ; i < 13; i++){
      digitalWrite(i, 0);
  }
    }
    RETURN = 0; // RESET RETURN
}
