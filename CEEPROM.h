#ifndef CEEPROM_H_
#define CEEPROM_H_

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#ifndef READ
#include "RWH_Arduino.h"
#endif /*READ*/

#ifndef EEPROM_OFFSET
#define EEPROM_OFFSET 0
#endif

class CEEPROMClass
{
public:
	//Creates a chunk from length and data. Calls "new" so don't forget to "delete" after usage.
	static uint8_t* createChunk(uint8_t length, uint8_t* data){
		uint8_t* chunk = new uint8_t[length+1];
		chunk[0] = length;
		for (uint8_t i = 1; i < length+1; i++) {
			chunk[i] = data[i];
		}
		return chunk;
	}

	///Returns the length of the chunk at the given Pointer.
	static uint8_t chunkLength(uint8_t* chunk){
		return chunk[0];
	}

	///Returns a Pointer to the data of the chunk at the given Pointer.
	static uint8_t* chunkData(uint8_t* chunk){
		return chunk+1;
	}

	///Adds a chunk to the storage and returns the position.
	static uint16_t add(uint8_t* chunk){
		uint8_t position = chunkCount();
		uint16_t address = getAddress(position);
		writeChunk(chunk, address);
		UPDATE(address+chunk[0]+1, 0); //Makes sure random data at the end wont be interpreted as values
		return position;
	}

	///Removes a chunk from the storage.
	static void remove(uint16_t position){
		uint16_t nextFreeAddress = getAddress(chunkCount());
		uint16_t from = getAddress(position + 1); //TODO: From can be calculated from to.
		uint16_t to = getAddress(position);
		uint8_t len = READ(to); //== length of the chunk at the given position
		moveDataLeft(from, to, nextFreeAddress - to);
		UPDATE(nextFreeAddress - len - 1, 0); //Makes sure random data at the end wont be interpreted as values
	}

	///Retrieves a Chunk in Storage. Calls "new" so don't forget to "delete" after usage.
	static uint8_t* get(uint16_t position){
		uint16_t address = getAddress(position);
		uint8_t length = READ(address);
		uint8_t* chunk = new uint8_t[length+1];
		for (uint8_t i = 0; i < length+1; i++) {
			chunk[i] = READ(address+i);
		}
		return chunk;
	}

	///Returns the amount of chunks that are stored
	static uint16_t chunkCount() {
		uint16_t length = 0;
		uint16_t address = EEPROM_OFFSET;
		uint8_t currentValue = 0;
		while ((currentValue = READ(address)) != 0) {
			address = address + currentValue + 1;
			length++;
		}
		return length;
	}

	///"Formats" the Storage. All Chunks are removed.
	static void format() {
		UPDATE(EEPROM_OFFSET,0);
	}

private:
	static uint16_t getAddress(uint8_t position) {
		uint16_t address = EEPROM_OFFSET;
		while (position > 0) {
			address = address + READ(address) + 1;
			position--;
		}
		return address;
	}

	static void moveDataLeft(uint16_t from, uint16_t to, uint16_t length) {
		for (uint16_t i = 0; i <= length + 1; i++) {
			UPDATE(to + i, READ(from + i));
		}
	}

	static void writeChunk(uint8_t* chunk, uint16_t address) {
		for (uint8_t i = 0; i <= chunk[0]; i++) {
			UPDATE(address + i, chunk[i]);
		}
	}
}; /* CEEPROMClass */

extern CEEPROMClass CEEPROM;


#endif /* CEEPROM_H_ */
