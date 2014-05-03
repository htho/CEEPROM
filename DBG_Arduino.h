#ifndef DBG_H_
#define DBG_H_

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif


#define DBG(STR) Serial.print(STR);
#define DBGL(STR) Serial.println(STR);

#define DBG_ARRAY(PTR, LEN) \
		DBG("{ "); \
		for(int DBG_ARRAY_i = 0; DBG_ARRAY_i < LEN; DBG_ARRAY_i++) { \
			DBG(int(PTR[DBG_ARRAY_i])); \
			DBG(" "); \
		}; \
		DBG("}"); \


#endif /* DBG_H_ */
