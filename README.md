CEEPROM
=======

An Arduino library to store multiple arrays of different sizes in EEPROM without keeping track of their adresses.

In order to use CEEPROM you need to

```cpp   
#include <CEEPROM.h>
```

##Chunks
Arrays are read and written as "chunks". A "chunk" is an array, where the first value describes the length of the chunk.

```cpp   
uint8_t chunk[] = {2, 42, 43}; //length=2, values={42, 43}
```

###Helper: Creating a Chunk
`uint8_t* CEEPROM.createChunk(uint8_t length, uint8_t* data)` Creates a chunk from an array and the length. It allocates memory for the new array and returns a Pointer, so the Programmer is responsible for deleting the array when it is not needed anymore.

```cpp
uint8_t length = 2;
uint8_t data[] = {42, 43};
uint8_t* chunk = CEEPROM.createChunk(length, data);
//...do something here...
delete chunk;
```

###Helper: Getting Length and Data
`uint8_t CEEPROM.chunkLength(uint8_t* chunk)` returns the length of the given chunk and `uint8_t* CEEPROM.chunkData(uint8_t* chunk)` returns a pointer to the data (no new memory is allocated).

```cpp
uint8_t chunk[] = {2, 42, 43}; //length=2, values={42, 43}
uint8_t* data = CEEPROM.chunkData(chunk);
for (int i = 0; i < CEEPROM.chunkLength(chunk); i++) {
  //...do something with data[i]...
}
```

##Usage

###Adding Chunks
`void CEEPROM.add(uint8_t* chunk)` Adds a chunk to the storage and returns its position. New chunks are appended.

```cpp
uint8_t chunk[] = {2, 42, 43}; //length=2, values={42, 43}
uint16_t pos = CEEPROM.add(chunk);
```

###Reading Chunks
`uint8_t* CEEPROM.get(uint16_t position)` Retrieves a Chunk from Storage. It allocates memory for the new array and returns a Pointer, so the Programmer is responsible for deleting the array when it is not needed anymore.

```cpp
uint8_t* chunk = CEEPROM.get(0); //Retrieves the first chunk in storage.
//..do something with the chunk...
delete chunk;
```

###Removing Chunks
`void CEEPROM.remove(uint16_t position)` Removes the chunk at the given position.
Implementaion info: Remaining data is moved. The lower the position the more time it takes to remove the chunk. This also wears out EEPROM cells.

```cpp
CEEPROM.remove(0); //removes the first chunk in storage
```

###Amount of Chunks
`uint16_t chunkCount()` returns the amount of chunks stored.

```cpp
for(int i = 0; i < CEEPROM.chunkCount(); i++){
  uint8_t* chunk = CEEPROM.get(i);
  //..do something with the chunk...
  delete chunk;
}
```

###Initialization
`void format()` deletes all chunks. This is needed to initailize the EEPROM for first usage. So its not called at the beginning of each sketch. Instead its called once, in order to initialize the board for using CEEPROM in the future.

## #define Macros
Some `#define` macros can be used to adjust the functionality. For basic usage, none of them are needed.

```cpp
//Defines an Offset from which to use EEPROM for chunked data.
//This is useful if your sketch or othere libraries need a fixed area in EEPROM.
#define EEPROM_OFFSET 32

//Defines the size of the EEPROM, if not defined, 512 bytes of EEPROM are assumed.
#define EEPROM_SIZE 1024
```

These Macros have to be defined before including `CEEPROM.h`.

##Helpers

In order to help debuging, there is `CEEPROMPrint.h` which provides functions to print chunks and storage.

```cpp   
#include <CEEPROMPRINT.h>

//Prints a chunk using Serial.println();
void printChunk(uint8_t* chunk);

//Prints the used storage using Serial.print();
//Parameters can be omitted, there are sane default values.
void printStorageDump(uint8_t linebreakAfter, uint16_t length);

//Prints the given portion of the EEPROM using Serial.print();
//Parameters can be omitted, there are sane default values.
void printEEPROMDump(uint8_t linebreakAfter, uint16_t lowerBound, uint16_t upperBound);
```

Here an example for the usage of `CEEPROMPrint.printChunk()`:
```cpp
for(int i = 0; i < CEEPROM.chunkCount(); i++){
  uint8_t* chunk = CEEPROM.get(i);
  CEEPROMPrint.printChunk(chunk);
  delete chunk;
}
```

## Faking EEPROM
In order to debug your scripts without wearing out the EEPROM cells, EEPROM can be faked.
Simply `#include <RWH_Fake.h>`. Of course data will not be stored permanently.

## TODO
 - [ ] Improve Read Performance (by caching adresses)
 - [ ] Improve Memory Usage (by removing unnecessary variables)
 - [ ] Follow http://arduino.cc/en/Reference/APIStyleGuide
 - [ ] Follow http://arduino.cc/en/Reference/StyleGuide
