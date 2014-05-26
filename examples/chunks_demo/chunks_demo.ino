/*
	chunks_demo

	Demonstrates the usage of chunks.

	The circuit:
	* no components need to be attached.

	Created 14.05.2014
	By Hauke Thorenz

	https://github.com/htho/CEEPROM
*/

//Defines that CHUNKS printing functions should be available (DBG(STR) needs to be definde too!)
#define CHUNKS_PRINT

//The Printing functions need this Macro
#define DBG(STR) Serial.print(STR);

//The CHUNK Functionality
#include <CHUNKS.h>

void setup()
{
  Serial.begin(9600);

  // TEST 1
  Serial.println("Testing Integer Array...");
  int dataArray[] = {1, 512, 1024};

  Serial.println("Original Data:");
  for (int i = 0; i < 3; i++) {
    Serial.println(dataArray[i]);
  }
  Serial.print('\n');

  uint8_t* chunkArray = CHUNKS.create<int>(dataArray, 3); //creates a chunk from an integer array, which has 3 elements.
  CHUNKS.printChunk(chunkArray);
  int* reproducedArray = CHUNKS.getPointer<int>(chunkArray);

  Serial.println("Reproduced Data:");
  for (int i = 0; i < CHUNKS.length<int>(chunkArray); i++) {
    Serial.println(reproducedArray[i]);
  }
  Serial.print('\n');

  delete chunkArray;

  // TEST 2
  Serial.println("Testing Integer Value...");
  int value = 42;

  Serial.println("Original Data:");
  Serial.println(value);

  uint8_t* chunkValue = CHUNKS.create<int>(value); //creates a chunk from an integer array, which has 3 elements.
  CHUNKS.printChunk(chunkValue);
  int reproducedValue = CHUNKS.getValue<int>(chunkValue);

  Serial.println("Reproduced Data:");
  Serial.println(reproducedValue);

  delete chunkValue;

  // TEST 2
  Serial.println("Testing Text...");
  char text[] = "Hello World";

  Serial.println("Original Data:");
  Serial.println(text);

  uint8_t* chunkText = CHUNKS.create<char>(text, sizeof(text)); //creates a chunk from an integer array, which has 3 elements.
  CHUNKS.printChunk(chunkText);
  char* reproducedText = CHUNKS.getPointer<char>(chunkText);

  Serial.println("Reproduced Data:");
  Serial.println(reproducedText);

  delete chunkText;

}
void loop()
{
  // Nothing to do during loop
}


