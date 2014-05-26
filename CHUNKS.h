/** @file CHUNKS.h
 * @brief Provides functionality to create and use Chunks.
 */

 #ifndef CHUNKS_H_
 #define CHUNKS_H_


#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

/** Create and use Chunks.
 * A Chunk is an array of bytes (uint8_t). The first field contains the amount of bytes this array is long.
 * When processing an array by its reference, it is known how many bytes this array takes.
 *
 * Any type can be stored as a chunk (as long it is not bigger than 255 bytes).
 */
class ChunkClass {
public:
	/** Create a Chunk from a reference.
	 *@tparam The type of data that should be put into this chunk
	 *@param  data A reference to the data that should be stored in this chunk
	 *@param  length An optional Argument. Needs to be set if the Reference points to an array.
	 */
	template<class T> static uint8_t* create(T* data, uint8_t length = 1) {
		return createFromPointer<T>((data), (length * sizeof(T)));
	}
	/** Create a Chunk from a value.
	 *@tparam The type of the Value that should be put into this chunk
	 *@param  data The Value that should be stored in this chunk
	 *@param  length An optional Argument. Needs to be set if the Value is an array.
	 */
	template<class T> static uint8_t* create(T value, uint8_t length = 1) {
		return createFromPointer<T>(&value, sizeof(T));
	}

	/**
	 * @param chunk The chunk which length should be returned.
	 * @return The amount of elements of an array stored in this chunk.
	 */
	template<class T> static uint8_t length(uint8_t* chunk) {
		return chunk[0] / sizeof(T);
	}

	/**
	 * @param chunk The chunk which size should be returned.
	 * @return The amount of bytes stored in this chunk.
	 * @note The chunk takes up one byte more in memory.
	 */
	static uint8_t size(uint8_t* chunk) {
		return chunk[0];
	}

	/**
	 * @param chunk The chunk to use.
	 * @tparam The type of the data that is stored in the given chunk.
	 * @return A pointer to the data stored in this chunk
	 */
	template<class T> static T* getPointer(uint8_t* chunk) {
		return (T*) (chunk + 1);
	}

	/**
	 * @param chunk The chunk to use.
	 * @tparam The type of the value that is stored in the given chunk.
	 * @return The Value that is stored in the given chunk.
	 */
	template<class T> static T getValue(uint8_t* chunk) {
		return *(getPointer<T>(chunk));
	}

#ifdef CHUNKS_PRINT
	/** Prints the given chunk.
	 * @param chunk The chunk to print.
	 * @note #CHUNKS_PRINT needs to be defined in order to use this function.
	 */
	static void printChunk(uint8_t* chunk) {
		DBG("(");DBG(int(chunk[0]));DBG(")\t");
		DBG("[ ");
		for (int i = 1; i <= chunk[0]; i++) {
			DBG(int(chunk[i]));DBG(" ");
		}
		DBG("]");
	}
#endif

private:
	/** Creates a chunk from the given pointer.
	 *
	 */
	template<class T> static uint8_t* createFromPointer(T* data,
			uint8_t length) {
		uint8_t* in = (uint8_t*) data;
		uint8_t* chunk = new uint8_t[length + 1];
		chunk[0] = length;
		for (uint8_t i = 0; i < length; i++) {
			chunk[i + 1] = in[i];
		}
		return chunk;
	}

};

extern ChunkClass CHUNKS;

#endif /* CHUNKS_H_ */
