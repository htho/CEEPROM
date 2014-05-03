#ifndef RWH_ARDUINO_H_
#define RWH_ARDUINO_H_

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif


#ifndef EEPROM_SIZE
#define EEPROM_SIZE 512
#endif

#include <avr/eeprom.h>

#define WRITE(POS, VAL) eeprom_write_byte((uint8_t *)POS, VAL)
#define READ(POS) eeprom_read_byte((uint8_t *)POS)
#define UPDATE(POS, VAL) if(READ(POS) != VAL){WRITE(POS, VAL);}


#endif /* RWH_ARDUINO_H_ */
