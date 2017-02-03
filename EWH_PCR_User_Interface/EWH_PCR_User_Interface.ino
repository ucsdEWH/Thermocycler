#include"EWH_PCR_UI_Display.h"
#include "EWH_PCR_UI_Controller.h"
#include "EWH_PCR_UI_Models.h"
#include "EWH_PCR_LCDTestConstants.h"

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;    // the number of the pushbutton pin
const int ledPin = 13;      // the number of the LED pin

// Variables will change:
int controlState = 0;         // the current state of the output pin
int buttonState;              // the current reading from the input pin
int lastButtonState = 0;      // the previous reading from the input pin

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers

int windowFrame = 0; 

// initialize the library with the numbers of the interface pins
LiquidCrystal_I2C  lcd(I2C_ADDR, EN_PIN, RW_PIN, RS_PIN, D4_PIN, D5_PIN, D6_PIN, D7_PIN);

/*****************************************TEMPORARY FOR TESTING*************************************/

int testMemory[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 
17, 18, 19, 20, 21, 22, 23};
const char * names[MAX_ENTRIES] = {"0", "1", "2", "3", "4", "5", "6", "7", 
"8", "9", "10", "11", "12", "13", "14", "15", 
"16", "17", "18", "19", "20", "21", "22", "23"};

ProtocolEntry testProtocol[MAX_ENTRIES];

// TODO: check this part..... careful with references
int * memStart = &testMemory[0];
int * memPtr = memStart;

// for testing struct
int testID = 0;
const char * testString = "foobbarr";
int testCycles[8] = {1,2,3,4,5,6,7};
int testTemps[8] = {101,102,103,104,105,106,107};


/*****************************************END TEMP CONSTANTS*************************************/


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  initializeLCD( &lcd );
  lcd.clear();



}

void loop() {
  // put your main code here, to run repeatedly:
  /**
  ProtocolEntry testEntry;
  testEntry.PEID = testID;
  testEntry.protocolName = testString;
  for( int i = 0; i < 8; i++){
    testEntry.cycles[i] = testCycles[i];
    testEntry.temps[i] = testTemps[i];
  }
  for( int i=0; i < 8; i++ ){
    Serial.println(testEntry.pID);
    Serial.println(testEntry.pName);
    Serial.println( testEntry.pCycles[i] );
    Serial.println( testEntry.pTemps[i] );
  }
  **/

  
  
  // read the state of the switch into a local variable:
  int reading = readAnalogButton(BUTTON_PIN);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH),  and you've waited
  // long enough since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState != 0) {
        controlState = buttonState;
      }
    }
  }

  // set the LED:
  // digitalWrite(ledPin, controlState);
  //selectPrompt(memStart, names, &windowFrame, &lcd);
 // selectPrompt(memStart, names, &windowFrame, &lcd);
  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = reading;
  
}
