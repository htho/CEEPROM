/*
	fake_eeprom

	Demonstrates Reading, Writing and Removing Chunks from faked EEPROM.
	Faking the EEPROM means that instead of using the EEPROM, an array
	is used. This nice for debugging without wearing the EEPROM Cells.
	Of course data is not stored persistently as it would if the EEPROM
	was actually used.
	
	A Chunk is simply an array, where the first field contains the length of the array. 

	The circuit:
	* no components need to be attached.

	Created 03.05.2014
	By Hauke Thorenz

	https://github.com/htho/CEEPROM
*/

//Defines an Offset from which to use EEPROM for chunked data.
#define EEPROM_OFFSET 32
//In this case the fist 32 Adresses won't be used.

//Fakes the EEPROM. Not including this file means that the actual EEPROM will be used.
#include <RWH_Fake.h> 

//The CEEPROM Functionality
#include <CEEPROM.h> 

//CEEPROMPrint provides functions to print chunks and the memory.
#include <CEEPROMPrint.h>

void setup()
{
  Serial.begin(9600);
  //Some Testdata
  //A Chunk is simply an array, where the first field contains the length of the array. 
  uint8_t chunk0[] = {3, 1, 2, 3}; //Chunk Length: 3, Values: {1, 2, 3}
  uint8_t chunk1[] = {4, 11, 12, 13, 14}; //Chunk Length: 4, Values: {11, 12, 13, 14}
  uint8_t chunk2[] = {1, 21}; //Chunk Length: 1, Value: {21}
  
  //This is for initializing the storage. This function will remove any chunks stored.
  //Remove this when you actually want to store data in EEPROM.
  CEEPROM.format();
  
  Serial.print("Currently these ");
  Serial.print(CEEPROM.chunkCount());
  Serial.println(" Chunks are stored:");
  for(int i = 0; i < CEEPROM.chunkCount(); i++){
    uint8_t* chunk = CEEPROM.get(i);
    CEEPROMPrint.printChunk(chunk);
    delete chunk;
  }
  
  Serial.println("This is how the EEPROM looks like:");
  CEEPROMPrint.printEEPROMDump();
  
  Serial.println("\nAdding some Chunks:");
  CEEPROM.add(chunk0);
  CEEPROM.add(chunk1);
  CEEPROM.add(chunk2);

  Serial.print("Now these ");
  Serial.print(CEEPROM.chunkCount());
  Serial.println(" Chunks are stored:");
  for(int i = 0; i < CEEPROM.chunkCount(); i++){
    uint8_t* chunk = CEEPROM.get(i);
    CEEPROMPrint.printChunk(chunk);
    delete chunk;
  }
  Serial.println("This is how the EEPROM looks like:");
  CEEPROMPrint.printEEPROMDump();
 
  Serial.println("\nRemoving the Chunk at Position 0:");
  CEEPROM.remove(0);
  
  Serial.print("Now these ");
  Serial.print(CEEPROM.chunkCount());
  Serial.println(" Chunks are stored:");
  for(int i = 0; i < CEEPROM.chunkCount(); i++){
    uint8_t* chunk = CEEPROM.get(i);
    CEEPROMPrint.printChunk(chunk);
    delete chunk;
  }
  Serial.println("This is how the EEPROM looks like:");
  CEEPROMPrint.printEEPROMDump();
}

void loop()
{
  // Nothing to do during loop
}    


