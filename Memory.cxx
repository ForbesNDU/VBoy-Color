#include "Memory.h"

// Allocation
Memory::Memory(int msize) {
	size = msize;
	bytes = new uint8_t [size]; 
}

Memory::~Memory() {
	delete [] bytes;
}

// Get/Put functions won't throw address OOB errors in case of cartride errors (this behavior is poorly defined
// but should not occur when using a commercial ROM cartridge)

void Memory::putByte(uint8_t data, int index) {
	if( (index < size) && (index >= 0) ) {
		bytes[index] = data;	// don't write anything
	}
}

uint8_t Memory::getByte(int index) const {
	if( (index >= size) || (index < 0) ) {
		return 0;		// provide dummy value
	} else {
		return bytes[index];
	}
}

const uint8_t Memory::operator[](int index) const {
	if( (index >= size) || (index < 0) ) {
		return 0;
	} else {
		return bytes[index];
	}
}
