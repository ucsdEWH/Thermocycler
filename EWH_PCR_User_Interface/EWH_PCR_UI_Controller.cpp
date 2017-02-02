/**
 * 
 */

#include "EWH_PCR_UI_Controller.h"

/*
 * Chooses particular protocol depending on user input
 * 
 * Arguments:
 *    int selectedMode: integer representing choice selected by user 
 */
void selectMode(int selectedMode){
  switch(selectedMode){
    case 1:
      // call selectProtcol method
      break;
    case 2:
      // call createProtocol method
      break;
    case 3:
      // call the deleteProtocol method
      break;
    default:
      break;
  }
}

/*
 * Chooses particular protocol depending on user input
 * 
 * Arguments:
 *    int(selectPrompt*(int[])) is a pointer to a function which takes an array of integers(addresses) and returns an int
 */
int selectProtocol( int(* selectPrompt(int[])) ){
  // Makes call to backend to retrieve list of stored protocols
  // Using the list of stored protocols, retrieve information regarding each protocol
  
  // calls the presentation layer to display options based on passed in array
  // return value of the presentation layer determines which protocol to run 
}


/*
 * Creates particular protocol depending on user input
 * 
 * Arguments:
 *    int[](createPrompt*()) is a pointer to a function which returns an array of integers
 */
int createProtocol(int * (* createPrompt()) ){
  // call display level code to prompt user to enter the number of cycles and the length of each cycle
  // returned values of presentation level logic are sent to the backend to be written to memory
}


/*
 * Deletes particular protocol depending on user input
 * 
 * Arguments:
 *    int[](deletePrompt*(int[])) is a pointer to a function which takes an array of integers returns an array of integers
 */
int deleteProtocol(){
//void deleteProtocol( int(* deletePrompt(int[])) ){
  // call display level code to prompt user to select which protocol to delete
  // returned vaues of presentation evel logic are sent to the backend to be deleted
}




 
