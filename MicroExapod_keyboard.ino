//--------------------------------------------------------------
//-- MicroHexapod controller http://www.thingiverse.com/thing:34796
//--
//-- Uses the ArduSnake oscillator library by Juan Gonzalez-Gomez 
//-- https://github.com/Obijuan/ArduSnake
//__ Uses the Sketch by:
//__ Carlos Garcia-Saura (Carlosgs), November-2012
//-----------------------------------------------------------
//-- Description: Command MicroHexapod robot by pc keyboard
//--------------------------------------------------------------
//-- (c) Giovanni Gentile, November-2014
//__ http://www.0lab.it
//-- CC-BY-SA license
//--------------------------------------------------------------
#include <Servo.h>
#include <Oscillator.h>

//-- Declare the oscillators
Oscillator osc_middle, osc_right, osc_left;

//-- Global parameters for the oscillatorßs
unsigned int A = 40; // Amplitude (higher -> longer steps) set 10-40
unsigned int T = 3000; // Period (lower -> faster moves)

//-- Declare variable for serial read
byte caratteri;
byte tempChar;

//-- Declare movements variable
int right=90;
int left=90;

void setup()
{
  Serial.begin(19200);
  delay(1000); // Small startup delay, replace with start-button press (if present)
  Serial.println(F("Ready"));
  
  //-- Attach the oscillators to the servos
  osc_middle.attach(2); // 2,3 and 4 are the digital pins
  osc_right.attach(3);
  osc_left.attach(4);
  
  //-- Set the parameters
  osc_middle.SetO(-15); // Correction for the offset of the servos
  osc_right.SetO(-20);
  osc_left.SetO(25);
  
  osc_middle.SetA(15); // Middle motor needs a small amplitude (5-10)
  osc_right.SetA(A);
  osc_left.SetA(A);
  
  osc_middle.SetT(T); // Set the period of work
  osc_right.SetT(T);
  osc_left.SetT(T);
  
  //-- Refresh the oscillators
  osc_middle.refresh();
  osc_right.refresh();
  osc_left.refresh();

  //-- Set the phase difference
  //-- This defines the type of movement the robot makes
  osc_middle.SetPh(DEG2RAD( 90 ));
  osc_left.SetPh(  DEG2RAD( 0 )); 
  osc_right.SetPh( DEG2RAD( 0 )); // For example, putting 180 here will make the robot spin clockwise

}


void loop()
{
 if (Serial.available()) {
 byte command = Serial.read(); //Read the byte
   switch (command) {
     case 'i':
       Serial.println(F("Forward"));
       right = 0;
       left = 0;
       break;
     case 'k':
       Serial.println(F("STOP"));
       right = 90;
       left = 90;
       break;
     case 'j':
       Serial.println(F("Left"));
       right = 0;
       left = 180;
       break;
     case 'l':
       Serial.println(F("Right"));
       right = 180;
       left = 0;
       break;      
     case 'm':
       Serial.println(F("Backward"));
       right = 180;
       left = 180;
       break;
     case 'q':
       if (T > 500) {
       T = T-500;
       }
       Serial.print(F("Increase speed: "));
       Serial.println(T);
       break;
     case 'a':
       if (T < 5000){
       T= T+500;
       }
       Serial.print(F("Decrease speed: "));
       Serial.println(T);
       break;
     } 
   }  
  osc_right.SetPh( DEG2RAD( right ));
  osc_left.SetPh( DEG2RAD( left ));
  //-- Refresh the oscillators
  osc_middle.SetT(T); // Set the period of work
  osc_right.SetT(T);
  osc_left.SetT(T);
  
  osc_middle.refresh();
  osc_right.refresh();
  osc_left.refresh();
}
