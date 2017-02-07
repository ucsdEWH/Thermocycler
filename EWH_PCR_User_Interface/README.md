# PCR USER INTERFACE
----------------------------------------------------------------------------------------------------------------------------------
## UI component for the EWH Thermocycler

Authors: YiDing Fang

Maintain: YiDing Fang

Contact: yif017@eng.ucsd.edu

### NOTES 02-02-2017 

Different ways to represent cycle procedures
* struct containing the following:
  * array with number of cycles per temperature
  * array of temperatures
* array for temperature, array for cycles, array for index

### NOTES 02-03-2017

Memory usage may be too high if we read the whole array of protocolEntries
* can possibly resolve this by reading in only the pID and name arrays

### NOTES 02-05-2017

Should probably refactor the ProtocolEntry struct into a class
* Constructor to intialize methods
* Equals method
* Null check method
* Proper getters and setters
* methods to read and write object from and to EEPROM

Feature can be implemented after the code is entirely functional and if using
classes is friendly for memory requirements

Should probably re-implement the ID feature to easily search through the EEPROM
for empty entries and such

### NOTES 02-06-2017

TODO: refactor readEEPROMInt method
* confirm that current code is consistent with new signature
  * changed order of address and write value to be consistent with EEPROM lib
* might be a good idea to store an ID field in the EEPROM
