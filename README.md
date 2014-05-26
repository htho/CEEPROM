CEEPROM
=======

An Arduino library to store values of different types and multiple arrays of different sizes in EEPROM without keeping track of their adresses.

In order to use CEEPROM you need to

```cpp   
#include <CEEPROM.h>
```

##Chunks
As CEEPROM itself is only able to store unsigned bytes (uint8_t), any data stored is stored as "chunks".
A "chunk" is an uint8_t array, where the first value describes the amount of bytes stored in the chunk.

```cpp
uint8_t example_chunk[] = {2, 42, 43}; //length=2, values={42, 43}
```

###`CHUNKS.h`
`CHUNKS.h` provides helper functions to create chunks.

```cpp   
#include <CHUNKS.h>
```

####Chunk Creation

`uint8_t* CHUNKS.create<T>(T* data, uint8_t length = 1)` and `uint8_t* CHUNKS.create<T>(T data, uint8_t length = 1)` Create a chunk from the given data and the length. It allocates memory for the new array and returns a Pointer, so the Programmer is responsible for deleting the array when it is not needed anymore.

An example:
```cpp   
uint8_t length = 2;
int data[] = {1024, 512};
uint8_t* chunk = CHUNKS.create<int>(data, length);
//...do something here...
delete chunk;
```

Not only arrays, but single values can be stored too:
```cpp   
float value = 3.1415;
uint8_t* chunk = CHUNKS.create<float>(value);
//...do something here...
delete chunk;
```

See the exmple sketches for more possibilitys to store data.

####Getting Length and Data
`uint8_t CHUNKS.length<T>(uint8_t* chunk)` returns the length of the given
chunk and `uint8_t* CHUNKS.getPointer<T>(uint8_t* chunk)` returns
a pointer to the data. `uint8_t* CHUNKS.getValue<T>(uint8_t* chunk)`
returns the Value stored.

```cpp
uint8_t chunk[] = {2, 42, 43}; //length=2, values={42, 43}
uint8_t* data = CHUNKS.getPointer<uint8_t>(chunk);
for (int i = 0; i < CEEPROM.length(chunk); i++) {
  //...do something with data[i]...
}
```

```cpp
float value = 3.14;
uint8_t* chunk = CHUNKS.create<int>(value);

float retrievedValue = CHUNKS.getValue<int>(chunk);
```

##Usage

###Adding Chunks
`void CEEPROM.add(uint8_t* chunk)` Adds a chunk to the storage and returns its position. New chunks are appended.

```cpp
uint8_t chunk[] = {2, 42, 43}; //length=2, values={42, 43}
uint16_t pos = CEEPROM.add(chunk);
```

###Reading Chunks
`uint8_t* CEEPROM.get(uint16_t position)` Retrieves a Chunk from Storage.
It allocates a memory for the new array and returns a Pointer, so the
Programmer is responsible for deleting the array when it is not needed anymore.

```cpp
uint8_t* chunk = CEEPROM.get(0); //Retrieves the first chunk in storage.
//..do something with the chunk...
delete chunk;
```

###Removing Chunks
`void CEEPROM.remove(uint16_t position)` Removes the chunk at the given position.
Implementaion info: Remaining data is moved. The lower the position
the more time it takes to remove the chunk. This also wears out EEPROM cells.

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
`void format()` deletes all chunks. This is needed to initailize the EEPROM for first usage.

## #define Macros
Some `#define` macros can be used to adjust the functionality. For basic usage, none of them are needed.

```cpp
//Defines an Offset from which to use EEPROM for chunked data.
//This is useful if your sketch or othere libraries need a fixed area in EEPROM.
#define EEPROM_OFFSET 32

//Defines the size of the EEPROM, if not defined, 512 bytes of EEPROM are assumed.
#define EEPROM_SIZE 1024
```

##Printing
CHUNKS and CEEPROM have printing functions that can be enabled by defining
the macros `CHUNKS_PRINT` and or `CEEPROM_PRINT` _before_ including CEEPROM.h and CHUKS.h. Both need the `DBG(STR)`
Macro to be defined.

An example for the `DBG(STR)` Macro.
```cpp
#define DBG(STR) Serial.print(STR)
```

##CEEPROM's printing Functions

To enable printing for CEEPROM (before including CEEPROM.h):
```cpp
#define CEEPROM_PRINT
```

These functions are provided:
```cpp
/** Prints the storage.
* @param linebreakAfter How Many values should be prointed before printing a linebreak.
* @param length The amount of bytes that should be printed.
* @note The Difference to printEEPROMDump() is: The part of the EEPROM that is actually used is printed.
* @note parameters can be omitted.
*/
printStorageDump(uint8_t linebreakAfter, uint16_t length);

/** Prints the EEPROM.
* @param linebreakAfter How Many values should be prointed before printing a linebreak.
* @param length The amount of bytes that should be printed.
* @note parameters can be omitted.
*/
void printEEPROMDump(uint8_t linebreakAfter, uint16_t lowerBound, uint16_t upperBound);
```

##CHUNKS's printing Functions

To enable printing for CHUNKS (before including CHUNKS.h):
```cpp
#define CHUNKS_PRINT
```

Here is an example for the usage of `CHUNKS.printChunk()`:
```cpp
for(int i = 0; i < CEEPROM.chunkCount(); i++){
  uint8_t* chunk = CEEPROM.get(i);
  CEEPROMPrint.printChunk(chunk);
  delete chunk;
}
```

## Faking EEPROM
In order to debug your scripts without wearing out the EEPROM cells, EEPROM can be faked.
Simply `#define FAKE_EEPROM`. Data will be stored in an array. Of course data will not be stored permanently.

## TODO
 - [ ] Improve Read Performance (by caching adresses)
 - [ ] Improve Memory Usage (by removing unnecessary variables)
 - [ ] Follow http://arduino.cc/en/Reference/APIStyleGuide
 - [ ] Follow http://arduino.cc/en/Reference/StyleGuide
