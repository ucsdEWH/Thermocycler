#include "EWH_PCR_UI_Models.h"

/**
 * 
 * EEPROM is available on the arduno as persistant storage
 *  1024 bytes are available. Architecture will be laid out as so
 *    - each protocol can have a maximum of 8 stages
 *      - 2 ints for each stage (stage length and stage temperature)
 *      - 8 chars for the protocol name
 *      - 1 int for cycles
 *      - (1 int for each stage (temperature) * 2 bytes per int * 8 stages) + 8 chars + (1 int(cycles) * 2 bytes per int)= 26 bytes per entry
 *      - maximum of 36 entries at 26 bytes each
 *    - reserve first 88 bytes for metadata
 *    | checksum ... XX ... XX | N A M E H E R E | Cycles | 0 1 2 3 4 5 6 7 | ... |
 *            Metadata            protocol name                     Temps
 *      
 * Since Arduino EEPROM library only stores 1 byte at a time, we will write the ints as big endian
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
int createProtocol( int id, const char * protocolName, int temps[], int cycles, ProtocolEntry * entry ){
  entry->pID = id;
  entry->pName = protocolName;
  entry->pCycles = cycles;
  for( int i=0; i< MAX_CYCLES; i++ ){
    entry->pTemps[i] = temps[i];
  }
  return 1;
}


int readProtocols(int * payload, ProtocolEntry * protocols[]){
  *payload = EEPROM.read(0);
  // index for the output array
  int protocolIndex = 0;
  int romIndex = METADATA_SIZE-1;
  
  while( romIndex<EEPROM.length()){
    // process the name string
    char tempName[MAX_NAME_LENGTH];
    for( int j=0; j< MAX_NAME_LENGTH; j++ ){
      tempName[j] = EEPROM.read(romIndex+j);
    }
    // update protolEntry value at index 
    protocols[protocolIndex]->pName = tempName;
    // account for the increase from reading in string
    romIndex+= MAX_NAME_LENGTH;

    // read in the number of stages
    int tempCycles = 0;
    readEEPROMInt(&tempCycles, romIndex );
    protocols[protocolIndex]->pCycles = tempCycles;
    // update position in eeprom
    romIndex += SIZE_INT;

    // read in the array of temperature values
    int tempTemperatures[MAX_CYCLES];
    for( int k=0; k<(MAX_CYCLES * SIZE_INT); k+=2 ){
      int tempVal = 0;
      readEEPROMInt(&tempVal, romIndex + k);
      protocols[protocolIndex]->pTemps[((int)(k/2))] = tempVal;
    }
  }
}


// read the protocol names into memory
int readNames( int * payload, char ** names ){
  *payload = EEPROM.read(0);
  // index for the output array
  int namesIndex = 0;
  int romIndex = METADATA_SIZE-1;
  
  while(romIndex<EEPROM.length()){
    // define temporary name to read the temperature into
    char tempName[MAX_NAME_LENGTH];
    // read in the name as the first entry
    for( int j=0; j<MAX_NAME_LENGTH; j++ ){
      tempName[j] = (char)(EEPROM.read(romIndex+j));
    }
    names[namesIndex] = tempName;
    namesIndex++;
    romIndex += MAX_NAME_LENGTH;
    romIndex += ((MAX_STAGES + CYCLE_LEN) * SIZE_INT);
  }
}

int readEEPROMInt( int * output , int address){
    // read in 2 bytes and then combine to make valid int
    int cycles = 0;
    unsigned char upperByte = EEPROM.read(address++);
    unsigned char lowerByte = EEPROM.read(address);
    // or on lower byte 
    cycles = (cycles | lowerByte);
    cycles = cycles | (upperByte << 8);

    *output = cycles;
}


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

// write protocol into the EEPROM

/*
 * Writes protocol entry to the end of the EEPROM where there is an opening
 *
 * Arguments:
 *    int id is the 
 *
 * Return Value:
 *    int returned represents the payload written
 *    TODO: returns -1 on failure 
 */
int writeProtocolData( ProtocolEntry protocol){
  for(int i=(METADATA_SIZE-1); i<EEPROM.length(); i++){
    
  }
  
}
// delete protol in the EEPROM
int deleteProtocolData( int id, ProtocolEntry protocol){}
