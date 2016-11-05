#include "PCR_Thermocycler.h"

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

/**
 * Starts the LCD and displays quanities that are being monitored
 * by the device (current temperature, current cycle number, and final temperature)
 */
void initializeLCD()
{
   //initializes LCD screen with 16 columns and 2 rows
   lcd.begin(16,2); 
   lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
   lcd.setBacklight(LED_ON);
   lcd.createChar(0,upArrow); //saves upArrow character as 0
   lcd.createChar(1,downArrow); //saves downArrow character as 1

   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Goal:");
   lcd.setCursor(7,0);
   lcd.print("Cycle:");
   lcd.setCursor(0,1);
   lcd.print("Temp:");

}

/**
 * Displays the current temperature of the thermocycler.
 * @param   double temperature   the temperature of the thermocycler.
 */
void showTemp(double temperature){
  lcd.setCursor(5,1);
  lcd.print (temperature);
}

/**
 * Displays the current cycle being run on the thermocycler
 * @param   int cyclenum      The current cycle number
 */
void showCycle(int cyclenum){
  lcd.setCursor(13,0);
  lcd.print(cyclenum);
}

/**
 * Displays the temperature that the thermocycler is attempting to reach.
 * @param  int tempgoal    The final temperature being reached by the thermocycler.
 */
void showGoal(int tempgoal){
 lcd.setCursor(5,0);
 lcd.print(tempgoal);
}

