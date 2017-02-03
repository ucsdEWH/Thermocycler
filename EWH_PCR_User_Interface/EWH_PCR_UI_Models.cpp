#include "EWH_PCR_UI_Models.h"

/**
 * 
 * EEPROM is available on the arduno as persistant storage
 *  1024 bytes are available. Architecture will be laid out as so
 *    - each protocol can have a maximum of 8 stages
 *      - 2 ints for each stage (stage length and stage temperature)
 *      - 8 chars for the protocol name
 *      - 2 ints for each stage (num cycles & temperature) * 2 bytes per int * 8 stages + 8 chars= 40 bytes per entry
 *      - 24 entries maximum of 40 bytes each
 *    - reserve first 64 bytes for metadata
 *    | checksum ... XX ... XX | N A M E H E R E | 0 1 2 3 4 5 6 7 ... 0 1 2 3 4 5 6 7 | ... |
 *            Metadata            protocol name        Times               Cycles
 *      
 * 
 */
 
/* Populates our ProtocolEntry struct with the appropriate fields
 * 
 * Arguments:
 *    int id is the id to be associated with a protocol
 *    const char * protocolName is the name of the protocol to be displayed
 *    int temp[] is the sequence of temperatures that the protocol is to go through
 *    int cycles[] is the number of cycles to be associated with each temperature in our protocol
 * 
 * Return Value:
 *    return 1 if successful
 */
int createProtocol( int id, const char * protocolName, int temps[], int cycles[], ProtocolEntry * entry ){
  entry->pID = id;
  entry->pName = protocolName;
  for( int i=0; i< MAX_CYCLES; i++ ){
    entry->pCycles[i] = cycles[i];
    entry->pTemps[i] = temps[i];
  }
  return 1;
}

/**
int readProtocols(int * payload, ProtocolEntry * protocols[]){
  *payload = EEPROM.read(0);
  
  for( int i=(METADATA_SIZE-1); i<EEPROM.length(); i++){
    char * temp[MAX_NAME_LENGTH];
    for( int j=0; j< MAX_NAME_LENGTH; j++ ){
      temp[j] = EEPROM.read(i+j);
    }
    
  }
  
}
**/

/*
 * Writes the first bit in EEPROM to store the number of protocols the user is currently using
 *
 * Arguments:
 *    int payload is the number of protocols stored
 *
 * Return Value:
 *    int returned represents the payload written
 *    TODO: returns -1 on failure 
 */
int writeMetadata(int payload){
  EEPROM.write(0, payload);
}


int * writeProtocolData(int newIndexArray[]){
  for( int index = 0; index < MAX_ENTRIES; index++){
    
  }
    
}
const char * writeProtocolData(const char * newNameArray[]){}
