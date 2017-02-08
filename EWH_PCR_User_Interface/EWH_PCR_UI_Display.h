#ifndef EWH_PCR_UI_DISPLAY_H
#define EWH_PCR_UI_DISPLAY_H

#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "EWH_PCR_UI_Models.h"


#define BUTTON_THRESH_1 771
#define BUTTON_THRESH_2 512
#define BUTTON_THRESH_3 411
#define BUTTON_THRESH_4 319
#define BUTTON_TOLERANCE 5

#define BUTTON_LEFT 1 //white
#define BUTTON_RIGHT 2 //green
#define BUTTON_START 3 //blue
#define BUTTON_STOP 4 //yellow


#define DISPLAY_WIDTH 16
#define BUTTON_PIN 3


//int selectPrompt( ProtocolEntry protocols[], int * windowFrame, LiquidCrystal_I2C * lcd);
//int deletePrompt( ProtocolEntry protocols[], int * windowFrame, LiquidCrystal_I2C * lcd);

int selectPrompt(const char ** protocolNames, int * windowFrame, LiquidCrystal_I2C * lcd);
int deletePrompt(const char ** protocolNames, int * windowFrame, LiquidCrystal_I2C * lcd);

int * createPrompt();
int confirm(ProtocolEntry selected, int * windowFrame, LiquidCrystal_I2C * lcd );
int readAnalogButton( int pinNum );

#endif

