/*
 *
 */
#include "EWH_PCR_UI_Display.h"

/*
 * Animation for changing numeri_PC
 * Arguents:
 *    int min represents the smallest value on the scroll wheel
 */
int numSelection( int rangeMin, int rangeMax, LiquidCrystal_I2C * lcd, int row ){
  int counter = rangeMin;
  
  
  // on button press increase the counter
}

/*
 * Prompts user to select protocol from those stored
 *
 * Arguments:
 *    int[] indexArray is the array which stores the addresses of known protocols
 *
 * Return Value:
 *    int
 */
int selectPrompt( ProtocolEntry protocols[], int * windowFrame, LiquidCrystal_I2C * lcd ){
  // prompt user
  int buttonStatus = -1;
  int displayIndex = *windowFrame;

  // loop while confirm or back have not been pressed
  while(buttonStatus != BUTTON_START || buttonStatus != BUTTON_STOP){

    //lcd->clear();
    lcd->setCursor(0,0);
    lcd->print( "Select: "  );
    // clear out part of the display
    lcd->print( "        " );
    // move the cursor back to after 'select: '
    lcd->setCursor(8,0);
    lcd->print( protocols[displayIndex].pName);

    // DEBUG
    // Serial.print(displayIndex);

    // read in button press value
    buttonStatus = readAnalogButton(BUTTON_PIN);
    // display the values in the window frame
    // use i to keep track of the position on the screen
    // we want to print the dislay | _ tens ones | _ tens ones | ...
    for( int i = 0; i < DISPLAY_WIDTH; i++){
      lcd->setCursor(i, 1);
      // print a space before each entry as spacing
      if( ((i+1)%3) == 1){
        lcd->print(" ");  
      }
      // print on every third entry (i+1)%3 is every third position accounting for the offset
      else if( !((i+1)%3) ){
        // using window frame as the first value in our array to display compute positions relative to this
        // for double digit index protocols
        // use -1 to account for off by 1 error
        if( (*windowFrame - 1 + ((i+1)/3)) >= 10 ){
          // move cursor back one to print two digits
          lcd->setCursor(i-1, 1);
          lcd->print((*windowFrame - 1 + ((i+1)/3)));
        }
        // for single digit index protocols
        else if((*windowFrame - 1 + ((i+1)/3)) < 10){
          // print filler zero if a number is a single digit
          lcd->setCursor(i-1, 1);
          lcd->print(0);
          lcd->print((*windowFrame - 1 + ((i+1)/3)));
        }  
      }
    }
    if(buttonStatus == BUTTON_RIGHT){
      // _19 _20 _21 _ 2 2 _ 2  3 _
      // 012 345 678 91011 121314 15
    
      if( *windowFrame < (23-4) ){
        (*windowFrame) += 1;
      }

      if( displayIndex < 23 ){
        displayIndex++;
        
      }
    }
    if(buttonStatus == BUTTON_LEFT){
      if( *windowFrame > 0 && displayIndex < (24-4)){
      (*windowFrame) -= 1;
      }
      if( displayIndex > 0 ){
        displayIndex--;
      }
    }   
  }
  lcd->setCursor(0,1);
  lcd->blink();

  // 
  if(buttonStatus == BUTTON_START){
    return *windowFrame;
  }
  else if(buttonStatus == BUTTON_STOP){
    return 0;
  }
}

/*
 * Prompts user to select protocol from those stored
 *
 * Arguments:
 *    int[] indexArray is the array which stores the addresses of known protocols
 *
 * Return Value:
 *    int
 *
int selectPrompt( int indexArray[], const char ** nameArray, int * windowFrame, LiquidCrystal_I2C * lcd ){
  // prompt user
  
  const char * nameA = *nameArray;
  //extract the number of protocols stored in selected array
  int checkSum = indexArray[0];
  int arrayTail = checkSum++;
  int buttonStatus = -1;

  int displayIndex = *windowFrame;

  // loop while confirm or back have not been pressed
  while(buttonStatus != BUTTON_START || buttonStatus != BUTTON_STOP){

    //lcd->clear();
    lcd->setCursor(0,0);
    lcd->print( "Select: "  );
    // clear out part of the display
    lcd->print( "        " );
    // move the cursor back to after 'select: '
    lcd->setCursor(8,0);
    lcd->print( nameArray[displayIndex] );
    Serial.print(displayIndex);
    // read in button press value
    buttonStatus = readAnalogButton(BUTTON_PIN);
    // display the values in the window frame
    // use i to keep track of the position on the screen
    // we want to print the dislay | _ tens ones | _ tens ones | ...
    for( int i = 0; i < DISPLAY_WIDTH; i++){
      lcd->setCursor(i, 1);
      // print a space before each entry as spacing
      if( ((i+1)%3) == 1){
        lcd->print(" ");  
      }
      // print on every third entry (i+1)%3 is every third position accounting for the offset
      else if( !((i+1)%3) ){
        // using window frame as the first value in our array to display compute positions relative to this
        // for double digit index protocols
        // use -1 to account for off by 1 error
        if( indexArray[*windowFrame - 1 + ((i+1)/3)] >= 10 ){
          // move cursor back one to print two digits
          lcd->setCursor(i-1, 1);
          lcd->print(indexArray[*windowFrame - 1 + ((i+1)/3)]);
        }
        // for single digit index protocols
        else if(indexArray[*windowFrame - 1 + ((i+1)/3)] < 10){
          // print filler zero if a number is a single digit
          lcd->setCursor(i-1, 1);
          lcd->print(0);
          lcd->print(indexArray[*windowFrame - 1 + ((i+1)/3)]);
        }  
      }
    }
    if(buttonStatus == BUTTON_RIGHT){
      // _19 _20 _21 _ 2 2 _ 2  3 _
      // 012 345 678 91011 121314 15
    
      if( *windowFrame < (23-4) ){
        (*windowFrame) += 1;
      }

      if( displayIndex < 23 ){
        displayIndex++;
        
      }
    }
    if(buttonStatus == BUTTON_LEFT){
      if( *windowFrame > 0 ){
      (*windowFrame) -= 1;
      }
      if( displayIndex > 0 ){
        displayIndex--;
      }
    }   
  }
  lcd->setCursor(0,1);
  lcd->blink();

  // 
  if(buttonStatus == BUTTON_START){
    return *windowFrame;
  }
  else if(buttonStatus == BUTTON_STOP){
    return 0;
  }
}

*/


int deletePrompt( ProtocolEntry protocols[], int * windowFrame, LiquidCrystal_I2C * lcd){
    // prompt user
  int buttonStatus = -1;
  int displayIndex = *windowFrame;

  // loop while confirm or back have not been pressed
  while(buttonStatus != BUTTON_START || buttonStatus != BUTTON_STOP){

    //lcd->clear();
    lcd->setCursor(0,0);
    lcd->print( "Delete: "  );
    // clear out part of the display
    lcd->print( "        " );
    // move the cursor back to after 'select: '
    lcd->setCursor(8,0);
    lcd->print( protocols[displayIndex].pName);

    // DEBUG
    // Serial.print(displayIndex);

    // read in button press value
    buttonStatus = readAnalogButton(BUTTON_PIN);
    // display the values in the window frame
    // use i to keep track of the position on the screen
    // we want to print the dislay | _ tens ones | _ tens ones | ...
    for( int i = 0; i < DISPLAY_WIDTH; i++){
      lcd->setCursor(i, 1);
      // print a space before each entry as spacing
      if( ((i+1)%3) == 1){
        lcd->print(" ");  
      }
      // print on every third entry (i+1)%3 is every third position accounting for the offset
      else if( !((i+1)%3) ){
        // using window frame as the first value in our array to display compute positions relative to this
        // for double digit index protocols
        // use -1 to account for off by 1 error
        if( (*windowFrame - 1 + ((i+1)/3)) >= 10 ){
          // move cursor back one to print two digits
          lcd->setCursor(i-1, 1);
          lcd->print((*windowFrame - 1 + ((i+1)/3)));
        }
        // for single digit index protocols
        else if((*windowFrame - 1 + ((i+1)/3)) < 10){
          // print filler zero if a number is a single digit
          lcd->setCursor(i-1, 1);
          lcd->print(0);
          lcd->print((*windowFrame - 1 + ((i+1)/3)));
        }  
      }
    }
    if(buttonStatus == BUTTON_RIGHT){
      // _19 _20 _21 _ 2 2 _ 2  3 _
      // 012 345 678 91011 121314 15
    
      if( *windowFrame < (23-4) ){
        (*windowFrame) += 1;
      }

      if( displayIndex < 23 ){
        displayIndex++;
        
      }
    }
    if(buttonStatus == BUTTON_LEFT){
      if( *windowFrame > 0 && displayIndex < (24-4)){
      (*windowFrame) -= 1;
      }
      if( displayIndex > 0 ){
        displayIndex--;
      }
    }   
  }
  lcd->setCursor(0,1);
  lcd->blink();

  // 
  if(buttonStatus == BUTTON_START){
    return *windowFrame;
  }
  else if(buttonStatus == BUTTON_STOP){
    return 0;
  }
}
int * createPrompt(){}

/*
 * Prompts user to select protocol from those stored
 *
 * Arguments:
 *    int pinNum represents the pin to be read
 *
 * Return Value:
 *    int represents the button pressed
 */

int readAnalogButton( int pinNum ){
  int readIn = analogRead(pinNum);
  if((readIn > (BUTTON_THRESH_1 - BUTTON_TOLERANCE)) && (readIn < (BUTTON_THRESH_1 + BUTTON_TOLERANCE))){
    return 1;
  }
  else if((readIn > (BUTTON_THRESH_2 - BUTTON_TOLERANCE)) && (readIn < (BUTTON_THRESH_2 + BUTTON_TOLERANCE))){
    return 2;
  }
  else if((readIn > (BUTTON_THRESH_3 - BUTTON_TOLERANCE)) && (readIn < (BUTTON_THRESH_3 + BUTTON_TOLERANCE))){
    return 3;
  }
  else if((readIn > (BUTTON_THRESH_4 - BUTTON_TOLERANCE)) && (readIn < (BUTTON_THRESH_4 + BUTTON_TOLERANCE))){
    return 4;
  }
  else{
    return 0;
  }
}

