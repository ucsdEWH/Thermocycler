#ifndef EWH_PCR_UI_MODELS_H
#define EWH_PCR_UI_MODELS_H

#define MAX_CYCLES 8
#define MAX_NAME_LENGTH 8
#define MAX_STAGES 8
#define CYCLE_LEN 1
#define SIZE_INT 2


#define MAX_ENTRIES 36
#define METADATA_SIZE 88

#include <EEPROM.h>

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
 * 
 */

/**
 * ProtocolEntry is a struct defined for the
 */

struct ProtocolEntry {
  const char *pName;
  int pID;
  int pCycles;
  int pTemps[MAX_CYCLES]; 
};

int createProtocol( int id, const char * protocolName, int temps[], int cycles, ProtocolEntry * entry );

// read all protocols into memory
int readProtocols(int * payload,ProtocolEntry * protocols[]);
// read the protocol names into memory
int readNames( int * payload, char * names );


// write payload
int writeMetadata(int payload);
// write protocol data array
int * writeProtocolData( int newIndexArray[]);
const char * writeProtocolData( const char * newNameArray[]);


#endif
