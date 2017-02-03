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
