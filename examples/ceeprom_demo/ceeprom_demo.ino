/*
	ceeprom_demo

	Demonstrates Reading, Writing and Removing Chunks from and to EEPROM.
	
	A Chunk is simply an array, where the first field contains the
	length of the array. 

	The circuit:
	* no components need to be attached.

	Created 03.05.2014
	By Hauke Thorenz

	https://github.com/htho/CEEPROM
*/

//Defines an Offset from which to use EEPROM for chunked data.
#define EEPROM_OFFSET 32
//In this case the fist 32 Adresses won't be used.

//Defines the size of the EEPROM, if not defined, 512 bytes of EEPROM are assumed.
#define EEPROM_SIZE 1024

//Defines that CEEPROMs printing functions should be available (DBG(STR) needs to be definde too!)
#define CEEPROM_PRINT
//Defines that CHUNKS printing functions should be available (DBG(STR) needs to be definde too!)
#define CHUNKS_PRINT

//The Printing functions need this Macro
#define DBG(STR) Serial.print(STR);

//The CEEPROM Functionality
#include <CEEPROM.h> 
//The CHUNKS Functionality
#include <CHUNKS.h> 

void setup()
{
  Serial.begin(9600);
  //Some Testdata
  //A Chunk is simply an array, where the first field contains the length of the array. 
  uint8_t chunk0[] = {3, 1, 2, 3}; //Chunk Length: 3, Values: {1, 2, 3}
  uint8_t chunk1[] = {4, 11, 12, 13, 14}; //Chunk Length: 4, Values: {11, 12, 13, 14}
  uint8_t chunk2[] = {1, 21}; //Chunk Length: 1, Value: {21}
  
  //###############
  //---ATTENTION---
  //###############
  //This is for initializing the storage for CEEPROM for the first time.
  //This function will remove any chunks stored.
  //Remove this when you actually want to start storing data in EEPROM.
  CEEPROM.format();
  //###############
  
  Serial.print("Currently these ");
  Serial.print(CEEPROM.chunkCount());
  Serial.println(" Chunks are stored:");
  for(int i = 0; i < CEEPROM.chunkCount(); i++){
    uint8_t* chunk = CEEPROM.get(i);
    CHUNKS.printChunk(chunk);
    delete chunk;
  }
  
  Serial.println("This is how the EEPROM looks like:");
  CEEPROM.printEEPROMDump();
  
  //###############
  //---ATTENTION---
  //###############
  //Starting the Arduino with this sketch over and over again results in
  //adding these three chunks over and over again.
  //(If the storage is not formated before.)
  Serial.println("\nAdding some Chunks:");
  CEEPROM.add(chunk0);
  CEEPROM.add(chunk1);
  CEEPROM.add(chunk2);
  //###############


  Serial.print("Now these ");
  Serial.print(CEEPROM.chunkCount());
  Serial.println(" Chunks are stored:");
  for(int i = 0; i < CEEPROM.chunkCount(); i++){
    uint8_t* chunk = CEEPROM.get(i);
    CHUNKS.printChunk(chunk);
    delete chunk;
  }
  Serial.println("This is how the EEPROM looks like:");
  CEEPROM.printEEPROMDump();
 
  Serial.println("\nRemoving the Chunk at Position 0:");
  CEEPROM.remove(0);
  
  Serial.print("Now these ");
  Serial.print(CEEPROM.chunkCount());
  Serial.println(" Chunks are stored:");
  for(int i = 0; i < CEEPROM.chunkCount(); i++){
    uint8_t* chunk = CEEPROM.get(i);
    CHUNKS.printChunk(chunk);
    delete chunk;
  }
  Serial.println("This is how the EEPROM looks like:");
  CEEPROM.printEEPROMDump();
}

void loop()
{
  // Nothing to do during loop
}    


