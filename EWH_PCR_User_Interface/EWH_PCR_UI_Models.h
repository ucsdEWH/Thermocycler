#ifndef EWH_PCR_UI_MODELS_H
#define EWH_PCR_UI_MODELS_H

#define MAX_CYCLES 8
#define MAX_NAME_LENGTH 8
#define MAX_ENTRIES 24
#define METADATA_SIZE 64

#include <EEPROM.h>

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
 *            Metadata            protocol name        Temps               Cycles
 *      
 * 
 */

/**
 * ProtocolEntry is a struct defined for the
 */

struct ProtocolEntry {
  int pID;
  const char *pName;
  int pCycles[MAX_CYCLES];
  int pTemps[MAX_CYCLES]; 
};

int createProtocol( int id, const char * protocolName, int temps[], int cycles[], ProtocolEntry * entry );

/**
 * Functions defined to be used in arduino memory accesses
 */
 
// read all the metadata into our output arrays
int readProtocols(int * payload,ProtocolEntry * protocols[]);

// write payload
int writeMetadata(int payload);
// write protocol data array
int * writeProtocolData( int newIndexArray[]);
const char * writeProtocolData( const char * newNameArray[]);


#endif
