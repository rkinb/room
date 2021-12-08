//-------------------------------------------------------------------------------------------------------------------------------

//INCLUDES ********************************************************************
#include <Wire.h>
//#include <LiquidCrystal_I2C.h>

#include <DmxMaster.h>

// VARIABLES ******************************************************************
#define PAYLOAD_SIZE 2 // how many bytes to expect from each I2C salve node
#define NODE_MAX 20 // maximum number of slave nodes (I2C addresses) to probe
#define START_NODE 1 // The starting I2C address of slave nodes
#define NODE_READ_DELAY 10 // Some delay between I2C node reads

// System vars.................................................................
int nodePayload[PAYLOAD_SIZE];
byte x = 0;
int COUNT = 0; // keep track of cycles 
int SEND = 0; // value to send to PC
int RECEIVE = 0; // data from PC
int STAGE = 0; // what stage of the program it is in.
int MOOD = 100; // what moode the AI is in, less than 100 is angry and 100+ is happy. 
int WCOUNT = 0; // how long to wait to repeat instructions. 
int MSTAGE = 0; // Motion sensor number of fails. 
int LDJSTAGE = 0; // what stage of punishment. 
int TDISPLAY = 0; // what track has been show on the screen. 
int FURYCOUNT = 0; // how many laser trips durring AI fury.
int NETWORK = 0; // store variable of what port the virus or cable is pluged into.
int CBSTAGE = 0; // combox mini game stage.
int CBCOUNT = 0; // how many times they have pressed a button on combox in game stage. 
int CBWARNING = 0; // what was the last CB warning. 

// Slave vars .................................................................
int GENSOLVE = 0; // if generator is solved a [1] will show up.
int EPANELSOLVE = 0;// if epannel is solved a [2] will show up.
int PATCHSOLVE = 0;// if patch panel is solved a [3] will show up.
int JUKETRACK = 0; // What track is currently playing on juke box. [1-255]
int COMBOX1 = 0;// if power button is pressed a [1] will show up. 
int COMBOX2 = 0;// if power button is pressed a [1] will show up.
int AIPLAYING = 0;// [1] when a track is playing [2] when not playing.
int DJBOOTH = 0;// [1] GREEN button pressed OK [11] Green FAIL [2] Blue press OK [12] Blue FAIL [3] Binary puzzle solved.
int ATMBAT = 0;// [1]B1 in [2]B2 in [3]B3 in [4]B4 in [10]B1 removed [20]B2 removed [30]B3 removed.
//int TRACK = 0; // track storage var
int BAT1 = 0; //state of BAT1
int BAT2 = 0;// state of BAT2
int BAT3 = 0;// state of BAT3
int BSEND = 0; // what value to send of battery to PC
int BSENT = 0; // what value was sent to to PC of battery stat.
int MOTIONLASER = 0; // what is received from the motion-laser arduino, if any of the sensors are tripped.
int MOTIONTRIPSKIP = 0; // skipping first trip. 
int TRACK = 0; // what track is playing on the juke box, or if a button is pressed.
int CLOSET = 0; // what is received from the CLOSET arduino.
int CLOSETCOUNT = 0; // how pissed AI is getting about the closet. 

boolean p1;
boolean p2;
boolean p3;
int iiiiii = 0;
int S5 = 0; // variables to store data from slaves
int S6 = 0;

boolean MusicUp;
boolean MusicDown;

int gameIntroStarted;
int gameSetUP;

boolean GameWinTotal;
boolean GenOFFGameWin;
boolean EPANELThree;
int abb = 0;
boolean djDoorCanOpen;
boolean GameOverTime;
boolean PatchStart;
boolean GameIntroOnce;
boolean WORKINGgames;
//TIME VARS *****
//unsigned long startMillis;  //some global variables available anywhere in the program
//unsigned long currentMillis;
//const unsigned long period = 9000;  //the value is a number of milliseconds

unsigned long time_now = 0; // setting of master time var.


//LCD SETUP*****************************************************************************************
// LCD for Juke Box is x27...........................................................................
//LiquidCrystal_I2C lcd1(0x27,20,4);  // set the LCD address to 0x27 for a 20 chars and 4 line display [lcd1]
// LCD for COM Box #1 is x26..........................................................................
//LiquidCrystal_I2C lcd2(0x26,20,4);  // set the LCD address to 0x27 for a 20 chars and 4 line display [lcd2] Single A1 bridge. 
// LCD for COM Box #2 is x24..........................................................................
//LiquidCrystal_I2C lcd3(0x24,20,4);  // set the LCD address to 0x27 for a 20 chars and 4 line display [lcd3] dual A0-A1 bridge








// SETUP **********************************************************************

void setup() {
  WORKINGgames = true;;
p1 = false;
  p2 = false;
  p3 = false;
  GameIntroOnce = false;
  
EPANELThree = false;
GenOFFGameWin = false;
GameWinTotal = false;
MusicUp = false;
MusicDown = false;
djDoorCanOpen = false;
   // SERIAL...................................................
  Serial.begin(115200);  


  gameIntroStarted = false;
  gameSetUP = true;
  GameOverTime = false;
  PatchStart = false;
  
 // Serial.println("MASTER ONLINE. starting wire..");
   // WIRE BEGIN ...............................................
  Wire.begin(); // join i2c bus (address optional for master)
  //Wire.setClock(100000); // slow things down
  //Serial.println("Wire started, booting displays...");

  //Time count start
  //startMillis = millis();  //initial start time
  

// LED Setup..................................................
//pinMode(LED_BUILTIN, OUTPUT);
//pinMode(13, OUTPUT);

//STAGE = 17; //force motion sensor challenge (((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((


// Serial.println("Setup done, going to loop.");
}// end of setup











// MAIN LOOP ##################################################################################################################################

void loop() {

if(PatchStart){
 if(p1 && p2 && p3){
    //ALL THREE CORRECT PLAY CORRECT NUMBERS
    Serial.write('i');
    EPANELThree = true;
    PatchStart = false;

    Wire.beginTransmission(4); // 4 Juke box 
    Wire.write(23);              // Simon complete
    Wire.endTransmission();    // stop transmitting
    delay(10);
    
    Wire.beginTransmission(15); // dmx lighting
    Wire.write(1);              // start intro stuff
    //start the intro
    Wire.endTransmission();    // stop transmitting
    delay(10); 

    
  }
}


  if(gameIntroStarted){
    GameIntroOnce = true;
    Wire.beginTransmission(7); // dmx lighting
    Wire.write(7);              // start intro stuff
    //start the intro
    Wire.endTransmission();    // stop transmitting
    delay(10); 

    Wire.beginTransmission(14); // dmx lighting
    Wire.write(91);              // start intro stuff
    //start the intro
    Wire.endTransmission();    // stop transmitting
    delay(10); 

    Wire.beginTransmission(4); // 4 Juke box 
    Wire.write(1);              // Play Track 1
    Wire.endTransmission();    // stop transmitting
    delay(10);

    Wire.beginTransmission(1); // linear actuator 
    Wire.write(2);              // open cover
    Wire.endTransmission();    // stop transmitting
    delay(10);

    djDoorCanOpen = true;
  
    gameIntroStarted = false;
    
  }

 if(gameSetUP){

//set up the game
    Wire.beginTransmission(14); // dmx lighting
    Wire.write(90);              // start intro stuff
    //start the intro
    Wire.endTransmission();    // stop transmitting
    delay(10); 

    Wire.beginTransmission(7); // dmx lighting
    Wire.write(8);              // start intro stuff
    //start the intro
    Wire.endTransmission();    // stop transmitting
    delay(10); 

    Wire.beginTransmission(14); // dmx lighting
    Wire.write(5);              // TURN ALL GRID OFF
    //start the intro
    Wire.endTransmission();    // stop transmitting
    delay(10); 
    
  gameSetUP = false;
 }

 if(GameWinTotal){

    Wire.beginTransmission(7); // dmx lighting
    Wire.write(9);              // start intro stuff
    //start the intro
    Wire.endTransmission();    // stop transmitting
   
   delay(10); 

     Wire.beginTransmission(4); // 4 audio main
          Wire.write(100);              // djbooth intro
          //start the intro
          Wire.endTransmission();    // stop transmitting
          delay(10);
          
 Wire.beginTransmission(1); // linear actuator 
    Wire.write(19);              // open cover
    Wire.endTransmission();    // stop transmitting
    delay(10);
    
    GameWinTotal = false;
  
 }

 if(GameOverTime){
  
  Wire.beginTransmission(7); // dmx lighting
    Wire.write(9);              // start intro stuff
    //start the intro
    Wire.endTransmission();    // stop transmitting
   
   delay(10); 

     Wire.beginTransmission(4); // 4 audio main
          Wire.write(80);              // game over time
          //start the intro
          Wire.endTransmission();    // stop transmitting
          delay(10);

    GameOverTime = false;
    GameWinTotal = false;
 }
 if(EPANELThree){
  if(MusicUp){
     Wire.beginTransmission(4); // 4 audio main
      Wire.write(10);              // start intro stuff
      //start the intro
      Wire.endTransmission();    // stop transmitting
      delay(10);
      MusicUp = false;
  }
  
  if(MusicDown){
     Wire.beginTransmission(4); // 4 audio main
     Wire.write(11);              // start intro stuff
     //start the intro
     Wire.endTransmission();    // stop transmitting
     delay(10);
     MusicDown = false;
  }
 }
 
  char c;
  //delay(10);
  //Serial.println("a");
  if(Serial.available())  
  {
    
   
   c = Serial.read();
   //Serial.print(c);  
  
  //delay(100);
  if(c == '1'){
    
  }else if(c == '2'){
    
  }else if(c == '3'){
    //generator override
    if(!GameIntroOnce){
      Wire.beginTransmission(4); // 4 audio main
    Wire.write(1);              // start intro stuff
    //start the intro
    Wire.endTransmission();    // stop transmitting
    delay(10);
    gameIntroStarted = true;
    }
    
  }else if(c == '4'){
    Wire.beginTransmission(4); // 4 audio main
    Wire.write(2);              // red lights
    Wire.endTransmission();    // stop transmitting
    delay(10);
    // autofail
  }else if(c == '5'){//
    Wire.beginTransmission(4); // 7 is dmx board
    Wire.write(3);              // normal or out lights
    Wire.endTransmission();    // stop transmitting
    delay(10);
    // success button pressed
  }else if(c == '6'){
    Wire.beginTransmission(4); // 4
    Wire.write(4);              // green lights
    Wire.endTransmission();    // stop transmitting
    delay(10);
    //no loop
  }else if(c == '7'){
    
  }else if(c == '8'){
    
  }else if(c == '9'){
    
  }else if(c == 'A'){
    Wire.beginTransmission(3); // lights on
    Wire.write(1);              // 1
    Wire.endTransmission();    // stop transmitting
    delay(10);
  }else if(c == 'B'){
    Wire.beginTransmission(3); // 7 is dmx board
    Wire.write(2);              // green lights
    Wire.endTransmission();    // stop transmitting
    delay(10);
  }else if(c == 'C'){
    Wire.beginTransmission(3); // 7 is dmx board
    Wire.write(3);              // green lights
    Wire.endTransmission();    // stop transmitting
    delay(10);
  }else if(c == 'D'){
    Wire.beginTransmission(3); // 7 is dmx board
    Wire.write(4);              // green lights
    Wire.endTransmission();    // stop transmitting
    delay(10);
  }else if(c == 'E'){
    Wire.beginTransmission(3); // 7 is dmx board
    Wire.write(5);              // green lights
    Wire.endTransmission();    // stop transmitting
    delay(10);
  }else if(c == 'F'){
    Wire.beginTransmission(3); // 7 is dmx board
    Wire.write(6);              // green lights
    Wire.endTransmission();    // stop transmitting
    delay(10);
  }else if(c == 'G'){
    Wire.beginTransmission(3); // 7 is dmx board
    Wire.write(7);              // green lights
    Wire.endTransmission();    // stop transmitting
    delay(10);
  }else if(c == 'H'){
    Wire.beginTransmission(3); // lights on
    Wire.write(8);              // 8
    Wire.endTransmission();    // stop transmitting
    delay(10);
  }else if(c == 'I'){
    Wire.beginTransmission(7); // 7 is dmx board
    Wire.write(1);              // green lights
    Wire.endTransmission();    // stop transmitting
    delay(10);
  }else if(c == 'J'){
    Wire.beginTransmission(7); // 7 is dmx board
    Wire.write(2);              // BLUE lights
    Wire.endTransmission();    // stop transmitting
    delay(10);
  }else if(c == 'K'){
    Wire.beginTransmission(7); // 7 is dmx board
    Wire.write(3);              // RED lights
    Wire.endTransmission();    // stop transmitting
    delay(10);
  }else if(c == 'L'){
    Wire.beginTransmission(7); // 7 is dmx board
    Wire.write(4);              // YELLOW lights
    Wire.endTransmission();    // stop transmitting
    delay(10);
  }else if(c == 'M'){
    Wire.beginTransmission(7); // NORMAL on
    Wire.write(5);              // 8
    Wire.endTransmission();    // stop transmitting
    delay(10);
  }else if(c == 'S'){
    Wire.beginTransmission(7); // 
    Wire.write(6);              // 
    Wire.endTransmission();    // stop transmitting
    delay(10);
  }else if(c == 'T'){
    Wire.beginTransmission(7); // 
    Wire.write(12);              // 
    Wire.endTransmission();    // stop transmitting
    delay(10);
  }else if(c == 'V'){
    Wire.beginTransmission(7); // 
    Wire.write(5);              // 
    Wire.endTransmission();    // stop transmitting
    delay(10);
  }else if(c == 'W'){
    Wire.beginTransmission(7); // 
    Wire.write(5);              // 
    Wire.endTransmission();    // stop transmitting
    delay(10);
  }else if(c == 'X'){
    Wire.beginTransmission(7); // 
    Wire.write(5);              // 
    Wire.endTransmission();    // stop transmitting
    delay(10);
  }else if(c == 'Y'){
    Wire.beginTransmission(7); // 
    Wire.write(5);              // 
    Wire.endTransmission();    // stop transmitting
    delay(10);
  }else if(c == 'Z'){
    Wire.beginTransmission(7); // 
    Wire.write(5);              // 
    Wire.endTransmission();    // stop transmitting
    delay(10);
  }
  //Binary MagLOck
  else if( c == 'R'){
    Wire.beginTransmission(9); // Patch Simon Bin 
    Wire.write(1);              // Unlock Magnet
    Wire.endTransmission();    // stop transmitting
    delay(10);
    PatchStart = true;
 /*   
  Wire.beginTransmission(4); // 4 Juke box 
    Wire.write(21);              // Simon complete
    Wire.endTransmission();    // stop transmitting
    delay(10);
   */ 
    Wire.beginTransmission(15); // audio
    Wire.write(3);              // all four
    Wire.endTransmission();    // stop transmitting
    delay(10); 


    Wire.beginTransmission(4); // 4 Juke box 
    Wire.write(21);              //  bin complete
    Wire.endTransmission();    // stop transmitting
    delay(10);
    
    
  }
  else if( c == '+'){
    Serial.write('=');//signal echo
    delay(5);
  }
  else if( c == 'z'){
    Wire.beginTransmission(4); // 4 Juke box 
    Wire.write(1);              // Play Track 1
    Wire.endTransmission();    // stop transmitting
  //  delay(100);
  
    Wire.beginTransmission(8); // 8 MP3
    Wire.write(2);              // Play Track 2
    Wire.endTransmission();    // stop transmitting
  //  delay(100);
  }
  else if( c == 'y'){
    Wire.beginTransmission(4); // 4 Juke box 
    Wire.write(2);              // Play Track 2
    Wire.endTransmission();    // stop transmitting
    delay(100);
    
    Wire.beginTransmission(8); // 8 MP3
    Wire.write(101);              // music sound 50 percent
    Wire.endTransmission();    // stop transmitting
    delay(100);
  }
  else if( c == 'x'){
    Wire.beginTransmission(3); // 4 Juke box 
    Wire.write(1);              // Play Track 2
    Wire.endTransmission();    // stop transmitting
    digitalWrite(13, !digitalRead(13));
    delay(100);
    Wire.beginTransmission(8); // 8 MP3
    Wire.write(100);              // music sound 50 percent
    Wire.endTransmission();    // stop transmitting
    delay(100);
 //  Serial.print(c);  
  }else if(c == '@'){ // grid 3 on
    Wire.beginTransmission(14); // 14 is grid board
    Wire.write(1);              // blue lights
    Wire.endTransmission();    // stop transmitting
    delay(1);
  }else if(c == '^'){ // grid 5 on
    Wire.beginTransmission(14); // 14 is grid board 
    Wire.write(2);              // yellow lights
    Wire.endTransmission();    // stop transmitting
    delay(1);
  }else if(c == '%'){ // grid 7 on
    Wire.beginTransmission(14); // 14 is grid board
    Wire.write(3);              // red lights
    Wire.endTransmission();    // stop transmitting
    delay(1);
  }else if(c == '~'){// grid 8 on
    Wire.beginTransmission(14); // 14 is grid board
    Wire.write(4);              // normal or out lights
    Wire.endTransmission();    // stop transmitting
    delay(1);
  }else if(c == '('){ //grid all on
    Wire.beginTransmission(14); // 14 is grid board
    Wire.write(5);              // green lights
    Wire.endTransmission();    // stop transmitting
    delay(1);
  }else if(c == ')'){ // grid all off
    Wire.beginTransmission(14); // 14 is grid board
    Wire.write(6);              // green lights
    Wire.endTransmission();    // stop transmitting
    delay(1);
  }else if(c == '$'){
    Wire.beginTransmission(14); // 14 is grid board
    Wire.write(32);              //binary start
    Wire.endTransmission();    // stop transmitting
    delay(10);
  }else if(c == 'a'){
    Wire.beginTransmission(21); // lights on
    Wire.write(1);              // 1
    Wire.endTransmission();    // stop transmitting
    delay(10);
  }else if(c == 'b'){
    Wire.beginTransmission(21); // 7 is dmx board
    Wire.write(2);              // green lights
    Wire.endTransmission();    // stop transmitting
    delay(10);
  }else if(c == 'c'){
    Wire.beginTransmission(21); // 7 is dmx board
    Wire.write(3);              // green lights
    Wire.endTransmission();    // stop transmitting
    delay(10);
  }else if(c == 'd'){
    Wire.beginTransmission(21); // 7 is dmx board
    Wire.write(4);              // green lights
    Wire.endTransmission();    // stop transmitting
    delay(10);
  }else if(c == 'e'){
    Wire.beginTransmission(21); // 7 is dmx board
    Wire.write(5);              // green lights
    Wire.endTransmission();    // stop transmitting
    delay(10);
  }else if(c == 'f'){
    Wire.beginTransmission(21); // 7 is dmx board
    Wire.write(6);              // green lights
    Wire.endTransmission();    // stop transmitting
    delay(10);
  }else if(c == 'g'){
    Wire.beginTransmission(21); // 7 is dmx board
    Wire.write(7);              // green lights
    Wire.endTransmission();    // stop transmitting
    delay(10);
  }else if(c == 'h'){
    Wire.beginTransmission(21); // lights on
    Wire.write(8);              // 8
    Wire.endTransmission();    // stop transmitting
    delay(10);
  }else if(c == 'i'){
    Wire.beginTransmission(21); // 7 is dmx board
    Wire.write(9);              // green lights
    Wire.endTransmission();    // stop transmitting
    delay(10);
  }else if(c == 'j'){
    Wire.beginTransmission(21); // 
    Wire.write(10);              // 
    Wire.endTransmission();    // stop transmitting
    delay(10);
  }else if(c == 'l'){
    Wire.beginTransmission(21); // 
    Wire.write(11);              // 
    Wire.endTransmission();    // stop transmitting
    delay(10);
   }
   else if(c == 'N'){
  //Mag lock for lights on game
   Wire.beginTransmission(14); // 
    Wire.write(10);              // 
    Wire.endTransmission();    // stop transmitting
    delay(10);
}else if(c == 'O'){
  //Mag lock for Ten lights game
  Wire.beginTransmission(14); // 
    Wire.write(11);              // 
    Wire.endTransmission();    // stop transmitting
    delay(10);
}else if(c == 'P'){
    //Mag lock for DJbooth after simon is complete
    // Wire.beginTransmission(1); //
    //Wire.write(1);              // 
    //Wire.endTransmission();    // stop transmitting
    //delay(10);
    
    Wire.beginTransmission(4); //
    Wire.write(22);            // 
    Wire.endTransmission();    // stop transmitting
    delay(10);
    Wire.beginTransmission(14); //
    Wire.write(9);              // 
    Wire.endTransmission();    // stop transmitting
    delay(10);
    
    //p1 = true;
    //p2 = true;
    //p3 = true;
    //PatchStart = true;
    
  }else if(c == 'Q'){
    // Game over time up
    GameOverTime = true;
  }else if(c == 'U'){
    p1 = true;
    p2 = true;
    p3 = true;
  }
}

  delay(10);
Wire.requestFrom(1, 1);    // request 1 bytes from slave device #23
while (Wire.available()) { // slave may send less than requested
    char c = Wire.read(); // receive a byte as character
    //delay(14);
    if(c == 1){
      if(GameIntroOnce){
        Serial.write('!'); // Gen Switch down from powered up
        WORKINGgames = false;
      }
    }
      if(c == 2){
        if(!GameIntroOnce){
          Serial.write('0'); // Gen Switch powered up
          gameIntroStarted = true;
        }else{
          //generator back up from being down after start up
          WORKINGgames = true;
          Serial.write('?'); // Gen Switch powered up
        }
        
      }else if(c == 3){
        if(GenOFFGameWin){
          Serial.write('9'); // Gen Switch powered down
          //Game win here
          GameWinTotal = true;
        }
      }else if(c == 4){
        
    Serial.write('w'); //  SWITCH Binary High
    Wire.beginTransmission(4); // 4 Juke box 
    Wire.write(21);              //  bin complete
    Wire.endTransmission();    // stop transmitting
    delay(10);
    
}else if(c == 5){
  //correct input from epanel 3
  if(EPANELThree){
    Wire.beginTransmission(4); // 4 Juke box 
    Wire.write(24);              // epanel 3 complete
    Wire.endTransmission();    // stop transmitting
    delay(10);
    GenOFFGameWin = true;
     // Serial.write('%'); // epanel 3 dj booth input
  }
      }else if(c == 6){

      }else if(c == 7){

      }else if(c == 8){
        //has to be closed at start of the game
        if(djDoorCanOpen){
          
          Wire.beginTransmission(4); // 4 audio main
          Wire.write(20);              // djbooth intro
          //start the intro
          Wire.endTransmission();    // stop transmitting
          delay(10);
          
          Serial.write('#');// the dj booth door opened up

          djDoorCanOpen = false;
        }
      }else if(c == 9){
        MusicUp = true;
      }else if(c == 10){
        MusicDown = true;
      }
  }
  delay(10);
//  if(WORKINGgames){
  Wire.requestFrom(2, 1);    // request 1 bytes from slave device #2
while (Wire.available()) { // slave may send less than requested
    char c = Wire.read(); // receive a byte as character
      delay(14);
      if(c == 2){
        Serial.write('1'); // 1 SWITCH 
      }else if(c == 3){
        Serial.write('2'); // 2 SWITCH 
      }else if(c == 4){
        Serial.write('3'); // 3 SWITCH 
      }else if(c == 5){
        Serial.write('4'); // 4 SWITCH 
      }else if(c == 6){
        Serial.write('5'); // 5 SWITCH 
      }else if(c == 7){
        Serial.write('6'); // 6 SWITCH 
      }else if(c == 8){
        Serial.write('7'); // 7 SWITCH 
      }else if(c == 9){
        Serial.write('8'); // 8 SWITCH 
      }else if(c == 10){
        Serial.write('9'); // 9 SWITCH 
      }else if(c == 11){
        Serial.write('Z'); // 10 SWITCH 
      }
  }
//}
 //Serial.println("d");
//delay(10);
//if(WORKINGgames){
  Wire.requestFrom(10, 1);    // request 1 bytes from slave device #10
while (Wire.available()) { // slave may send less than requested
    char c = Wire.read(); // receive a byte as character
    delay(10);
    if(c == 2){
        Serial.write('a'); // 1 SWITCH 
      }else if(c == 3){
        Serial.write('b'); // 2 SWITCH 
      }else if(c == 4){
        Serial.write('c'); // 3 SWITCH 
      }else if(c == 5){
        Serial.write('d'); // 4 SWITCH 
      }else if(c == 6){
        Serial.write('e'); // 5 SWITCH 
      }else if(c == 7){
        Serial.write('f'); // 6 SWITCH 
      }else if(c == 8){
        Serial.write('g'); // 7 SWITCH 
      }else if(c == 9){
        Serial.write('h'); // 8 SWITCH 
      }
  }
//}
// Serial.println("e");
delay(2);
//if(WORKINGgames){
  Wire.requestFrom(19, 1);    // request 1 bytes from slave device #2
while (Wire.available()) { // slave may send less than requested
    char c = Wire.read(); // receive a byte as character
    delay(2);
    if(c == '1'){
        Serial.write('o'); // 1 SWITCH Green 1
        delay(10); 
           Wire.beginTransmission(7); // dmx lighting
          Wire.write(1);              // start intro stuff
    //start the intro
          Wire.endTransmission();    // stop transmitting
          delay(10); 
    
      }else if(c == '2'){
        Serial.write('p'); // 2 SWITCH Green 2
        delay(10); 
        Wire.beginTransmission(7); // dmx lighting
        Wire.write(1);              // start intro stuff
        //start the intro
        Wire.endTransmission();    // stop transmitting
         delay(10); 
    
      }else if(c == '3'){
        Serial.write('q'); // 3 SWITCH Red 1
        delay(10); 
             Wire.beginTransmission(7); // dmx lighting
    Wire.write(4);              // start intro stuff
    //start the intro
    Wire.endTransmission();    // stop transmitting
    delay(10); 
    
      }else if(c == '4'){
        Serial.write('r'); // 4 SWITCH Red 2
        delay(10); 
          Wire.beginTransmission(7); // dmx lighting
    Wire.write(4);              // start intro stuff
    //start the intro
    Wire.endTransmission();    // stop transmitting
    delay(10); 
    
      }else if(c == '5'){
        Serial.write('s'); // 5 SWITCH Blue 1
        delay(10); 
           Wire.beginTransmission(7); // dmx lighting
    Wire.write(2);              // start intro stuff
    //start the intro
    Wire.endTransmission();    // stop transmitting
    delay(10); 
    
      }else if(c == '6'){
        Serial.write('t'); // 6 SWITCH Blue 2
        delay(10); 
          Wire.beginTransmission(7); // dmx lighting
    Wire.write(4);              // start intro stuff
    //start the intro
    Wire.endTransmission();    // stop transmitting
    delay(10); 
    
      }else if(c == '7'){
        Serial.write('u'); // 7 SWITCH Yellow 1
        delay(10); 
          Wire.beginTransmission(7); // dmx lighting
    Wire.write(3);              // start intro stuff
    //start the intro
    Wire.endTransmission();    // stop transmitting
    delay(10); 
    
      }else if(c == '8'){
        Serial.write('v'); // 8 SWITCH Yellow 2
        delay(10); 
         Wire.beginTransmission(7); // dmx lighting
    Wire.write(3);              // start intro stuff
    //start the intro
    Wire.endTransmission();    // stop transmitting
    delay(10); 

      }// Patch inputs here
 else if(c == '9'){
  p1 = true;
         // 6 SWITCH Patch 1 high
  /*   p1 = true;
     if(p2){
          // 2 true if 1 is also true the game will win
          Wire.beginTransmission(15); // dmx lighting
          Wire.write(2);              // start intro stuff
          //start the intro
          Wire.endTransmission();    // stop transmitting
          delay(10); 
    
    }else if(p3){
      // 3 true if 1 is also true the game will win
      Wire.beginTransmission(15); // dmx lighting
      Wire.write(2);              // start intro stuff
      //start the intro
      Wire.endTransmission();    // stop transmitting
      delay(10); 
      
    }else{
      Wire.beginTransmission(15); // dmx lighting
      Wire.write(3);              // start intro stuff
      //start the intro
      Wire.endTransmission();    // stop transmitting
      delay(10); 
      
    }
*/
    
  /*  Wire.beginTransmission(7); // dmx lighting
    Wire.write(1);              // start intro stuff
    //start the intro
    Wire.endTransmission();    // stop transmitting
    delay(10); 

    */
      }else if(c == 'A'){
       // Serial.write('j'); // 7 SWITCH Patch 2 high
 p2 = true;
/*
      p2 = true;
      if(p1){
          // 2 true if 1 is also true the game will win
          Wire.beginTransmission(15); // dmx lighting
          Wire.write(2);              // start intro stuff
          //start the intro
          Wire.endTransmission();    // stop transmitting
          delay(10); 
    
    }else if(p3){
      // 3 true if 1 is also true the game will win
      Wire.beginTransmission(15); // dmx lighting
      Wire.write(2);              // start intro stuff
      //start the intro
      Wire.endTransmission();    // stop transmitting
      delay(10); 
      
    }else{
      Wire.beginTransmission(15); // dmx lighting
      Wire.write(3);              // start intro stuff
      //start the intro
      Wire.endTransmission();    // stop transmitting
      delay(10); 

    }

   Wire.beginTransmission(7); // dmx lighting
    Wire.write(2);              // start intro stuff
    //start the intro
    Wire.endTransmission();    // stop transmitting
    delay(10); 
    */
      
    
      }else if(c == 'B'){
      //  Serial.write('k'); // 8 SWITCH Patch 3 high
		p3 = true;
 /*   p3 = true;
    if(p1){
          // 2 true if 1 is also true the game will win
          Wire.beginTransmission(15); // dmx lighting
          Wire.write(2);              // start intro stuff
          //start the intro
          Wire.endTransmission();    // stop transmitting
          delay(10); 
    
    }else if(p2){
      // 3 true if 1 is also true the game will win
      Wire.beginTransmission(15); // dmx lighting
      Wire.write(2);              // start intro stuff
      //start the intro
      Wire.endTransmission();    // stop transmitting
      delay(10); 
      
    }else{
      Wire.beginTransmission(15); // dmx lighting
      Wire.write(3);              // start intro stuff
      //start the intro
      Wire.endTransmission();    // stop transmitting
      delay(10); 

    }

         Wire.beginTransmission(7); // dmx lighting
    Wire.write(3);              // start intro stuff
    //start the intro
    Wire.endTransmission();    // stop transmitting
    delay(10);;
    */


      }else if(c == 'C'){
        Serial.write('l'); // 7 SWITCH Patch 1 low
        Wire.beginTransmission(7); // dmx lighting
		Wire.write(5);              // start intro stuff
    //start the intro
		Wire.endTransmission();    // stop transmitting
		delay(10); 
		p1 = false;
  /*  
    if(p2 && p3){
      //two correct
      Wire.beginTransmission(15); // dmx lighting
      Wire.write(2);              // start intro stuff
      //start the intro
      Wire.endTransmission();    // stop transmitting
      delay(10); 
    }else if(p2 || p3){
      //one correct
      Wire.beginTransmission(15); // dmx lighting
      Wire.write(3);              // start intro stuff
      //start the intro
      Wire.endTransmission();    // stop transmitting
      delay(10); 
    }else{
      Wire.beginTransmission(15); // dmx lighting
      Wire.write(4);              // start intro stuff
      //start the intro
      Wire.endTransmission();    // stop transmitting
      delay(10); 
    }
*/
    
      }else if(c == 'D'){
        Serial.write('m'); // 8 SWITCH Patch 2 low
         Wire.beginTransmission(7); // dmx lighting
         Wire.write(5);              // start intro stuff
         //start the intro
         Wire.endTransmission();    // stop transmitting
         delay(10);
         p2 = false; 
/*
    p2 = false;
    if(p1 && p3){
      //two correct
      Wire.beginTransmission(15); // dmx lighting
      Wire.write(2);              // start intro stuff
      //start the intro
      Wire.endTransmission();    // stop transmitting
      delay(10); 
    }else if(p1 || p3){
      //one correct
      Wire.beginTransmission(15); // dmx lighting
      Wire.write(3);              // start intro stuff
      //start the intro
      Wire.endTransmission();    // stop transmitting
      delay(10); 
    }else{
      Wire.beginTransmission(15); // dmx lighting
      Wire.write(4);              // start intro stuff
      //start the intro
      Wire.endTransmission();    // stop transmitting
      delay(10); 
    }
*/
    
      }else if(c == 'E'){
        Serial.write('n'); // 7 SWITCH Patch 3 low
         Wire.beginTransmission(7); // dmx lighting
    Wire.write(5);              // start intro stuff
    //start the intro
    Wire.endTransmission();    // stop transmitting
    delay(10); 
    p3 = false;
/*
    p3 = false;
    if(p1 && p2){
      //two correct
      Wire.beginTransmission(15); // dmx lighting
      Wire.write(2);              // start intro stuff
      //start the intro
      Wire.endTransmission();    // stop transmitting
      delay(10); 
    }else if(p1 || p2){
      //one correct
      Wire.beginTransmission(15); // dmx lighting
      Wire.write(3);              // start intro stuff
      //start the intro
      Wire.endTransmission();    // stop transmitting
      delay(10); 
    }else{
      Wire.beginTransmission(15); // dmx lighting
      Wire.write(4);              // start intro stuff
      //start the intro
      Wire.endTransmission();    // stop transmitting
      delay(10); 
    }
*/
    
      }else if(c == 'F'){
        
        
      }else if(c == '%'){
        
      }
  }
//}
 //Serial.println("f");
delay(10);
Wire.requestFrom(4, 1);    // request 1 bytes from slave device #4
 while(Wire.available()) { // slave may send less than requested
    char c = Wire.read(); // receive a byte as character
      //delay(14);
    if(c == 1){
        Serial.write('@'); // autofail to next song
      }
      if(c == 1){
       // Serial.write('#'); 
      }
    }
 // delay(13);

  //Serial.println("b");

//delay(10);
}

// End of main loop


//-------------------------------------------------------------------------------------------------------------------------------
