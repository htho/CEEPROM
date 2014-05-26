/*
	ceeprom_chunks_demo

	Demonstrates Reading, Writing and Removing Arrays from faked EEPROM.
	Faking the EEPROM means that instead of using the EEPROM, an array
	is used. This nice for debugging without wearing the EEPROM Cells.
	Of course data is not stored persistently as it would if the EEPROM
	was actually used.
	
	A Chunk is simply an array, where the first field contains the length of the array. 

	The circuit:
	* no components need to be attached.

	Created 14.05.2014
	By Hauke Thorenz

	https://github.com/htho/CEEPROM
*/

//Defines that EEPROM should be faked.
#define FAKE_EEPROM

//Defines that CEEPROMs printing functions should be available (DBG(STR) needs to be definde too!)
#define CEEPROM_PRINT

//Defines that CHUNKS printing functions should be available (DBG(STR) needs to be definde too!)
#define CHUNKS_PRINT

//The Printing functions need this Macro
#define DBG(STR) Serial.print(STR);

//The CEEPROM Functionality
#include <CEEPROM.h> 
//The CHUNK Functionality
#include <CHUNKS.h> 

void setup()
{
  Serial.begin(9600);
  CEEPROM.format(); //Formats CEEPROM (nessesary for this test!)

//Part 1: Storing data.

  // TEST 1 pt 1
  Serial.println("Testing Integer Array...");
  int dataArray[] = {1, 512, 1024};

  Serial.println("Original Data:");
  for (int i = 0; i < 3; i++) {
    Serial.println(dataArray[i]);
  }
  Serial.print('\n');

  uint8_t* chunkArray = CHUNKS.create<int>(dataArray, 3); //creates a chunk from an integer array, which has 3 elements.
  CHUNKS.printChunk(chunkArray);
  
  CEEPROM.add(chunkArray); //Stores chunk1 in EEPROM.
  
  delete chunkArray;

  // TEST 2 pt 1
  Serial.println("Testing Integer Value...");
  int value = 42;

  Serial.println("Original Data:");
  Serial.println(value);

  uint8_t* chunkValue = CHUNKS.create<int>(value); //creates a chunk from an integer array, which has 3 elements.
  CHUNKS.printChunk(chunkValue);
  
  CEEPROM.add(chunkValue); //Stores chunk2 in EEPROM.
  
  delete chunkValue;

  // TEST 3 pt 1
  Serial.println("Testing Text...");
  char text[] = "Hello World";

  Serial.println("Original Data:");
  Serial.println(text);

  uint8_t* chunkText = CHUNKS.create<char>(text, sizeof(text)); //creates a chunk from an integer array, which has 3 elements.
  CHUNKS.printChunk(chunkText);
  
  CEEPROM.add(chunkText); //Stores chunk3 in EEPROM.

  delete chunkText;

//Part 2: Reproducing Data.

uint8_t* chunkArrayReproduced = CEEPROM.get(0);
int* reproducedArray = CHUNKS.getPointer<int>(chunkArrayReproduced);

  Serial.println("Reproduced Data:");
  for (int i = 0; i < CHUNKS.length<int>(chunkArray); i++) {
    Serial.println(reproducedArray[i]);
  }
  Serial.print('\n');

uint8_t* chunkValueReproduced = CEEPROM.get(1);
int reproducedValue = CHUNKS.getValue<int>(chunkValueReproduced);

  Serial.println("Reproduced Data:");
  Serial.println(reproducedValue);
  

uint8_t* chunkTextReproduced = CEEPROM.get(2);
char* reproducedText = CHUNKS.getPointer<char>(chunkTextReproduced);

  Serial.println("Reproduced Data:");
  Serial.println(reproducedText);

}
void loop()
{
  // Nothing to do during loop
}


