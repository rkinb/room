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
int x = 0;
//int STAGE = 1; // what stage of the program.
int SOLVED = 0;
int RETURN = 0;
int TRACK = 30; // what track number is playing
int RT = 0; // request track to play.
int PLAYZ = 0; // 0 if able to be played and 1 if it is playing
int LOCKOUT = 0; // to lock out the buttons
int SEND = 50; // yellow button press to master
unsigned long time_now = 0; // setting of master time var.
int STAGE = 1; // current play loop
boolean DJinteractionSUCCESS = false;
boolean DJinteractionNOLOOPGO = false;
boolean PlayNextDJInteractionAUTOFAIL = false;
boolean PLAYStartDJInteraction = false;
int DJState = 0;
boolean DJnextSongAdvance = false;
boolean GameStarted = false;
boolean playOnce = true;
int switchIterator;
boolean DJBoothIntro;
char fileeName[16]; 

boolean freeze;
int OVERRIDE = 0; // master can over ride puzzle.

//SETUP *****************************************************************
void setup() {

freeze = false;
  DJBoothIntro = true;

  //WIRE SETUP ....................................................
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent); // Request attention of master node
  //SERIAL.........................................................
  Serial.begin(9600);           // start serial for output
  Serial.println("Reciver ready Adress: 4 (Juke Box)");

  //BUTTON SETUP...................................................
 
//MP3 SETUP........................................................
char fileName[16];                // SDcard uses 8.3 names so 16 bytes is enough NOte room for the '\0' char is needed!
 sprintf(fileName, "%d.mp3", x);
 Serial.println(fileName);
 if (! musicPlayer.begin()) { // initialise the music player
     Serial.println(F("Can not find the sound board."));
     while (1);
  }
  Serial.println(F("MP3 Ready to go!"));
  SD.begin(CARDCS);    // initialise the SD card
  
  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(0,0);

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

SOLVED = 0;
switchIterator = 0;


}







//MAIN LOOP ##################################################################################

void loop() {

  //Only sent the first time that the generator is powered up
    if(RETURN == 1){//this is from the generator first making contact to turn on and start the room up
      PLAYStartDJInteraction = true;
      GameStarted = true;
      RETURN = 0;
      DJState = 0;
    }
    if(RETURN == 8){
      DJState = 10;
      RETURN = 0;
    }else if(RETURN == 10){
      DJState = 9;
    }else if(RETURN == 11){
      DJState = 9;
    }else if(RETURN == 12){
      DJState = 11;
      RETURN = 0;
    }

  if(RETURN == 2){// auto fail system
    PlayNextDJInteractionAUTOFAIL = true;
    SEND = 1;
    RETURN = 0;
    DJnextSongAdvance = true;

       DJState++;
    if(DJState >= 7){
      //final playlist
      DJState == 7;
    }
    
  }else if(RETURN == 3){// success button
    DJinteractionSUCCESS = true;
  
    RETURN = 0;
    DJnextSongAdvance = true;
    
    DJState++;
    
    if(DJState >= 7){
      //final playlist
      DJState == 7;
    }
  }else if(RETURN == 4){ //no loop button
    DJinteractionNOLOOPGO = true;
    
    RETURN = 0;
    DJnextSongAdvance = true;
    
  }else if(RETURN == 20){
    DJState = 20;
      RETURN = 0;
  }else if(RETURN == 21){
    DJState = 21;
      RETURN = 0;
  }else if(RETURN == 22){
    DJState = 22;
      RETURN = 0;
  }else if(RETURN == 23){
    DJState = 23;
      RETURN = 0;
  }else if(RETURN == 24){
    DJState = 24;
      RETURN = 0;
  }else if(RETURN == 80){
    DJState = 80;
      RETURN = 0;
  }else if(RETURN == 100){
    DJState = 100;
      RETURN = 0;
  }
  switch(DJState){
    case 0:
      //DJ intro - interaction 1
      if(PLAYStartDJInteraction){
        // start the game intro
        musicPlayer.setVolume(1,1);
        char fileName[16];   
        sprintf(fileName, "%d.mp3", 0);
        musicPlayer.stopPlaying();
        musicPlayer.startPlayingFile(fileName);
        Serial.print("MP3 request from master TRACK: "); 

        //Turn on the linear actuator positive volt relay
        //digitalWrite(1, 1); // turn on the relay at digital output 1 for linear actuator
        //Turn on the Cam motor relay
        //digitalWrite(2, 1); // turn on the relay at digital output 2 for Cam motor
        PLAYStartDJInteraction = false;
        //Serial.println("song 1 - intro song");
      }else{
        if(GameStarted){
         if(musicPlayer.playingMusic == false ){  
           // SEND = 1; // this will be sent once a file plays through the entire song 
            RETURN = 2; // autofail to the next song
          }
        }
      }

      if(DJinteractionNOLOOPGO){
          //dj interaction not correct - go to NO Loop song
          musicPlayer.setVolume(0,0);
          char fileName[16];   
          sprintf(fileName, "%dA.mp3", DJState);
          musicPlayer.stopPlaying();
          musicPlayer.startPlayingFile(fileName);
          Serial.print("MP3 request from master TRACK: "); 
          DJnextSongAdvance = false;
          Serial.println("song 1 - NO Loop for song 1");
          DJinteractionNOLOOPGO = false;
        }
    
      
    break;
    case 1:
      if(DJnextSongAdvance){
        if(DJinteractionNOLOOPGO){
          //dj interaction not correct - go to NO Loop song
          musicPlayer.setVolume(0,0);
          char fileName[16];   
          sprintf(fileName, "%dA.mp3", DJState);
          musicPlayer.stopPlaying();
          musicPlayer.startPlayingFile(fileName);
          Serial.print("MP3 request from master TRACK: "); 
          DJnextSongAdvance = false;
          Serial.println("song 1 - NO Loop for song 1");
        
          DJinteractionNOLOOPGO = false;
        }else if(DJinteractionSUCCESS){
          //operator presses the dj interaction complete button - go to next case and song with success song
          musicPlayer.setVolume(0,0);
          char fileName[16];   
          sprintf(fileName, "%dC.mp3", DJState);
          musicPlayer.stopPlaying();
          musicPlayer.startPlayingFile(fileName);
          Serial.print("MP3 request from master TRACK: "); 
          DJnextSongAdvance = false;
          Serial.println("song 1 - success from intro song");
        
          DJinteractionSUCCESS = false;
        }else if(PlayNextDJInteractionAUTOFAIL){
          //Once the song is complete - autofail to the next case and the next song - go to autofail of next song
          musicPlayer.setVolume(0,0);
          char fileName[16];   
          sprintf(fileName, "%dB.mp3", DJState);
          musicPlayer.stopPlaying();
          musicPlayer.startPlayingFile(fileName);
          Serial.print("MP3 request from master TRACK: "); 
          DJnextSongAdvance = false;
          Serial.println("song 1 - autofail from intro song");
        
          PlayNextDJInteractionAUTOFAIL = false;
        }
        
      }else{
        if(musicPlayer.playingMusic == false ){ // let master know it is done. 
          //SEND = 1; // this will be sent once a file plays through the entire song 
          RETURN = 2; // autofail to the next song
        }
      }
        
        break;
    case 2:
       if(DJnextSongAdvance){
        if(DJinteractionNOLOOPGO){
          //dj interaction not correct - go to NO Loop song
          musicPlayer.setVolume(0,0);
          char fileName[16];   
          sprintf(fileName, "%dA.mp3", DJState);
          musicPlayer.stopPlaying();
          musicPlayer.startPlayingFile(fileName);
          Serial.print("MP3 request from master TRACK: "); 
          DJnextSongAdvance = false;
          Serial.println("song 2 - NO Loop from song 2");
        
          DJinteractionNOLOOPGO = false;
        }else if(DJinteractionSUCCESS){
          //operator presses the dj interaction complete button - go to next case and song with success song
          musicPlayer.setVolume(0,0);
          char fileName[16];   
          sprintf(fileName, "%dC.mp3", DJState);
          musicPlayer.stopPlaying();
          musicPlayer.startPlayingFile(fileName);
          Serial.print("MP3 request from master TRACK: "); 
          DJnextSongAdvance = false;
          Serial.println("song 2 - success from song 1");
        
          DJinteractionSUCCESS = false;
        }else if(PlayNextDJInteractionAUTOFAIL){
          //Once the song is complete - autofail to the next case and the next song - go to autofail of next song
          musicPlayer.setVolume(0,0);
          char fileName[16];   
          sprintf(fileName, "%dB.mp3", DJState);
          musicPlayer.stopPlaying();
          musicPlayer.startPlayingFile(fileName);
          Serial.print("MP3 request from master TRACK: "); 
          DJnextSongAdvance = false;
          Serial.println("song 2 - autofail from song 1");
        
          PlayNextDJInteractionAUTOFAIL = false;
        }
        
      }else{
        if(musicPlayer.playingMusic == false ){ // let master know it is done. 
        //  SEND = 1; // this will be sent once a file plays through the entire song 
          RETURN = 2; // autofail to the next song
        }
      }
    break;
    case 3:
      if(DJnextSongAdvance){
        if(DJinteractionNOLOOPGO){
          //dj interaction not correct - go to NO Loop song
          musicPlayer.setVolume(0,0);
          char fileName[16];   
          sprintf(fileName, "%dA.mp3", DJState);
          musicPlayer.stopPlaying();
          musicPlayer.startPlayingFile(fileName);
          Serial.print("MP3 request from master TRACK: "); 
          DJnextSongAdvance = false;
          Serial.println("song 3 - NO Loop from song 3");
        
          DJinteractionNOLOOPGO = false;
        }else if(DJinteractionSUCCESS){
          //operator presses the dj interaction complete button - go to next case and song with success song
          musicPlayer.setVolume(0,0);
          char fileName[16];   
          sprintf(fileName, "%dC.mp3", DJState);
          musicPlayer.stopPlaying();
          musicPlayer.startPlayingFile(fileName);
          Serial.print("MP3 request from master TRACK: "); 
          DJnextSongAdvance = false;
          Serial.println("song 3 - success from song 2");
        
          DJinteractionSUCCESS = false;
        }else if(PlayNextDJInteractionAUTOFAIL){
          //Once the song is complete - autofail to the next case and the next song - go to autofail of next song
          musicPlayer.setVolume(0,0);
          char fileName[16];   
          sprintf(fileName, "%dB.mp3", DJState);
          musicPlayer.stopPlaying();
          musicPlayer.startPlayingFile(fileName);
          Serial.print("MP3 request from master TRACK: "); 
          DJnextSongAdvance = false;
          Serial.println("song 3 - autofail from song 2");
        
          PlayNextDJInteractionAUTOFAIL = false;
        }
        
      }else{
        if(musicPlayer.playingMusic == false ){ // let master know it is done. 
        //  SEND = 1; // this will be sent once a file plays through the entire song 
          RETURN = 2; // autofail to the next song
        }
      }
    break;
    case 4:
      if(DJnextSongAdvance){
        if(DJinteractionNOLOOPGO){
          //dj interaction not correct - go to NO Loop song
          musicPlayer.setVolume(0,0);
          char fileName[16];   
          sprintf(fileName, "%dA.mp3", DJState);
          musicPlayer.stopPlaying();
          musicPlayer.startPlayingFile(fileName);
          Serial.print("MP3 request from master TRACK: "); 
          DJnextSongAdvance = false;
          Serial.println("song 3 - NO Loop from song 3");
        
          DJinteractionNOLOOPGO = false;
        }else if(DJinteractionSUCCESS){
          //operator presses the dj interaction complete button - go to next case and song with success song
          musicPlayer.setVolume(0,0);
          char fileName[16];   
          sprintf(fileName, "%dB.mp3", DJState);
          musicPlayer.stopPlaying();
          musicPlayer.startPlayingFile(fileName);
          Serial.print("MP3 request from master TRACK: "); 
          DJnextSongAdvance = false;
          Serial.println("song 3 - success from song 2");
        
          DJinteractionSUCCESS = false;
        }else if(PlayNextDJInteractionAUTOFAIL){
          //Once the song is complete - autofail to the next case and the next song - go to autofail of next song
          musicPlayer.setVolume(0,0);
          char fileName[16];   
          sprintf(fileName, "%dB.mp3", DJState);
          musicPlayer.stopPlaying();
          musicPlayer.startPlayingFile(fileName);
          Serial.print("MP3 request from master TRACK: "); 
          DJnextSongAdvance = false;
          Serial.println("song 3 - autofail from song 2");
        
          PlayNextDJInteractionAUTOFAIL = false;
        }
      }else{
        if(musicPlayer.playingMusic == false ){ // let master know it is done. 
       //   SEND = 1; // this will be sent once a file plays through the entire song 
          RETURN = 2; // autofail to the next song
        }
      }
    break;
    case 5:
      if(DJnextSongAdvance){
        if(DJinteractionNOLOOPGO){
          //dj interaction not correct - go to NO Loop song
          musicPlayer.setVolume(0,0);
          char fileName[16];   
          sprintf(fileName, "%dA.mp3", DJState);
          musicPlayer.stopPlaying();
          musicPlayer.startPlayingFile(fileName);
          Serial.print("MP3 request from master TRACK: "); 
          DJnextSongAdvance = false;
          Serial.println("song 3 - NO Loop from song 3");
        
          DJinteractionNOLOOPGO = false;
        }else if(DJinteractionSUCCESS){
          //operator presses the dj interaction complete button - go to next case and song with success song
          musicPlayer.setVolume(0,0);
          char fileName[16];   
          sprintf(fileName, "%dC.mp3", DJState);
          musicPlayer.stopPlaying();
          musicPlayer.startPlayingFile(fileName);
          Serial.print("MP3 request from master TRACK: "); 
          DJnextSongAdvance = false;
          Serial.println("song 3 - success from song 2");
        
          DJinteractionSUCCESS = false;
        }else if(PlayNextDJInteractionAUTOFAIL){
          //Once the song is complete - autofail to the next case and the next song - go to autofail of next song
          musicPlayer.setVolume(0,0);
          char fileName[16];   
          sprintf(fileName, "%dB.mp3", DJState);
          musicPlayer.stopPlaying();
          musicPlayer.startPlayingFile(fileName);
          Serial.print("MP3 request from master TRACK: "); 
          DJnextSongAdvance = false;
          Serial.println("song 3 - autofail from song 2");
        
          PlayNextDJInteractionAUTOFAIL = false;
        }
      }else{
        if(musicPlayer.playingMusic == false ){ // let master know it is done. 
       //   SEND = 1; // this will be sent once a file plays through the entire song 
          RETURN = 2; // autofail to the next song
        }
      }
    break;
    case 6:
      if(DJnextSongAdvance){
        if(DJinteractionNOLOOPGO){
          //dj interaction not correct - go to NO Loop song
          musicPlayer.setVolume(0,0);
          char fileName[16];   
          sprintf(fileName, "%dA.mp3", DJState);
          musicPlayer.stopPlaying();
          musicPlayer.startPlayingFile(fileName);
          Serial.print("MP3 request from master TRACK: "); 
          DJnextSongAdvance = false;
          Serial.println("song 3 - NO Loop from song 3");
        
          DJinteractionNOLOOPGO = false;
        }else if(DJinteractionSUCCESS){
          //operator presses the dj interaction complete button - go to next case and song with success song
          musicPlayer.setVolume(0,0);
          char fileName[16];   
          sprintf(fileName, "%dC.mp3", DJState);
          musicPlayer.stopPlaying();
          musicPlayer.startPlayingFile(fileName);
          Serial.print("MP3 request from master TRACK: "); 
          DJnextSongAdvance = false;
          Serial.println("song 3 - success from song 2");
        
          DJinteractionSUCCESS = false;
        }else if(PlayNextDJInteractionAUTOFAIL){
          //Once the song is complete - autofail to the next case and the next song - go to autofail of next song
          musicPlayer.setVolume(0,0);
          char fileName[16];   
          sprintf(fileName, "%dB.mp3", DJState);
          musicPlayer.stopPlaying();
          musicPlayer.startPlayingFile(fileName);
          Serial.print("MP3 request from master TRACK: "); 
          DJnextSongAdvance = false;
          Serial.println("song 3 - autofail from song 2");
        
          PlayNextDJInteractionAUTOFAIL = false;
        }
      }else{
        if(musicPlayer.playingMusic == false ){ // let master know it is done. 
    //      SEND = 1; // this will be sent once a file plays through the entire song 
          RETURN = 2; // autofail to the next song
        }
      }
    break;
    case 7:
      if(DJnextSongAdvance){
        if(DJinteractionNOLOOPGO){
          //dj interaction not correct - go to NO Loop song
          musicPlayer.setVolume(0,0);
          char fileName[16];   
          sprintf(fileName, "%dA.mp3", DJState);
          musicPlayer.stopPlaying();
          musicPlayer.startPlayingFile(fileName);
          Serial.print("MP3 request from master TRACK: "); 
          DJnextSongAdvance = false;
          Serial.println("song 3 - NO Loop from song 3");
        
          DJinteractionNOLOOPGO = false;
        }else if(DJinteractionSUCCESS){
          //operator presses the dj interaction complete button - go to next case and song with success song
          musicPlayer.setVolume(0,0);
          char fileName[16];   
          sprintf(fileName, "%dC.mp3", DJState);
          musicPlayer.stopPlaying();
          musicPlayer.startPlayingFile(fileName);
          Serial.print("MP3 request from master TRACK: "); 
          DJnextSongAdvance = false;
          Serial.println("song 3 - success from song 2");
        
          DJinteractionSUCCESS = false;
        }else if(PlayNextDJInteractionAUTOFAIL){
          //Once the song is complete - autofail to the next case and the next song - go to autofail of next song
          musicPlayer.setVolume(0,0);
          char fileName[16];   
          sprintf(fileName, "%dB.mp3", DJState);
          musicPlayer.stopPlaying();
          musicPlayer.startPlayingFile(fileName);
          Serial.print("MP3 request from master TRACK: "); 
          DJnextSongAdvance = false;
          Serial.println("song 3 - autofail from song 2");
        
          PlayNextDJInteractionAUTOFAIL = false;
        }
      }else{
        if(musicPlayer.playingMusic == false ){ // let master know it is done. 
    //      SEND = 1; // this will be sent once a file plays through the entire song 
          RETURN = 2; // autofail to the next song
        }
      }
    break;
    case 8:

 //Once the song is complete - autofail to the next case and the next song - go to autofail of next song
 
          if(TRACK > 37){
            TRACK = 30;
          }
          musicPlayer.setVolume(0,0);
          char fileName[16];   
          sprintf(fileName, "%d.mp3", TRACK);
          musicPlayer.stopPlaying();
          musicPlayer.startPlayingFile(fileName);
          DJState = 9;

 
    break;
    case 9:
       
  // IF track previous button
if (RETURN == 10){
   TRACK = TRACK - 1;
   if(TRACK < 30){TRACK = 37;}
  // musicPlayer.sineTest(0x43, 10);    // Make a tone to indicate VS1053 is working
  // musicPlayer.sineTest(0x46, 10);    // Make a tone to indicate VS1053 is working
   Serial.println("BUTTON: <-");
   delay(20);
   DJState = 8;
   RETURN = 0;
  }

// IF next track button
if (RETURN == 11){
   TRACK = TRACK + 1;
   if(TRACK > 37){TRACK = 30;}
   //musicPlayer.sineTest(0x43, 10);    // Make a tone to indicate VS1053 is working
   //musicPlayer.sineTest(0x46, 10);    // Make a tone to indicate VS1053 is working
   Serial.println("BUTTON: ->");
   delay(20);
   DJState = 8;
   RETURN = 0;
        
  }
  
   if(musicPlayer.playingMusic == false ){ // let master know it is done. 
    TRACK = TRACK + 1;
      if(TRACK > 37){
        TRACK = 30;
      }
      DJState = 8;
   }
    break;
    case 10:
    //DJ booth intro
    if(DJBoothIntro){
      musicPlayer.setVolume(0,0);
          char fileName[16];   
          sprintf(fileName, "%d.mp3", TRACK);
          musicPlayer.stopPlaying();
          musicPlayer.startPlayingFile(fileName);
          DJBoothIntro = false;
    }
      
   if(musicPlayer.playingMusic == false ){ // let master know it is done. 
    DJState = 8;
    //go to dj booth for the first time 
    TRACK = 30;//first dj song in list
    
   }

    break;
    case 11:
 musicPlayer.setVolume(0,0);
          sprintf(fileeName, "%d.mp3", 1);
          musicPlayer.stopPlaying();
          musicPlayer.startPlayingFile(fileeName);
          DJState = 9;
    break;
    case 12:
//game over time

 musicPlayer.setVolume(0,0);
          sprintf(fileeName, "%d.mp3", 1);
          musicPlayer.stopPlaying();
          musicPlayer.startPlayingFile(fileeName);
          DJState = 9;
    break;
    case 13:

    break;
    case 14:

    break;
    case 15:

    break;
    case 16:

    break;
    case 17:
//Reset the game
      DJState = 0;
      GameStarted = false;
      DJinteractionSUCCESS = false;
      DJinteractionNOLOOPGO = false;
      PlayNextDJInteractionAUTOFAIL = false;
      PLAYStartDJInteraction = false;
      DJnextSongAdvance = false;
      
    break;
    case 20:
    //dj booth intro
          musicPlayer.setVolume(0,0);
            
          sprintf(fileeName, "%d.mp3", 20);
          musicPlayer.stopPlaying();
          musicPlayer.startPlayingFile(fileeName);
          DJState = 9;
    break;
    case 21:
          musicPlayer.setVolume(0,0);
          sprintf(fileeName, "%d.mp3", 21);
          musicPlayer.stopPlaying();
          musicPlayer.startPlayingFile(fileeName);
          DJState = 9;
    break;
    case 22:
    //simon complete
           musicPlayer.setVolume(0,0);
          sprintf(fileeName, "%d.mp3", 22);
          musicPlayer.stopPlaying();
          musicPlayer.startPlayingFile(fileeName);
          DJState = 9;
    break;
    case 23:
    //patch complete
          musicPlayer.setVolume(0,0);
          sprintf(fileeName, "%d.mp3", 23);
          musicPlayer.stopPlaying();
          musicPlayer.startPlayingFile(fileeName);
          DJState = 9;
    break;
    case 24:
//epanel 3 complete
          musicPlayer.setVolume(0,0);
          sprintf(fileeName, "%d.mp3", 24);
          musicPlayer.stopPlaying();
          musicPlayer.startPlayingFile(fileeName);
          DJState = 9;
    break;

    case 80:
    //final game over time
          musicPlayer.setVolume(0,0);
          sprintf(fileeName, "%d.mp3", 80);
          musicPlayer.stopPlaying();
          musicPlayer.startPlayingFile(fileeName);
          DJState = 9;
    break;
    case 100:
// game win success
          musicPlayer.setVolume(0,0);
          sprintf(fileeName, "%d.mp3", 100);
          musicPlayer.stopPlaying();
          musicPlayer.startPlayingFile(fileeName);
          DJState = 9;
    break;
  }
}// End of  main loop

// 20 is dj booth intro success
// 21 is binary success
//22 is simon success
//23 is patch success
//24 djbooth success
//80 is final fail
//100 is final success

//RECEIVE DATA FROM MASTER ***********************************************************

void receiveEvent(int howMany) {
          RETURN = Wire.read();           // receive byte as an integer
    
}// end of function



// SEND DATA TO MASTER WHEN POLLED ***********************************************************

void requestEvent(){

 if(SEND == 1){
 //   Wire.write(4); // what slave it was sent from ( may not be used ) 
  Wire.write(0);  // send off the data to the master.
  //Serial.print("DATA sent to MASTER:"); 
    SEND = 50;  

  }

  
  
 }// end of function
