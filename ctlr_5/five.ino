// Wire Slave Receiver

//INCLUDES ****************************************
#include <Wire.h>

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
#define DREQ 3       // VS1053 Data request, ideally an Interrupt pin

Adafruit_VS1053_FilePlayer musicPlayer = 
  // create breakout-example object!
  // create shield-example object!
  Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);
  //****************************************************************************************


//VARIABLES *****************************************
int x = 0;
//int STAGE = 1; // what stage of the program.
int SOLVED = 0;
int RETURN = 0;


int PatchState;
boolean PlayPatchSongOnce;
boolean playOnce = true;


//SETUP *****************************************************************
void setup() {

  
  

  //WIRE SETUP ....................................................
  Wire.begin(15);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
  //SERIAL.........................................................
  Serial.begin(9600);           // start serial for output

  //BUTTON SETUP...................................................
  //pinMode(LED_BUILTIN, OUTPUT); // LED
 

// pinMode(9, OUTPUT); //  Patch LED #4

//MP3 SETUP........................................................
char fileName[16];                // SDcard uses 8.3 names so 16 bytes is enough NOte room for the '\0' char is needed!
 sprintf(fileName, "%d.mp3", x);
 if (! musicPlayer.begin()) { // initialise the music player
     Serial.println(F("Can not find the sound board."));
     while (1);
  }
  Serial.println(F("MP3 Ready to go!"));
  SD.begin(CARDCS);    // initialise the SD card
  
  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(0,0);

  // If DREQ is on an interrupt pin (on uno, #2 or #3) we can do background
  // audio playing
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int
 
RETURN = 3;
PatchState = 0;
PlayPatchSongOnce = false;

}
//MAIN LOOP ##################################################################################

void loop() {
  
  switch(RETURN){
    case 1:
      PatchState = RETURN;
      RETURN = 0;
      PlayPatchSongOnce = true;
    break;
    case 2:
      PatchState = RETURN;
      RETURN = 0;
      PlayPatchSongOnce = true;
    break;
    case 3:
      PatchState = RETURN;
      RETURN = 0;
      PlayPatchSongOnce = true;
    break;
    case 4:
      PatchState = RETURN;
      RETURN = 0;
      PlayPatchSongOnce = true;
    break;
  }
  switch(PatchState){
    case 1:

      if(PlayPatchSongOnce){

        musicPlayer.setVolume(1,1);
        char fileName[16];   
        sprintf(fileName, "%d.mp3", 90);
        musicPlayer.stopPlaying();
        musicPlayer.startPlayingFile(fileName);
        
        PlayPatchSongOnce = false;
      
      }else{
        if(musicPlayer.playingMusic == false ){  
          PlayPatchSongOnce = true;
        }
      }
    break;
    case 2:

      if(PlayPatchSongOnce){

        musicPlayer.setVolume(1,1);
        char fileName[16];   
        sprintf(fileName, "%d.mp3", 90);
        musicPlayer.stopPlaying();
        musicPlayer.startPlayingFile(fileName);

        sprintf(fileName, "%d.mp3", 91);
        musicPlayer.startPlayingFile(fileName);
        
        PlayPatchSongOnce = false;

      
      }else{
        if(musicPlayer.playingMusic == false ){  
          PlayPatchSongOnce = true;
        }
      }
      
    break;
    
    case 3:


      if(PlayPatchSongOnce){

        musicPlayer.setVolume(1,1);
        char fileName[16];   
        sprintf(fileName, "%d.mp3", 111);
        musicPlayer.stopPlaying();
        musicPlayer.startPlayingFile(fileName);

     //   sprintf(fileName, "%d.mp3", 91);
      //  musicPlayer.startPlayingFile(fileName);
        
      //  sprintf(fileName, "%d.mp3", 92);
       // musicPlayer.startPlayingFile(fileName);
        
        PlayPatchSongOnce = false;
        RETURN = 50;
      
      }else{
        if(musicPlayer.playingMusic == false ){  
          PlayPatchSongOnce = true;
        }
      }
      
    break;
    case 4:
    
    if(PlayPatchSongOnce){
      
        musicPlayer.setVolume(1,1);
        char fileName[16];   
        sprintf(fileName, "%d.mp3", 90);
        musicPlayer.stopPlaying();
        musicPlayer.startPlayingFile(fileName);
        
        sprintf(fileName, "%d.mp3", 91);
        musicPlayer.startPlayingFile(fileName);
        
        sprintf(fileName, "%d.mp3", 92);
        musicPlayer.startPlayingFile(fileName); 
          
        sprintf(fileName, "%d.mp3", 93);
        musicPlayer.startPlayingFile(fileName);
        
        PlayPatchSongOnce = false;

      
      }else{
        if(musicPlayer.playingMusic == false ){  
          PlayPatchSongOnce = true;
        }
      }
      
    break;

   
  }
}
//90 is correct numbers
//91 is 2 correct
//92 is 1 correct 
//93 is zero correct

//RECEIVE DATA FROM MASTER ***********************************************************

void receiveEvent(int howMany) {
          RETURN = Wire.read();           // receive byte as an integer
          delay(10);
}// end of function
