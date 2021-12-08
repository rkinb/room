//INCLUDES ****************************************
#include <Wire.h>


//VARIABLES *****************************************
int x = 0;
int STAGE = 0; // what stage of the program.
int SOLVED = 3;
int RETURN = 0; // what is received from master
int SEND = 0; // what to send to master
int LCOUNT = 0; // count var for led transision

// The Array used to store the grid value.
int GRID[] = {
  0,0,0,
  0,0,0,
  0,0,0};

//milisec timer
unsigned long startMillis;  //what to start with
unsigned long currentMillis; // current time
const unsigned long period = 500;  //the value is a number of milliseconds for how long to wait
const unsigned long Bperiod = 500; // this is how long to wait between binary flashes

//SETUP *****************************************************************
void setup() {
  
  //WIRE SETUP ....................................................
  Wire.begin(14);                // join i2c bus with address #14
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent); // Request attention of master node
  //SERIAL.........................................................
  Serial.begin(9600);           // start serial for output
  Serial.println("Reciver ready Adress: 14 (GRID_RELAY)");
   
  //BUTTON SETUP...................................................
  pinMode(LED_BUILTIN, OUTPUT); // LED
 // no inputs.

  pinMode(2, OUTPUT); // RELAY #1 ( Grid 1)
  pinMode(3, OUTPUT); // RELAY #2 ( Grid 2)
  pinMode(4, OUTPUT); // RELAY #3 ( Grid 3)
  pinMode(5, OUTPUT); // RELAY #4 ( Grid 4)
  pinMode(6, OUTPUT); // RELAY #5 ( Grid 5)
  pinMode(7, OUTPUT); // RELAY #6 ( Grid 6)
  pinMode(8, OUTPUT); // RELAY #7 ( Grid 7)
  pinMode(9, OUTPUT); // RELAY #8 ( Grid 8)
  pinMode(10, OUTPUT); // RELAY #9 ( Grid 9)
  pinMode(11, OUTPUT); // RELAY #10 (CLOSET DOOR maglock)
  pinMode(12, OUTPUT); // RELAY #11 ( EPANEL#3 door maglock)
  pinMode(A0, OUTPUT); // RELAY #12 ( AI DROP PANEL maglock)
  pinMode(A1, OUTPUT); // RELAY #13 ( N/C) // not used
  pinMode(A2, OUTPUT); // RELAY #14 ( N/C) // not used
  pinMode(A3, OUTPUT); // RELAY #15 ( N/C) // not used
// Relay #16 is not is use, and saved as a spare for now. 

// Turn them all off. 
digitalWrite(2, HIGH); 
digitalWrite(3, HIGH); 
digitalWrite(4, HIGH); 
digitalWrite(5, HIGH); 
digitalWrite(6, HIGH); 
digitalWrite(7, HIGH); 
digitalWrite(8, HIGH); 
digitalWrite(9, HIGH); 
digitalWrite(10, HIGH);//grid 9

 digitalWrite(11, HIGH); //dj cam motor on LOW is on HIGH is off
 digitalWrite(12, HIGH); //combo A0 HIGH and 12 LOW is dj door mag off
 digitalWrite(A0, LOW); //combo A0 LOW and 12 high is dj door mag on
 digitalWrite(A1, HIGH);//red lights turn on 
 digitalWrite(A2, LOW); //mag lock lights on game
 digitalWrite(A3, LOW); //mag lock for 10 lights game

 delay(100);
/*
 // Turn them all on. 
digitalWrite(2, LOW); 
digitalWrite(3, LOW); 
digitalWrite(4, LOW); 
digitalWrite(5, LOW); 
digitalWrite(6, LOW); 
digitalWrite(7, LOW); 
digitalWrite(8, LOW); 
digitalWrite(9, LOW); 
digitalWrite(10, LOW);

 digitalWrite(11, LOW); 
 digitalWrite(12, LOW); 
 digitalWrite(A0, LOW); 
 digitalWrite(A1, LOW); 
 digitalWrite(A2, LOW); 
 digitalWrite(A3, LOW); 

 delay(500);

 // Turn them all off. 
digitalWrite(2, HIGH); 
digitalWrite(3, HIGH); 
digitalWrite(4, HIGH); 
digitalWrite(5, HIGH); 
digitalWrite(6, HIGH); 
digitalWrite(7, HIGH); 
digitalWrite(8, HIGH); 
digitalWrite(9, HIGH); 
digitalWrite(10, HIGH);

 digitalWrite(11, HIGH); 
 digitalWrite(12, HIGH); 
 digitalWrite(A0, HIGH); 
 digitalWrite(A1, HIGH); 
 digitalWrite(A2, HIGH); 
 digitalWrite(A3, HIGH); 
  
*/


}








//MAIN LOOP ##################################################################################

void loop() {

// EVERYTHING OFF  just stay here and wait for command.
if(STAGE == 0){
// turn off all relays. 

 
}


//GRID: Idle animation **************************************
if(STAGE == 1){

currentMillis = millis();  //get the current "time" (actually the number of milliseconds since the program started)

 // if the time has passed.
 if (currentMillis - startMillis >= period){ //test whether the period has elapsed
  //* do something *
  LCOUNT = LCOUNT + 1;
  if(LCOUNT > 5){LCOUNT = 0; }// how many stages to the animation.
  startMillis = currentMillis; // reset the counter.
 }


//if(LCOUNT == 0){} // Stage 1 if doing animation. 


// Set them all on,
GRID[0] = 1; GRID[1] = 1; GRID[2] = 1;
GRID[3] = 1; GRID[4] = 1; GRID[5] = 1;
GRID[6] = 1; GRID[7] = 1; GRID[8] = 1;










// update the grid.
for(int i = 0; i < 9; i++){
  if(GRID[i] == 1){ digitalWrite(i + 2, LOW);} // turn off the relay
  if(GRID[i] == 0){ digitalWrite(i + 2, HIGH);} // turn on the relay
}









}
//************************************************************





//GRID: ATM code show **************************************
if(STAGE == 2){
// ATM CODE IS: 159873
currentMillis = millis();  //get the current "time" (actually the number of milliseconds since the program started)

 // if the time has passed.
 if (currentMillis - startMillis >= period){ //test whether the period has elapsed
  //* do something *
  LCOUNT = LCOUNT + 1;
  if(LCOUNT > 7){LCOUNT = 0; }// how many stages to the animation.
  startMillis = currentMillis; // reset the counter.
 }


if(LCOUNT == 0){// Stage 0
GRID[0] = 0; GRID[1] = 0; GRID[2] = 0;
GRID[3] = 0; GRID[4] = 0; GRID[5] = 0;
GRID[6] = 0; GRID[7] = 0; GRID[8] = 0;
}

if(LCOUNT == 1){// Stage 1
GRID[0] = 1; GRID[1] = 0; GRID[2] = 0;
GRID[3] = 0; GRID[4] = 0; GRID[5] = 0;
GRID[6] = 0; GRID[7] = 0; GRID[8] = 0;
}

if(LCOUNT == 2){// Stage 2
GRID[0] = 0; GRID[1] = 0; GRID[2] = 0;
GRID[3] = 0; GRID[4] = 1; GRID[5] = 0;
GRID[6] = 0; GRID[7] = 0; GRID[8] = 0;
}

if(LCOUNT == 3){// Stage 3
GRID[0] = 0; GRID[1] = 0; GRID[2] = 0;
GRID[3] = 0; GRID[4] = 0; GRID[5] = 0;
GRID[6] = 0; GRID[7] = 0; GRID[8] = 1;
}

if(LCOUNT == 4){// Stage 4
GRID[0] = 0; GRID[1] = 0; GRID[2] = 0;
GRID[3] = 0; GRID[4] = 0; GRID[5] = 0;
GRID[6] = 0; GRID[7] = 1; GRID[8] = 0;
}

if(LCOUNT == 5){// Stage 5
GRID[0] = 0; GRID[1] = 0; GRID[2] = 0;
GRID[3] = 0; GRID[4] = 0; GRID[5] = 0;
GRID[6] = 1; GRID[7] = 0; GRID[8] = 0;
}

if(LCOUNT == 6){// Stage 6
GRID[0] = 0; GRID[1] = 0; GRID[2] = 1;
GRID[3] = 0; GRID[4] = 0; GRID[5] = 0;
GRID[6] = 0; GRID[7] = 0; GRID[8] = 0;
}





// update the grid.
for(int i = 0; i < 9; i++){
  if(GRID[i] == 1){ digitalWrite(i + 2, LOW);} // turn off the relay
  if(GRID[i] == 0){ digitalWrite(i + 2, HIGH);} // turn on the relay
}
}
//************************************************************




//GRID: BINARY************************************************
if(RETURN == 32){
// 101*010*110* flash example, 5 groups of 3 switches
// CODE: 010*001*000*100*101
currentMillis = millis();  //get the current "time" (actually the number of milliseconds since the program started)

 // if the time has passed.
 if (currentMillis - startMillis >= Bperiod ){ //test whether the period has elapsed
  //* do something *
  LCOUNT = LCOUNT + 1;
  if(LCOUNT > 39){LCOUNT = 0; }// how many stages to the animation.
  startMillis = currentMillis; // reset the counter.
 }


if(LCOUNT == 0){// ALL
GRID[0] = 1; GRID[1] = 1; GRID[2] = 1;
GRID[3] = 1; GRID[4] = 1; GRID[5] = 1;
GRID[6] = 1; GRID[7] = 1; GRID[8] = 1;
}

// first group of 3 **************************
if(LCOUNT == 1){// NONE
GRID[0] = 0; GRID[1] = 0; GRID[2] = 0;
GRID[3] = 0; GRID[4] = 0; GRID[5] = 0;
GRID[6] = 0; GRID[7] = 0; GRID[8] = 0;
}
if(LCOUNT == 2){// ZERO
GRID[0] = 1; GRID[1] = 1; GRID[2] = 1;
GRID[3] = 1; GRID[4] = 0; GRID[5] = 1;
GRID[6] = 1; GRID[7] = 1; GRID[8] = 1;
}
if(LCOUNT == 3){// NONE
GRID[0] = 0; GRID[1] = 0; GRID[2] = 0;
GRID[3] = 0; GRID[4] = 0; GRID[5] = 0;
GRID[6] = 0; GRID[7] = 0; GRID[8] = 0;
}
if(LCOUNT == 4){// ONE
GRID[0] = 0; GRID[1] = 1; GRID[2] = 0;
GRID[3] = 0; GRID[4] = 1; GRID[5] = 0;
GRID[6] = 0; GRID[7] = 1; GRID[8] = 0;
}
if(LCOUNT == 5){// NONE
GRID[0] = 0; GRID[1] = 0; GRID[2] = 0;
GRID[3] = 0; GRID[4] = 0; GRID[5] = 0;
GRID[6] = 0; GRID[7] = 0; GRID[8] = 0;
}
if(LCOUNT == 6){// ZERO
GRID[0] = 1; GRID[1] = 1; GRID[2] = 1;
GRID[3] = 1; GRID[4] = 0; GRID[5] = 1;
GRID[6] = 1; GRID[7] = 1; GRID[8] = 1;
}
if(LCOUNT == 7){// NONE
GRID[0] = 0; GRID[1] = 0; GRID[2] = 0;
GRID[3] = 0; GRID[4] = 0; GRID[5] = 0;
GRID[6] = 0; GRID[7] = 0; GRID[8] = 0;
}
if(LCOUNT == 7){// PERIOD
GRID[0] = 0; GRID[1] = 0; GRID[2] = 0;
GRID[3] = 0; GRID[4] = 1; GRID[5] = 0;
GRID[6] = 0; GRID[7] = 0; GRID[8] = 0;
}


// Second group of 3 ************************
if(LCOUNT == 8){// NONE
GRID[0] = 0; GRID[1] = 0; GRID[2] = 0;
GRID[3] = 0; GRID[4] = 0; GRID[5] = 0;
GRID[6] = 0; GRID[7] = 0; GRID[8] = 0;
}
if(LCOUNT == 9){// ZERO
GRID[0] = 1; GRID[1] = 1; GRID[2] = 1;
GRID[3] = 1; GRID[4] = 0; GRID[5] = 1;
GRID[6] = 1; GRID[7] = 1; GRID[8] = 1;
}
if(LCOUNT == 10){// NONE
GRID[0] = 0; GRID[1] = 0; GRID[2] = 0;
GRID[3] = 0; GRID[4] = 0; GRID[5] = 0;
GRID[6] = 0; GRID[7] = 0; GRID[8] = 0;
}
if(LCOUNT == 11){// ZERO
GRID[0] = 1; GRID[1] = 1; GRID[2] = 1;
GRID[3] = 1; GRID[4] = 0; GRID[5] = 1;
GRID[6] = 1; GRID[7] = 1; GRID[8] = 1;
}
if(LCOUNT == 12){// NONE
GRID[0] = 0; GRID[1] = 0; GRID[2] = 0;
GRID[3] = 0; GRID[4] = 0; GRID[5] = 0;
GRID[6] = 0; GRID[7] = 0; GRID[8] = 0;
}
if(LCOUNT == 13){// ONE
GRID[0] = 0; GRID[1] = 1; GRID[2] = 0;
GRID[3] = 0; GRID[4] = 1; GRID[5] = 0;
GRID[6] = 0; GRID[7] = 1; GRID[8] = 0;
}
if(LCOUNT == 14){// NONE
GRID[0] = 0; GRID[1] = 0; GRID[2] = 0;
GRID[3] = 0; GRID[4] = 0; GRID[5] = 0;
GRID[6] = 0; GRID[7] = 0; GRID[8] = 0;
}
if(LCOUNT == 15){// PERIOD
GRID[0] = 0; GRID[1] = 0; GRID[2] = 0;
GRID[3] = 0; GRID[4] = 1; GRID[5] = 0;
GRID[6] = 0; GRID[7] = 0; GRID[8] = 0;
}


// third group of 3 ************************
if(LCOUNT == 16){// NONE
GRID[0] = 0; GRID[1] = 0; GRID[2] = 0;
GRID[3] = 0; GRID[4] = 0; GRID[5] = 0;
GRID[6] = 0; GRID[7] = 0; GRID[8] = 0;
}
if(LCOUNT == 17){// ZERO
GRID[0] = 1; GRID[1] = 1; GRID[2] = 1;
GRID[3] = 1; GRID[4] = 0; GRID[5] = 1;
GRID[6] = 1; GRID[7] = 1; GRID[8] = 1;
}
if(LCOUNT == 18){// NONE
GRID[0] = 0; GRID[1] = 0; GRID[2] = 0;
GRID[3] = 0; GRID[4] = 0; GRID[5] = 0;
GRID[6] = 0; GRID[7] = 0; GRID[8] = 0;
}
if(LCOUNT == 19){// ZERO
GRID[0] = 1; GRID[1] = 1; GRID[2] = 1;
GRID[3] = 1; GRID[4] = 0; GRID[5] = 1;
GRID[6] = 1; GRID[7] = 1; GRID[8] = 1;
}
if(LCOUNT == 20){// NONE
GRID[0] = 0; GRID[1] = 0; GRID[2] = 0;
GRID[3] = 0; GRID[4] = 0; GRID[5] = 0;
GRID[6] = 0; GRID[7] = 0; GRID[8] = 0;
}
if(LCOUNT == 21){// ZERO
GRID[0] = 1; GRID[1] = 1; GRID[2] = 1;
GRID[3] = 1; GRID[4] = 0; GRID[5] = 1;
GRID[6] = 1; GRID[7] = 1; GRID[8] = 1;
}
if(LCOUNT == 22){// NONE
GRID[0] = 0; GRID[1] = 0; GRID[2] = 0;
GRID[3] = 0; GRID[4] = 0; GRID[5] = 0;
GRID[6] = 0; GRID[7] = 0; GRID[8] = 0;
}
if(LCOUNT == 23){// PERIOD
GRID[0] = 0; GRID[1] = 0; GRID[2] = 0;
GRID[3] = 0; GRID[4] = 1; GRID[5] = 0;
GRID[6] = 0; GRID[7] = 0; GRID[8] = 0;
}


// 4th group of 3 ************************
if(LCOUNT == 24){// NONE
GRID[0] = 0; GRID[1] = 0; GRID[2] = 0;
GRID[3] = 0; GRID[4] = 0; GRID[5] = 0;
GRID[6] = 0; GRID[7] = 0; GRID[8] = 0;
}
if(LCOUNT == 25){// ONE
GRID[0] = 0; GRID[1] = 1; GRID[2] = 0;
GRID[3] = 0; GRID[4] = 1; GRID[5] = 0;
GRID[6] = 0; GRID[7] = 1; GRID[8] = 0;
}
if(LCOUNT == 26){// NONE
GRID[0] = 0; GRID[1] = 0; GRID[2] = 0;
GRID[3] = 0; GRID[4] = 0; GRID[5] = 0;
GRID[6] = 0; GRID[7] = 0; GRID[8] = 0;
}
if(LCOUNT == 27){// ZERO
GRID[0] = 1; GRID[1] = 1; GRID[2] = 1;
GRID[3] = 1; GRID[4] = 0; GRID[5] = 1;
GRID[6] = 1; GRID[7] = 1; GRID[8] = 1;
}
if(LCOUNT == 28){// NONE
GRID[0] = 0; GRID[1] = 0; GRID[2] = 0;
GRID[3] = 0; GRID[4] = 0; GRID[5] = 0;
GRID[6] = 0; GRID[7] = 0; GRID[8] = 0;
}
if(LCOUNT == 29){// ZERO
GRID[0] = 1; GRID[1] = 1; GRID[2] = 1;
GRID[3] = 1; GRID[4] = 0; GRID[5] = 1;
GRID[6] = 1; GRID[7] = 1; GRID[8] = 1;
}
if(LCOUNT == 30){// NONE
GRID[0] = 0; GRID[1] = 0; GRID[2] = 0;
GRID[3] = 0; GRID[4] = 0; GRID[5] = 0;
GRID[6] = 0; GRID[7] = 0; GRID[8] = 0;
}
if(LCOUNT == 31){// PERIOD
GRID[0] = 0; GRID[1] = 0; GRID[2] = 0;
GRID[3] = 0; GRID[4] = 1; GRID[5] = 0;
GRID[6] = 0; GRID[7] = 0; GRID[8] = 0;
}

// 5th group of 3 ************************
if(LCOUNT == 32){// NONE
GRID[0] = 0; GRID[1] = 0; GRID[2] = 0;
GRID[3] = 0; GRID[4] = 0; GRID[5] = 0;
GRID[6] = 0; GRID[7] = 0; GRID[8] = 0;
}
if(LCOUNT == 33){// ONE
GRID[0] = 0; GRID[1] = 1; GRID[2] = 0;
GRID[3] = 0; GRID[4] = 1; GRID[5] = 0;
GRID[6] = 0; GRID[7] = 1; GRID[8] = 0;
}
if(LCOUNT == 34){// NONE
GRID[0] = 0; GRID[1] = 0; GRID[2] = 0;
GRID[3] = 0; GRID[4] = 0; GRID[5] = 0;
GRID[6] = 0; GRID[7] = 0; GRID[8] = 0;
}
if(LCOUNT == 35){// ZERO
GRID[0] = 1; GRID[1] = 1; GRID[2] = 1;
GRID[3] = 1; GRID[4] = 0; GRID[5] = 1;
GRID[6] = 1; GRID[7] = 1; GRID[8] = 1;
}
if(LCOUNT == 36){// NONE
GRID[0] = 0; GRID[1] = 0; GRID[2] = 0;
GRID[3] = 0; GRID[4] = 0; GRID[5] = 0;
GRID[6] = 0; GRID[7] = 0; GRID[8] = 0;
}
if(LCOUNT == 37){// ONE
GRID[0] = 0; GRID[1] = 1; GRID[2] = 0;
GRID[3] = 0; GRID[4] = 1; GRID[5] = 0;
GRID[6] = 0; GRID[7] = 1; GRID[8] = 0;
}
if(LCOUNT == 38){// NONE
GRID[0] = 0; GRID[1] = 0; GRID[2] = 0;
GRID[3] = 0; GRID[4] = 0; GRID[5] = 0;
GRID[6] = 0; GRID[7] = 0; GRID[8] = 0;
}
if(LCOUNT == 39){// OFF
GRID[0] = 0; GRID[1] = 0; GRID[2] = 0;
GRID[3] = 0; GRID[4] = 0; GRID[5] = 0;
GRID[6] = 0; GRID[7] = 0; GRID[8] = 0;
}


// update the grid.
for(int i = 0; i < 9; i++){
  if(GRID[i] == 1){ digitalWrite(i + 2, LOW);} // turn off the relay
  if(GRID[i] == 0){ digitalWrite(i + 2, HIGH);} // turn on the relay
}
}
//************************************************************





// DATA FROM MASTER &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


//  *****************************************************
if(RETURN == 1){

digitalWrite(2, LOW); // 1
digitalWrite(3, HIGH); //2
digitalWrite(4, HIGH); //3
digitalWrite(5, HIGH); //4
digitalWrite(6, HIGH); //5
digitalWrite(7, HIGH); //6
digitalWrite(8, HIGH); //7
digitalWrite(9, HIGH); //8
digitalWrite(10, HIGH);//9
   STAGE = 0;
   RETURN = 0;
}


//  *****************************************************
if(RETURN == 2){
   digitalWrite(2, HIGH); // 1
digitalWrite(3, HIGH); //2
digitalWrite(4, HIGH); //3
digitalWrite(5, HIGH); //4
digitalWrite(6, HIGH); //5
digitalWrite(7, HIGH); //6
digitalWrite(8, HIGH); //7
digitalWrite(9, HIGH); //8
digitalWrite(10, LOW);//9
 STAGE = 0;
  RETURN = 0;
}

// ***************************************************
if(RETURN == 3){
   digitalWrite(2, HIGH); // 1
digitalWrite(3, LOW); //2
digitalWrite(4, HIGH); //3
digitalWrite(5, HIGH); //4
digitalWrite(6, HIGH); //5
digitalWrite(7, HIGH); //6
digitalWrite(8, HIGH); //7
digitalWrite(9, HIGH); //8
digitalWrite(10, HIGH);//9
 STAGE = 0;
  RETURN = 0;
}

// ***************************************************
if(RETURN == 4){
   digitalWrite(2, HIGH); // 1
digitalWrite(3, HIGH); //2
digitalWrite(4, HIGH); //3
digitalWrite(5, HIGH); //4
digitalWrite(6, HIGH); //5
digitalWrite(7, LOW); //6
digitalWrite(8, HIGH); //7
digitalWrite(9, HIGH); //8
digitalWrite(10, HIGH);//9
 STAGE = 0;
  RETURN = 0;
}


// ALL OFF *****************************************************
if(RETURN == 5){
  digitalWrite(2, HIGH); // 1
digitalWrite(3, HIGH); //2
digitalWrite(4, HIGH); //3
digitalWrite(5, HIGH); //4
digitalWrite(6, HIGH); //5
digitalWrite(7, HIGH); //6
digitalWrite(8, HIGH); //7
digitalWrite(9, HIGH); //8
digitalWrite(10, HIGH);//9
 STAGE = 0;
  RETURN = 0;
}


// ALL ON *****************************************************
if(RETURN == 6){
   digitalWrite(2, LOW); // 1
digitalWrite(3, LOW); //2
digitalWrite(4, LOW); //3
digitalWrite(5, LOW); //4
digitalWrite(6, LOW); //5
digitalWrite(7, LOW); //6
digitalWrite(8, LOW); //7
digitalWrite(9, LOW); //8
digitalWrite(10, LOW);//9
 RETURN = 0;
 STAGE = 0;
}
if(RETURN == 9){
  //dj booth mag lock
  
       digitalWrite(A0,HIGH);
        digitalWrite(12, LOW); // Toggle DJ booth mag lock
      delay(100);
 RETURN = 0;
}
if(RETURN == 10){
  //
  if(digitalRead(A2) == HIGH){
        digitalWrite(A2, LOW); // Toggle Light on mag lock
      }else{
        digitalWrite(A2,HIGH);
      }

  RETURN = 0;
}
if(RETURN == 11){
  //
  if(digitalRead(A3) == HIGH){
        digitalWrite(A3, LOW); // Toggle 10 light mag lock
      }else{
        digitalWrite(A3,HIGH);
      }
      RETURN = 0;
}

// AI DROP PANEL *****************************************************
if(RETURN == 7){
  //digitalWrite(A0, LOW); // Drop panel AI reveal
  //Serial.println("MASTER REQUEST Drop panel AI Reveal."); 
  RETURN = 0;
}

if(RETURN == 90){


 digitalWrite(11, HIGH); //dj cam motor on LOW is on HIGH is off
 digitalWrite(12, HIGH); //combo A0 HIGH and 12 LOW is dj door mag off
 digitalWrite(A0, LOW); //combo A0 LOW and 12 high is dj door mag on
 digitalWrite(A1, HIGH);//red lights turn on 
 digitalWrite(A2, LOW); //mag lock lights on game
 digitalWrite(A3, LOW); //mag lock for 10 lights game

  
}else if(RETURN == 91){

 digitalWrite(11, LOW); //dj cam motor on LOW is on HIGH is off
 digitalWrite(12, HIGH); //combo A0 HIGH and 12 LOW is dj door mag off
 digitalWrite(A0, LOW); //combo A0 LOW and 12 high is dj door mag on
 digitalWrite(A1, LOW);//red lights turn on 
 digitalWrite(A2, LOW); //mag lock lights on game
 digitalWrite(A3, LOW); //mag lock for 10 lights game

  
}










  
  digitalWrite(LED_BUILTIN, LOW); 
  delay(50);

 
}// End of main loop
//############################################################################################







//RECEIVE DATA FROM MASTER ***********************************************************

void receiveEvent(int howMany) {
         RETURN = Wire.read();           // receive byte as an integer
          //Serial.print("DATA from MASTER:");         // print the integer
         //Serial.println(RETURN);         // print the integer
}// end of function



// SEND DATA TO MASTER WHEN POLLED ***********************************************************

void requestEvent(){

if(SEND != 0){
  
  Wire.write(14); // what slave it was sent from ( may not be used ) 
  Wire.write(SEND);  // send off the data to the master.
 // Serial.print("DATA sent to MASTER:"); 
 
  SEND = 0;
  }
  digitalWrite(LED_BUILTIN, HIGH); // flash the LED to show data was sent.
  delay(20); 
 }// end of function
