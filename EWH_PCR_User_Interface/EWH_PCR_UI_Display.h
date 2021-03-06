#ifndef EWH_PCR_UI_DISPLAY_H
#define EWH_PCR_UI_DISPLAY_H

#include <LiquidCrystal_I2C.h>
#include <Wire.h>


#define BUTTON_THRESH_1 748
#define BUTTON_THRESH_2 504
#define BUTTON_THRESH_3 398
#define BUTTON_THRESH_4 329
#define BUTTON_TOLERANCE 5

#define BUTTON_LEFT 1 //green
#define BUTTON_RIGHT 2 //white
#define BUTTON_START 3 //yellow
#define BUTTON_STOP 4 //blue


#define DISPLAY_WIDTH 16
#define BUTTON_PIN 3

int selectPrompt( int indexArray[], const char ** nameArray, int * windowFrame, LiquidCrystal_I2C * lcd );
int deletePrompt( int indexArray[], const char ** nameArray, int * windowFrame, LiquidCrystal_I2C * lcd);
int * createPrompt();
int readAnalogButton( int pinNum );

#endif

