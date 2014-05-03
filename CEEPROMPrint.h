#ifndef CEEPROMPRINT_H_
#define CEEPROMPRINT_H_

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#ifndef DBG
#include "DBG_Arduino.h"
#endif

#ifndef READ
#include "RWH_Arduino.h"
#endif /*READ*/

#ifndef EEPROM_OFFSET
#define EEPROM_OFFSET 0
#endif

class CEEPROMPrintClass {
public:
	static void printChunk(uint8_t* chunk) {
		DBG("(");DBG(int(chunk[0]));DBG(")\t");
		DBG("[ ");
		for (int i = 1; i <= chunk[0]; i++) {
			DBG(int(chunk[i]));DBG(" ");
		}
		DBGL("]");
	}

	static void printStorageDump(uint8_t linebreakAfter = 16,
			uint16_t length = (EEPROM_SIZE - EEPROM_OFFSET)) {
		printEEPROMDump(linebreakAfter, EEPROM_OFFSET, EEPROM_OFFSET + length);
	}

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

};
/* CEEPROMPrintClass */

extern CEEPROMPrintClass CEEPROMPrint;

#endif /* CEEPROMPRINT_H_ */
