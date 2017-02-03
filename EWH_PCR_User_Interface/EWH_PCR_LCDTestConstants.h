#ifndef EWH_PCR_LCDTESTCONSTANTS_H
#define EWH_PCR_LCDTESTCONSTANTS_H

/*****************************************BEGIN DEFINE STATEMENTS*************************************/


/*******PIN ASSIGNMENT FOR PCB*******/
#define EN_PIN  4
#define RW_PIN  5
#define RS_PIN  6
#define D4_PIN  0
#define D5_PIN  1
#define D6_PIN  2
#define D7_PIN  3

/*********LED ASSIGNMENT VALUES**********/
#define  LED_OFF  0
#define  LED_ON  1

#define I2C_ADDR    0x38              // Define I2C Address for LCD

#define BACKLIGHT_PIN  7

/**
 * Byte code associated with the up arrow for the LCD.
 */
byte upArrow [8] = {
  B00100,
  B01110,
  B11111,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100
};

/**
 * Byte code associated with the down arrow for the LCD.
 */
byte downArrow [8] = {
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B11111,
  B01110,
  B00100
};

void initializeLCD(LiquidCrystal_I2C *lcd)
{
   //initializes LCD screen with 16 columns and 2 rows
   lcd->begin(16,2); 
   lcd->setBacklightPin(BACKLIGHT_PIN,POSITIVE);
   lcd->setBacklight(LED_ON);
   lcd->createChar(0,upArrow); //saves upArrow character as 0
   lcd->createChar(1,downArrow); //saves downArrow character as 1

   lcd->clear();
   lcd->setCursor(0,0);
   lcd->print("Goal:");
   lcd->setCursor(7,0);
   lcd->print("Cycle:");
   lcd->setCursor(0,1);
   lcd->print("Temp:");

}

#endif
