#ifndef RWH_FAKE_H_
#define RWH_FAKE_H_

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#ifndef EEPROM_SIZE
#define EEPROM_SIZE 512
#endif

uint8_t fake_eeprom[EEPROM_SIZE];

#define WRITE(POS, VAL) fake_eeprom[(POS)] = VAL
#define READ(POS) (fake_eeprom[POS])
#define UPDATE(POS, VAL) if(READ(POS) != VAL){WRITE(POS, VAL);}

#endif /* RWH_FAKE_H_ */
