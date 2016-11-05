#include <LiquidCrystal.h>

/****Defines PCR_THERMOCYCLER_H if it has not already been defined elsewhere*****/
#ifndef PCR_THERMOCYCLER_H
#define PCR_THERMOCYCLER_H


void showTemp();
void advancedPrint();
void initializeSerial();
void initializeLCD();
void heat();
void cool();
void showCycle();
void showGoal();

#endif // PCR_THERMOCYCLER_H
