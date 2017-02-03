/**

*/
#ifndef EWH_PCR_UI_CONTROLLER_H
#define EWH_PCR_UI_CONTROLLER_H

#include "EWH_PCR_UI_Display.h"



/* function to select type of operation to use */
void selectMode(int selectedMode);

/* three main protocol options */
int selectProtocol( int(* selectPrompt(int[])) );
int createProtocol( int * (* createPrompt()) );
int deleteProtocol( int(* deletePrompt(int[])) );

#endif


