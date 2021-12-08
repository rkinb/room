// Wire Slave Receiver

//INCLUDES ****************************************
#include <Wire.h>
//#include <DmxMaster.h>

//MUSIC SHIELD STUFF***********************************************************************
// include SPI, MP3 and SD libraries
#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>
#include <Wire.h>

// define the pins used
#define CLK 13       // SPI Clock, shared with SD card
#define MISO 12      // Input data, from VS1053/SD card
#define MOSI 11      // Output data, to VS1053/SD card
// Connect CLK, MISO and MOSI to hardware SPI pins. 
// See http://arduino.cc/en/Reference/SPI "Connections"

// These are the pins used for the breakout example
#define BREAKOUT_RESET  9      // VS1053 reset pin (output)
#define BREAKOUT_CS     10     // VS1053 chip select pin (output)
#define BREAKOUT_DCS    8      // VS1053 Data/command select pin (output)
// These are the pins used for the music maker shield
#define SHIELD_RESET  -1      // VS1053 reset pin (unused!)
#define SHIELD_CS     7      // VS1053 chip select pin (output)
#define SHIELD_DCS    6      // VS1053 Data/command select pin (output)

// These are common pins between breakout and shield
#define CARDCS 4     // Card chip select pin
// DREQ should be an Int pin, see http://arduino.cc/en/Reference/attachInterrupt
#define DREQ 3       // VS1053 Data request, ideally an Interrupt pin

Adafruit_VS1053_FilePlayer musicPlayer = 
  // create breakout-example object!
 // Adafruit_VS1053_FilePlayer(BREAKOUT_RESET, BREAKOUT_CS, BREAKOUT_DCS, DREQ, CARDCS);
  // create shield-example object!
  Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);
  //****************************************************************************************


//VARIABLES *****************************************
int RETURN = 0; // valve from master.
int R1 = 0;
int SEND = 0;


//SETUP *****************************************************************
void setup() {
  
  //WIRE SETUP ....................................................
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent); // Request attention of master node
  //SERIAL.........................................................
  Serial.begin(9600);           // start serial for output
  Serial.println("Reciver ready Adress: 8 (MP3_BOARD_AI)");

  //MP3 SETUP........................................................
char fileName[16];                // SDcard uses 8.3 names so 16 bytes is enough NOte room for the '\0' char is needed!
 sprintf(fileName, "%d.mp3", R1);
 Serial.println(fileName);
 if (! musicPlayer.begin()) { // initialise the music player
     Serial.println(F("Can not find the sound board."));
     while (1);
  }
  Serial.println(F("MP3 Ready to go!"));
  SD.begin(CARDCS);    // initialise the SD card
  
  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(50,50);

  // Timer interrupts are not suggested, better to use DREQ interrupt!
  //musicPlayer.useInterrupt(VS1053_FILEPLAYER_TIMER0_INT); // timer int

  // If DREQ is on an interrupt pin (on uno, #2 or #3) we can do background
  // audio playing
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int
  
  // Play one file, don't return until complete
  //Serial.println(F("Playing track 001"));
  //musicPlayer.playFullFile("GLASS.mp3");
  // Play another file in the background, REQUIRES interrupts!
  //Serial.println(F("Playing track 002"));
  //musicPlayer.startPlayingFile("track002.mp3");



//musicPlayer.startPlayingFile("1.mp3"); // temp for tsting.
}








//MAIN LOOP ##################################################################################

void loop() {



musicPlayer.setVolume(10,10);
      char fileName[16];   
      sprintf(fileName, "%d.mp3", 1);
      musicPlayer.stopPlaying();
      musicPlayer.startPlayingFile(fileName);
      RETURN = 0;
      Serial.print("MP3 request from master TRACK: "); Serial.println(1);\

      delay(10000);

musicPlayer.setVolume(50,50);
      sprintf(fileName, "%d.mp3",2);
      musicPlayer.stopPlaying();
      musicPlayer.startPlayingFile(fileName);
      RETURN = 0;
      Serial.print("MP3 request from master TRACK: "); Serial.println(2);


    delay(10000);

  if(RETURN != 0){
    R1 = RETURN;
    
    if(R1 == 100){ musicPlayer.setVolume(0,0); Serial.print("MP3 LOUD from master:"); RETURN = 0;}
    if(R1 == 101){ musicPlayer.setVolume(50,50); Serial.print("MP3 SOFT from master:"); RETURN = 0;}
    
      if(R1 != 100 && R1 != 101){
      char fileName[16];   
      sprintf(fileName, "%d.mp3", R1);
      musicPlayer.stopPlaying();
      musicPlayer.startPlayingFile(fileName);
      RETURN = 0;
      Serial.print("MP3 request from master TRACK: "); Serial.println(R1);
      }
    }


 


//if(R1 == 1){musicPlayer.stopPlaying(); musicPlayer.startPlayingFile("1.mp3"); Serial.println("Playing track #1"); R1 = 0;}

    
 if(musicPlayer.playingMusic == true ){ // let master know track is playing
  SEND = 1;  
 }

 if(musicPlayer.playingMusic == false ){ // let master know it is done. 
  SEND = 2;  
 }
  
  digitalWrite(LED_BUILTIN, LOW); 
  delay(50);

 
}// End of main loop
//############################################################################################







//RECEIVE DATA FROM MASTER ***********************************************************

void receiveEvent(int howMany) {
         RETURN = Wire.read();           // receive byte as an integer
         Serial.println(RETURN);         // print the integer
}// end of function



// SEND DATA TO MASTER WHEN POLLED ***********************************************************

void requestEvent(){
  if(SEND != 0){ 
  digitalWrite(LED_BUILTIN, HIGH); // flash the LED to show data was sent. 
  Wire.write(8); // what slave it was sent from ( may not be used ) 
  Wire.write(SEND);  // send off the data to the master.
  delay(20);
  SEND = 0;
  }
  
 }// end of function
