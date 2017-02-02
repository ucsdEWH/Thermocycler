#ifndef EWH_PCR_UTILS_H
#define EWH_PCR_UTILS_H

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



#endif
