#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <stdlib.h>

class Memory {
	public:
		Memory(int);
		~Memory();

		void putByte(uint8_t, int);
		uint8_t getByte(int) const;
		
		const uint8_t operator[](int) const; 	// Getter

	private:
		uint8_t *bytes;
		int size;

};

#endif
