/** @file CEEPROM.h
 * @brief Provides functionality to store chunks in EEPROM.
 */
#ifndef CEEPROM_H_
#define CEEPROM_H_

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#ifndef EEPROM_SIZE
	#define EEPROM_SIZE 512 //< Default assumed EEPROM size. Define it if your Controller has more EEPROM.
#endif

#ifdef FAKE_EEPROM
	uint8_t fake_eeprom[EEPROM_SIZE]; //< The faked EEPROM.
	#define WRITE(POS, VAL) fake_eeprom[(POS)] = VAL
	#define READ(POS) (fake_eeprom[POS])
	#define UPDATE(POS, VAL) if(READ(POS) != VAL){WRITE(POS, VAL);}
#else
	#include <avr/eeprom.h>
	#define WRITE(POS, VAL) eeprom_write_byte((uint8_t *)POS, VAL)
	#define READ(POS) eeprom_read_byte((uint8_t *)POS)
	#define UPDATE(POS, VAL) if(READ(POS) != VAL){WRITE(POS, VAL);}
#endif

#ifndef EEPROM_OFFSET
	#define EEPROM_OFFSET 0 //< An offset for the EEPROM. So other parts of the sketch still can use EEPROM.
#endif

class CEEPROMClass {
public:

	/**Adds a chunk to the storage and returns the position.
	 * @param chunk The chunk to add.
	 */
	static uint16_t add(uint8_t* chunk) {
		uint8_t position = chunkCount();
		uint16_t address = getAddress(position);
		writeChunk(chunk, address);
		UPDATE(address + chunk[0] + 1, 0); //Makes sure random data at the end wont be interpreted as values
		return position;
	}

	/** Removes a chunk from the storage.
	 * @param position The position of th chunk to remove.
	 */
	static void remove(uint16_t position) {
		uint16_t nextFreeAddress = getAddress(chunkCount());
		uint16_t from = getAddress(position + 1); //TODO: From can be calculated from to.
		uint16_t to = getAddress(position);
		uint8_t len = READ(to); //== length of the chunk at the given position
		moveDataLeft(from, to, nextFreeAddress - to);
		UPDATE(nextFreeAddress - len - 1, 0); //Makes sure random data at the end wont be interpreted as values
	}

	/** Retrieves a Chunk from Storage.
	 * @param The position of the chunk to retrieve.
	 * @return A Reference to the chunk that was stored.
	 * @note Calls "new" so don't forget to "delete" after usage.
	 */
	static uint8_t* get(uint16_t position) {
		uint16_t address = getAddress(position);
		uint8_t length = READ(address);
		uint8_t* chunk = new uint8_t[length + 1];
		for (uint8_t i = 0; i < length + 1; i++) {
			chunk[i] = READ(address + i);
		}
		return chunk;
	}

	/**
	 * @return The amount of chunks that are stored.
	 */
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

	/**
	 * "Formats" the Storage. All Chunks are removed.
	 */
	static void format() {
		UPDATE(EEPROM_OFFSET, 0);
	}

#ifdef CEEPROM_PRINT
	/** Prints the storage.
	 * @param linebreakAfter How Many values should be prointed before printing a linebreak.
	 * @param length The amount of bytes that should be printed.
	 * @note The Difference to printEEPROMDump() is: The part of the EEPROM that is actually used is printed.
	 */
	static void printStorageDump(uint8_t linebreakAfter = 16,
			uint16_t length = (EEPROM_SIZE - EEPROM_OFFSET)) {
		printEEPROMDump(linebreakAfter, EEPROM_OFFSET, EEPROM_OFFSET + length);
	}
	/** Prints the EEPROM.
	 * @param linebreakAfter How Many values should be prointed before printing a linebreak.
	 * @param length The amount of bytes that should be printed.
	 */
	static void printEEPROMDump(uint8_t linebreakAfter = 16, uint16_t lowerBound = 0,
			uint16_t upperBound = EEPROM_SIZE) {
		for (uint8_t i = 0; i < linebreakAfter; i++) {
			DBG("|");
			DBG(int(i));
			DBG("\t");
		};
		DBG("\n");
		uint8_t linebreakCounter = 0;
		for (uint16_t i = lowerBound; i < upperBound; i++) {
			linebreakCounter++;
			DBG(" ");
			DBG(int(READ(i)));
			DBG("\t");
			if (linebreakCounter == linebreakAfter) {
				DBG("\n");
				linebreakCounter = 0;
			};
		};
		DBG("\n");
	}
#endif

private:
	/**
	 * @param The position of the chunk which address should be returned.
	 * @return The EEPROM address of the chunk at the given position.
	 */
	static uint16_t getAddress(uint8_t position) {
		uint16_t address = EEPROM_OFFSET;
		while (position > 0) {
			address = address + READ(address) + 1;
			position--;
		}
		return address;
	}

	/** Moves the given amount of bytes left from the given position to the given position.
	 * @param from the address from which to statrt.
	 * @param to the address to move the data to.
	 * @param length the amount of bytes that should be moved.
	 * @note This function stupidly moves data. Old data is not deleted. Usually the next byte should be set to 0.
	 */
	static void moveDataLeft(uint16_t from, uint16_t to, uint16_t length) {
		for (uint16_t i = 0; i <= length + 1; i++) {
			UPDATE(to + i, READ(from + i));
		}
	}

	/** Writes the given chunk, starting at the given address.
	 * @param chunk the chunk to store.
	 * @param address the address to start with.
	 */
	static void writeChunk(uint8_t* chunk, uint16_t address) {
		for (uint8_t i = 0; i <= chunk[0]; i++) {
			UPDATE(address + i, chunk[i]);
		}
	}
};
/* CEEPROMClass */

extern CEEPROMClass CEEPROM;

#endif /* CEEPROM_H_ */
