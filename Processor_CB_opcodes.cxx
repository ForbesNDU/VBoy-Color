#include "Processor.h"

////////////////////// HELPER METHODS //////////////////////

bool Processor::testMemoryBit(int idx) {
	uint8_t value = (*main_memory)[HL.getValue()];

	uint8_t result = value & (1 << idx);
	return (bool)result;
}

void Processor::resetMemoryBit(int idx) {
	uint8_t value = (*main_memory)[HL.getValue()]

        uint8_t result = value & ~(1 << idx);
	main_memory->putByte(result, HL.getValue());
}

void Processor::setMemoryBit(int idx) {
        uint8_t value = (*main_memory)[HL.getValue()]

        uint8_t result = value | (1 << idx);
        main_memory->putByte(result, HL.getValue());
}

////////////////////// OPCODE BLOCK 0x0* //////////////////////


// rlc b
void Processor::CB_opcode_0x00() {
	uint8_t carry = (BC.getHiByte() & (1 << 7)) >> 7;
	carryFlag = (bool)carry;
	BC.setHiByte( (BC.getHiByte() << 1) | carry);
}

// rlc c
void Processor::CB_opcode_0x01() {
        uint8_t carry = (BC.getLoByte() & (1 << 7)) >> 7;
        carryFlag = (bool)carry;
        BC.setLoByte( (BC.getLoByte() << 1) | carry);
}

// rlc d
void Processor::CB_opcode_0x02() {
        uint8_t carry = (DE.getHiByte() & (1 << 7)) >> 7;
        carryFlag = (bool)carry;
        DE.setHiByte( (DE.getHiByte() << 1) | carry);
}

// rlc e
void Processor::CB_opcode_0x03() {
        uint8_t carry = (DE.getLoByte() & (1 << 7)) >> 7;
        carryFlag = (bool)carry;
        DE.setLoByte( (DE.getLoByte() << 1) | carry);
}

// rlc h
void Processor::CB_opcode_0x04() {
        uint8_t carry = (HL.getHiByte() & (1 << 7)) >> 7;
        carryFlag = (bool)carry;
        HL.setHiByte( (HL.getHiByte() << 1) | carry);
}

// rlc l
void Processor::CB_opcode_0x05() {
        uint8_t carry = (HL.getLoByte() & (1 << 7)) >> 7;
        carryFlag = (bool)carry;
        HL.setLoByte( (HL.getLoByte() << 1) | carry);
}

// rlc (hl)
void Processor::CB_opcode_0x06() {
	uint8_t value = (*main_memory)[HL.getValue()];
        uint8_t carry = (value & (1 << 7)) >> 7;
        carryFlag = (bool)carry;
        value = (value << 1) | carry;
	main_memory->putByte( value, (int)HL.getValue() );
}

// rlc a
void Processor::CB_opcode_0x07() {
        uint8_t carry = (AF.getHiByte() & (1 << 7)) >> 7;
        carryFlag = (bool)carry;
        AF.setLoByte( (AF.getHiByte() << 1) | carry);
}

// rrc b
void Processor::CB_opcode_0x08() {
	uint8_t carry = BC.getHiByte() & 1;
	carryFlag = (bool)carry;
	BC.setHiByte( (BC.getHiByte() >> 1) | (carry << 7) );
}

// rrc c
void Processor::CB_opcode_0x09() {
        uint8_t carry = BC.getLoByte() & 1;
        carryFlag = (bool)carry;
        BC.setLoByte( (BC.getLoByte() >> 1) | (carry << 7) );
}

// rrc d
void Processor::CB_opcode_0x0A() {
        uint8_t carry = DE.getHiByte() & 1;
        carryFlag = (bool)carry;
        DE.setHiByte( (DE.getHiByte() >> 1) | (carry << 7) );
}

// rrc e
void Processor::CB_opcode_0x0B() {
        uint8_t carry = DE.getLoByte() & 1;
        carryFlag = (bool)carry;
        DE.setHiByte( (DE.getLoByte() >> 1) | (carry << 7) );
}

// rrc h
void Processor::CB_opcode_0x0C() {
        uint8_t carry = HL.getHiByte() & 1;
        carryFlag = (bool)carry;
        HL.setHiByte( (HL.getHiByte() >> 1) | (carry << 7) );
}

// rrc l
void Processor::CB_opcode_0x0D() {
        uint8_t carry = HL.getLoByte() & 1;
        carryFlag = (bool)carry;
        HL.setHiByte( (HL.getLoByte() >> 1) | (carry << 7) );
}

// rrc (hl)
void Processor::CB_opcode_0x0E() {
	uint8_t value = (*main_memory)[HL.getValue()];
        uint8_t carry = value & 1;
        carryFlag = (bool)carry;
        value = (value >> 1) | (carry << 7);
	main_memory->putByte( value, HL.getValue() );
}

// rrc a
void Processor::CB_opcode_0x0F() {
        uint8_t carry = BC.getHiByte() & 1;
        carryFlag = (bool)carry;
        BC.setHiByte( (BC.getHiByte() >> 1) | (carry << 7) );
}


////////////////////// OPCODE BLOCK 0x1* //////////////////////


// rl b
void Processor::CB_opcode_0x10() {
        uint8_t newCarry = (BC.getHiByte() & (1 << 7)) >> 7;
        BC.setHiByte( (BC.getHiByte() << 1) | (uint8_t)carryFlag );
        carryFlag = (bool)newCarry;
}

// rl c
void Processor::CB_opcode_0x11() {
        uint8_t newCarry = (BC.getLoByte() & (1 << 7)) >> 7;
        BC.setLoByte( (BC.getLoByte() << 1) | (uint8_t)carryFlag );
        carryFlag = (bool)newCarry;
}

// rl d
void Processor::CB_opcode_0x12() {
        uint8_t newCarry = (DE.getHiByte() & (1 << 7)) >> 7;
        DE.setHiByte( (DE.getHiByte() << 1) | (uint8_t)carryFlag );
        carryFlag = (bool)newCarry;
}

// rl e
void Processor::CB_opcode_0x13() {
        uint8_t newCarry = (DE.getLoByte() & (1 << 7)) >> 7;
        DE.setLoByte( (DE.getLoByte() << 1) | (uint8_t)carryFlag );
        carryFlag = (bool)newCarry;
}

// rl h
void Processor::CB_opcode_0x14() {
        uint8_t newCarry = (HL.getHiByte() & (1 << 7)) >> 7;
        HL.setHiByte( (HL.getHiByte() << 1) | (uint8_t)carryFlag );
        carryFlag = (bool)newCarry;
}

// rl l
void Processor::CB_opcode_0x15() {
        uint8_t newCarry = (HL.getLoByte() & (1 << 7)) >> 7;
        HL.setHiByte( (HL.getLoByte() << 1) | (uint8_t)carryFlag );
        carryFlag = (bool)newCarry;
}

// rl (hl)
void Processor::CB_opcode_0x16() {
	uint8_t value = (*main_memory)[HL.getValue()];
        uint8_t newCarry = (value & (1 << 7)) >> 7;
        value = (value << 1) | (uint8_t)carryFlag;
        carryFlag = (bool)newCarry;
	main_memory->putByte( value, HL.getValue() );
}

// rl a
void Processor::CB_opcode_0x17() {
        uint8_t newCarry = (AF.getHiByte() & (1 << 7)) >> 7;
        AF.setHiByte( (AF.getHiByte() << 1) | (uint8_t)carryFlag );
        carryFlag = (bool)newCarry;
}

// rr b
void Processor::CB_opcode_0x18() {
	uint8_t newCarry = BC.getHiByte() & 1;
	BC.setHiByte( (BC.getHiByte() >> 1) | ((uint8_t)carryFlag << 7) );
	carryFlag = (bool)newCarry;
}

// rr c
void Processor::CB_opcode_0x19() {
        uint8_t newCarry = BC.getLoByte() & 1;
        BC.setLoByte( (BC.getLoByte() >> 1) | ((uint8_t)carryFlag << 7) );
        carryFlag = (bool)newCarry;
}

// rr d
void Processor::CB_opcode_0x1A() {
        uint8_t newCarry = DE.getHiByte() & 1;
        DE.setHiByte( (DE.getHiByte() >> 1) | ((uint8_t)carryFlag << 7) );
        carryFlag = (bool)newCarry;
}

// rr e
void Processor::CB_opcode_0x1B() {
        uint8_t newCarry = DE.getLoByte() & 1;
        DE.setLoByte( (DE.getLoByte() >> 1) | ((uint8_t)carryFlag << 7) );
        carryFlag = (bool)newCarry;
}

// rr h
void Processor::CB_opcode_0x1C() {
        uint8_t newCarry = HL.getHiByte() & 1;
        HL.setHiByte( (HL.getHiByte() >> 1) | ((uint8_t)carryFlag << 7) );
        carryFlag = (bool)newCarry;
}

// rr l
void Processor::CB_opcode_0x1D() {
        uint8_t newCarry = HL.getLoByte() & 1;
        HL.setLoByte( (HL.getLoByte() >> 1) | ((uint8_t)carryFlag << 7) );
        carryFlag = (bool)newCarry;
}

// rr (hl)
void Processor::CB_opcode_0x1E() {
	uint8_t value = (*main_memory)[HL.getValue()];
        uint8_t newCarry = value & 1;
        value = (value >> 1) | ((uint8_t)carryFlag << 7);
        carryFlag = (bool)newCarry;
	main_memory->putByte( value, HL.getValue() );
}

// rr a
void Processor::CB_opcode_0x1F() {
        uint8_t newCarry = AF.getHiByte() & 1;
        AF.setHiByte( (AF.getHiByte() >> 1) | ((uint8_t)carryFlag << 7) );
        carryFlag = (bool)newCarry;
}


////////////////////// OPCODE BLOCK 0x2* //////////////////////


// sla b
void Processor::CB_opcode_0x20() {
	uint8_t carry = (BC.getHiByte() & (1 << 7)) >> 7;
	carryFlag = (bool)carry;
	BC.setHiByte( BC.getHiByte() << 1 );
}

// sla c
void Processor::CB_opcode_0x21() {
        uint8_t carry = (BC.getLoByte() & (1 << 7)) >> 7;
        carryFlag = (bool)carry;
        BC.setLoByte( BC.getLoByte() << 1 );
}

// sla d
void Processor::CB_opcode_0x22() {
        uint8_t carry = (DE.getHiByte() & (1 << 7)) >> 7;
        carryFlag = (bool)carry;
        DE.setHiByte( DE.getHiByte() << 1 );
}

// sla e
void Processor::CB_opcode_0x23() {
        uint8_t carry = (DE.getLoByte() & (1 << 7)) >> 7;
        carryFlag = (bool)carry;
        DE.setLoByte( DE.getLoByte() << 1 );
}

// sla h
void Processor::CB_opcode_0x24() {
        uint8_t carry = (HL.getHiByte() & (1 << 7)) >> 7;
        carryFlag = (bool)carry;
        HL.setHiByte( HL.getHiByte() << 1 );
}

// sla l
void Processor::CB_opcode_0x25() {
        uint8_t carry = (HL.getLoByte() & (1 << 7)) >> 7;
        carryFlag = (bool)carry;
        HL.setLoByte( HL.getLoByte() << 1 );
}

// sla (hl)
void Processor::CB_opcode_0x26() {
	uint8_t value = (main_memory*)[HL.getValue()];
        uint8_t carry = (value & (1 << 7)) >> 7;
        carryFlag = (bool)carry;
        value = BC.getHiByte() << 1;
	main_memory->putByte( value, HL.getValue() );
}

// sla a
void Processor::CB_opcode_0x27() {
        uint8_t carry = (AF.getHiByte() & (1 << 7)) >> 7;
        carryFlag = (bool)carry;
        AF.setHiByte( AF.getHiByte() << 1 );
}

// sra b
void Processor::CB_opcode_0x28() {
	uint8_t carry = BC.getHiByte() & 1;
	uint8_t bit7 = BC.getHiByte() & (1 << 7);
	carryFlag = (bool)carry;
	BC.setHiByte( (BC.getHiByte() >> 1) | bit7 ); 
}

// sra c
void Processor::CB_opcode_0x29() {
        uint8_t carry = BC.getLoByte() & 1;
        uint8_t bit7 = BC.getLoByte() & (1 << 7);
        carryFlag = (bool)carry;
        BC.setLoByte( (BC.getLoByte() >> 1) | bit7 );
}

// sra d
void Processor::CB_opcode_0x2A() {
        uint8_t carry = DE.getHiByte() & 1;
        uint8_t bit7 = DE.getHiByte() & (1 << 7);
        carryFlag = (bool)carry;
        DE.setHiByte( (DE.getHiByte() >> 1) | bit7 );
}

// sra e
void Processor::CB_opcode_0x2B() {
        uint8_t carry = DE.getLoByte() & 1;
        uint8_t bit7 = DE.getLoByte() & (1 << 7);
        carryFlag = (bool)carry;
        DE.setLoByte( (DE.getLoByte() >> 1) | bit7 );
}

// sra h
void Processor::CB_opcode_0x2C() {
        uint8_t carry = HL.getHiByte() & 1;
        uint8_t bit7 = HL.getHiByte() & (1 << 7);
        carryFlag = (bool)carry;
        HL.setHiByte( (HL.getHiByte() >> 1) | bit7 );
}

// sra l
void Processor::CB_opcode_0x2D() {
        uint8_t carry = HL.getLoByte() & 1;
        uint8_t bit7 = HL.getLoByte() & (1 << 7);
        carryFlag = (bool)carry;
        HL.setLoByte( (HL.getLoByte() >> 1) | bit7 );
}

// sra (hl)
void Processor::CB_opcode_0x2E() {
	uint8_t value = (*main_memory)[HL.getValue()];
        uint8_t carry = value & 1;
        uint8_t bit7 = value & (1 << 7);
        carryFlag = (bool)carry;
        value = (value >> 1) | bit7 ;
	main_memory->putByte( value, HL.getValue() );
}

// sra a
void Processor::CB_opcode_0x2F() {
        uint8_t carry = AF.getHiByte() & 1;
        carryFlag = (bool)carry;
        AF.setHiByte( AF.getHiByte() >> 1 );
}


////////////////////// OPCODE BLOCK 0x3* //////////////////////

// swap b
void Processor::CB_opcode_0x30() {
	uint8_t newLow = (BC.getHiByte() & 0xF0) >> 4;
	uint8_t newHigh = (BC.getHiByte() & 0x0F) << 4;
	BC.setHiByte( newLow + newHigh ); 
}

// swap c
void Processor::CB_opcode_0x31() {
        uint8_t newLow = (BC.getLoByte() & 0xF0) >> 4;
        uint8_t newHigh = (BC.getLoByte() & 0x0F) << 4;
        BC.setLoByte( newLow + newHigh );
}

// swap d
void Processor::CB_opcode_0x32() {
        uint8_t newLow = (DE.getHiByte() & 0xF0) >> 4;
        uint8_t newHigh = (DE.getHiByte() & 0x0F) << 4;
        DE.setHiByte( newLow + newHigh );
}

// swap e
void Processor::CB_opcode_0x33() {
        uint8_t newLow = (DE.getLoByte() & 0xF0) >> 4;
        uint8_t newHigh = (DE.getLoByte() & 0x0F) << 4;
        DE.setLoByte( newLow + newHigh );
}

// swap h
void Processor::CB_opcode_0x34() {
        uint8_t newLow = (HL.getHiByte() & 0xF0) >> 4;
        uint8_t newHigh = (HL.getHiByte() & 0x0F) << 4;
        HL.setHiByte( newLow + newHigh );
}

// swap l
void Processor::CB_opcode_0x35() {
        uint8_t newLow = (HL.getLoByte() & 0xF0) >> 4;
        uint8_t newHigh = (HL.getLoByte() & 0x0F) << 4;
        HL.setLoByte( newLow + newHigh );
}

// swap (hl)
void Processor::CB_opcode_0x36() {
	uint8_t value = (*main_memory)[HL.getValue()];
	uint8_t newLow = (value & 0xF0) >> 4;
        uint8_t newHigh = (value & 0x0F) << 4;
        value = newLow + newHigh;
	main_memory->putByte( value, HL.getValue() );
}

// swap a
void Processor::CB_opcode_0x37() {
        uint8_t newLow = (AF.getHiByte() & 0xF0) >> 4;
        uint8_t newHigh = (AF.getHiByte() & 0x0F) << 4;
        AF.setHiByte( newLow + newHigh );
}

// srl b
void Processor::CB_opcode_0x38() {
	uint8_t carry = BC.getHiByte() & 1;
	carryFlag = (bool)carry;
	BC.setHiByte(BC.getHiByte() >> 1);
}

// srl c
void Processor::CB_opcode_0x39() {
        uint8_t carry = BC.getLoByte() & 1;
        carryFlag = (bool)carry;
        BC.setLoByte(BC.getLoByte() >> 1);
}

// srl d
void Processor::CB_opcode_0x3A() {
        uint8_t carry = DE.getHiByte() & 1;
        carryFlag = (bool)carry;
        DE.setHiByte(DE.getHiByte() >> 1);
}

// srl e
void Processor::CB_opcode_0x3B() {
        uint8_t carry = DE.getLoByte() & 1;
        carryFlag = (bool)carry;
        DE.setLoByte(DE.getLoByte() >> 1);
}

// srl h
void Processor::CB_opcode_0x3C() {
        uint8_t carry = HL.getHiByte() & 1;
        carryFlag = (bool)carry;
        HL.setHiByte(HL.getHiByte() >> 1);
}

// srl l
void Processor::CB_opcode_0x3D() {
        uint8_t carry = HL.getLoByte() & 1;
        carryFlag = (bool)carry;
        HL.setHiByte(HL.getLoByte() >> 1);
}

// srl (hl)
void Processor::CB_opcode_0x3E() {
	uint8_t value = (*main_memory)[HL.getValue()];
	uint8_t carry = value & 1;
        carryFlag = (bool)carry;
        value = value >> 1;
	main_memory->putByte(value, HL.getValue());
}

// srl a
void Processor::CB_opcode_0x3F() {
        uint8_t carry = AF.getHiByte() & 1;
        carryFlag = (bool)carry;
        AF.setHiByte(AF.getHiByte() >> 1);
}


////////////////////// OPCODE BLOCK 0x4* //////////////////////


// bit 0, b
void Processor::CB_opcode_0x40() {
	zeroFlag = !BC.testHiBit(0);
}

// bit 0, c
void Processor::CB_opcode_0x41() {
        zeroFlag = !BC.testLoBit(0);
}

// bit 0, d
void Processor::CB_opcode_0x42() {
        zeroFlag = !DE.testHiBit(0);
}

// bit 0, e
void Processor::CB_opcode_0x43() {
        zeroFlag = !DE.testLoBit(0);
}

// bit 0, h
void Processor::CB_opcode_0x44() {
        zeroFlag = !HL.testHiBit(0);
}

// bit 0, l
void Processor::CB_opcode_0x45() {
        zeroFlag = !HL.testLoBit(0);
}

// bit 0, (hl)
void Processor::CB_opcode_0x46() {
        zeroFlag = !testMemoryBit(0);
}

// bit 0, a
void Processor::CB_opcode_0x47() {
        zeroFlag = !AF.testHiBit(0);
}

// bit 1, b
void Processor::CB_opcode_0x48() {
        zeroFlag = !BC.testHiBit(1);
}

// bit 1, c
void Processor::CB_opcode_0x49() {
        zeroFlag = !BC.testLoBit(1);
}

// bit 1, d
void Processor::CB_opcode_0x4A() {
        zeroFlag = !DE.testHiBit(1);
}

// bit 1, e
void Processor::CB_opcode_0x4B() {
        zeroFlag = !DE.testLoBit(1);
}

// bit 1, h
void Processor::CB_opcode_0x4C() {
        zeroFlag = !HL.testHiBit(1);
}

// bit 1, l
void Processor::CB_opcode_0x4D() {
        zeroFlag = !HL.testLoBit(1);
}

// bit 1, (hl)
void Processor::CB_opcode_0x4E() {
	zeroFlag = !testMemoryBit(1);
}

// bit 1, a
void Processor::CB_opcode_0x4F() {
        zeroFlag = !AF.testHiBit(1);
}


////////////////////// OPCODE BLOCK 0x5* //////////////////////


// bit 2, b
void Processor::CB_opcode_0x50() {
        zeroFlag = !BC.testHiBit(2);
}

// bit 2, c
void Processor::CB_opcode_0x51() {
        zeroFlag = !BC.testLoBit(2);
}

// bit 2, d
void Processor::CB_opcode_0x52() {
        zeroFlag = !DE.testHiBit(2);
}

// bit 2, e
void Processor::CB_opcode_0x53() {
        zeroFlag = !DE.testLoBit(2);
}

// bit 2, h
void Processor::CB_opcode_0x54() {
        zeroFlag = !HL.testHiBit(2);
}

// bit 2, l
void Processor::CB_opcode_0x55() {
        zeroFlag = !HL.testLoBit(2);
}

// bit 2, (hl)
void Processor::CB_opcode_0x56() {
        zeroFlag = !testMemoryBit(2);
}

// bit 2, a
void Processor::CB_opcode_0x57() {
        zeroFlag = !AF.testHiBit(2);
}

// bit 3, b
void Processor::CB_opcode_0x58() {
        zeroFlag = !BC.testHiBit(3);
}

// bit 3, c
void Processor::CB_opcode_0x59() {
        zeroFlag = !BC.testLoBit(3);
}

// bit 3, d
void Processor::CB_opcode_0x5A() {
        zeroFlag = !DE.testHiBit(3);
}

// bit 3, e
void Processor::CB_opcode_0x5B() {
        zeroFlag = !DE.testLoBit(3);
}

// bit 3, h
void Processor::CB_opcode_0x5C() {
        zeroFlag = !HL.testHiBit(3);
}

// bit 3, l
void Processor::CB_opcode_0x5D() {
        zeroFlag = !HL.testLoBit(3);
}

// bit 3, (hl)
void Processor::CB_opcode_0x5E() {
        zeroFlag = !testMemoryBit(3);
}

// bit 3, a
void Processor::CB_opcode_0x5F() {
        zeroFlag = !AF.testHiBit(3);
}


////////////////////// OPCODE BLOCK 0x6* //////////////////////


// bit 4, b
void Processor::CB_opcode_0x60() {
        zeroFlag = !BC.testHiBit(4);
}

// bit 4, c
void Processor::CB_opcode_0x61() {
        zeroFlag = !BC.testLoBit(4);
}

// bit 4, d
void Processor::CB_opcode_0x62() {
        zeroFlag = !DE.testHiBit(4);
}

// bit 4, e
void Processor::CB_opcode_0x63() {
        zeroFlag = !DE.testLoBit(4);
}

// bit 4, h
void Processor::CB_opcode_0x64() {
        zeroFlag = !HL.testHiBit(4);
}

// bit 4, l
void Processor::CB_opcode_0x65() {
        zeroFlag = !HL.testLoBit(4);
}

// bit 4, (hl)
void Processor::CB_opcode_0x66() {
        zeroFlag = !testMemoryBit(4);
}

// bit 4, a
void Processor::CB_opcode_0x67() {
        zeroFlag = !AF.testHiBit(4);
}

// bit 5, b
void Processor::CB_opcode_0x68() {
        zeroFlag = !BC.testHiBit(5);
}

// bit 5, c
void Processor::CB_opcode_0x69() {
        zeroFlag = !BC.testLoBit(5);
}

// bit 5, d
void Processor::CB_opcode_0x6A() {
        zeroFlag = !DE.testHiBit(5);
}

// bit 5, e
void Processor::CB_opcode_0x6B() {
        zeroFlag = !DE.testLoBit(5);
}

// bit 5, h
void Processor::CB_opcode_0x6C() {
        zeroFlag = !HL.testHiBit(5);
}

// bit 5, l
void Processor::CB_opcode_0x6D() {
        zeroFlag = !HL.testLoBit(5);
}

// bit 5, (hl)
void Processor::CB_opcode_0x6E() {
        zeroFlag = !testMemoryBit(5);
}

// bit 5, a
void Processor::CB_opcode_0x6F() {
        zeroFlag = !AF.testHiBit(5);
}


////////////////////// OPCODE BLOCK 0x7* //////////////////////


// bit 6, b
void Processor::CB_opcode_0x70() {
        zeroFlag = !BC.testHiBit(6);
}

// bit 6, c
void Processor::CB_opcode_0x71() {
        zeroFlag = !BC.testLoBit(6);
}

// bit 6, d
void Processor::CB_opcode_0x72() {
        zeroFlag = !DE.testHiBit(6);
}

// bit 6, e
void Processor::CB_opcode_0x73() {
        zeroFlag = !DE.testLoBit(6);
}

// bit 6, h
void Processor::CB_opcode_0x74() {
        zeroFlag = !HL.testHiBit(6);
}

// bit 6, l
void Processor::CB_opcode_0x75() {
        zeroFlag = !HL.testLoBit(6);
}

// bit 6, (hl)
void Processor::CB_opcode_0x76() {
        zeroFlag = !testMemoryBit(6);
}

// bit 6, a
void Processor::CB_opcode_0x77() {
        zeroFlag = !AF.testHiBit(6);
}

// bit 7, b
void Processor::CB_opcode_0x78() {
        zeroFlag = !BC.testHiBit(7);
}

// bit 7, c
void Processor::CB_opcode_0x79() {
        zeroFlag = !BC.testLoBit(7);
}

// bit 7, d
void Processor::CB_opcode_0x7A() {
        zeroFlag = !DE.testHiBit(7);
}

// bit 7, e
void Processor::CB_opcode_0x7B() {
        zeroFlag = !DE.testLoBit(7);
}

// bit 7, h
void Processor::CB_opcode_0x7C() {
        zeroFlag = !HL.testHiBit(7);
}

// bit 7, l
void Processor::CB_opcode_0x7D() {
        zeroFlag = !HL.testLoBit(7);
}

// bit 7, (hl)
void Processor::CB_opcode_0x7E() {
        zeroFlag = !testMemoryBit(7);
}

// bit 7, a
void Processor::CB_opcode_0x7F() {
        zeroFlag = !AF.testHiBit(7);
}


////////////////////// OPCODE BLOCK 0x8* //////////////////////


// res 0, b
void Processor::CB_opcode_0x80() {
	BC.resetHiBit(0);
}

// res 0, c
void Processor::CB_opcode_0x81() {
        BC.resetLoBit(0);
}

// res 0, d
void Processor::CB_opcode_0x82() {
        DE.resetHiBit(0);
}

// res 0, e
void Processor::CB_opcode_0x83() {
        DE.resetLoBit(0);
}

// res 0, h
void Processor::CB_opcode_0x84() {
        HL.resetHiBit(0);
}

// res 0, l
void Processor::CB_opcode_0x85() {
        HL.resetLoBit(0);
}

// res 0, (hl)
void Processor::CB_opcode_0x86() {
	resetMemoryBit(0);
}

// res 0, a
void Processor::CB_opcode_0x87() {
        AF.resetHiBit(0);
}

// res 1, b
void Processor::CB_opcode_0x88() {
        BC.resetHiBit(1);
}

// res 1, c
void Processor::CB_opcode_0x89() {
        BC.resetLoBit(1);
}

// res 1, d
void Processor::CB_opcode_0x8A() {
        DE.resetHiBit(1);
}

// res 1, e
void Processor::CB_opcode_0x8B() {
        DE.resetLoBit(1);
}

// res 1, h
void Processor::CB_opcode_0x8C() {
        HL.resetHiBit(1);
}

// res 1, l
void Processor::CB_opcode_0x8D() {
        HL.resetLoBit(1);
}

// res 1, (hl)
void Processor::CB_opcode_0x8E() {
        resetMemoryBit(1);
}

// res 1, a
void Processor::CB_opcode_0x8F() {
        AF.resetHiBit(1);
}


////////////////////// OPCODE BLOCK 0x9* //////////////////////


// res 2, b
void Processor::CB_opcode_0x90() {
        BC.resetHiBit(2);
}

// res 2, c
void Processor::CB_opcode_0x91() {
        BC.resetLoBit(2);
}

// res 2, d
void Processor::CB_opcode_0x92() {
        DE.resetHiBit(2);
}

// res 2, e
void Processor::CB_opcode_0x93() {
        DE.resetLoBit(2);
}

// res 2, h
void Processor::CB_opcode_0x94() {
        HL.resetHiBit(2);
}

// res 2, l
void Processor::CB_opcode_0x95() {
        HL.resetLoBit(2);
}

// res 2, (hl)
void Processor::CB_opcode_0x96() {
        resetMemoryBit(2);
}

// res 2, a
void Processor::CB_opcode_0x97() {
        AF.resetHiBit(2);
}

// res 3, b
void Processor::CB_opcode_0x98() {
        BC.resetHiBit(3);
}

// res 3, c
void Processor::CB_opcode_0x99() {
        BC.resetLoBit(3);
}

// res 3, d
void Processor::CB_opcode_0x9A() {
        DE.resetHiBit(3);
}

// res 3, e
void Processor::CB_opcode_0x9B() {
        DE.resetLoBit(3);
}

// res 3, h
void Processor::CB_opcode_0x9C() {
        HL.resetHiBit(3);
}

// res 3, l
void Processor::CB_opcode_0x9D() {
        HL.resetLoBit(3);
}

// res 3, (hl)
void Processor::CB_opcode_0x9E() {
        resetMemoryBit(3);
}

// res 3, a
void Processor::CB_opcode_0x9F() {
        AF.resetHiBit(3);
}


////////////////////// OPCODE BLOCK 0xA* //////////////////////


// res 4, b
void Processor::CB_opcode_0xA0() {
        BC.resetHiBit(4);
}

// res 4, c
void Processor::CB_opcode_0xA1() {
        BC.resetLoBit(4);
}

// res 4, d
void Processor::CB_opcode_0xA2() {
        DE.resetHiBit(4);
}

// res 4, e
void Processor::CB_opcode_0xA3() {
        DE.resetLoBit(4);
}

// res 4, h
void Processor::CB_opcode_0xA4() {
        HL.resetHiBit(4);
}

// res 4, l
void Processor::CB_opcode_0xA5() {
        HL.resetLoBit(4);
}

// res 4, (hl)
void Processor::CB_opcode_0xA6() {
        resetMemoryBit(4);
}

// res 4, a
void Processor::CB_opcode_0xA7() {
        AF.resetHiBit(4);
}

// res 5, b
void Processor::CB_opcode_0xA8() {
        BC.resetHiBit(5);
}

// res 5, c
void Processor::CB_opcode_0xA9() {
        BC.resetLoBit(5);
}

// res 5, d
void Processor::CB_opcode_0xAA() {
        DE.resetHiBit(5);
}

// res 5, e
void Processor::CB_opcode_0xAB() {
        DE.resetLoBit(5);
}

// res 5, h
void Processor::CB_opcode_0xAC() {
        HL.resetHiBit(5);
}

// res 5, l
void Processor::CB_opcode_0xAD() {
        HL.resetLoBit(5);
}

// res 5, (hl)
void Processor::CB_opcode_0xAE() {
        resetMemoryBit(5);
}

// res 5, a
void Processor::CB_opcode_0xAF() {
        AF.resetHiBit(5);
}


////////////////////// OPCODE BLOCK 0xB* //////////////////////


// res 6, b
void Processor::CB_opcode_0xB0() {
        BC.resetHiBit(6);
}

// res 6, c
void Processor::CB_opcode_0xB1() {
        BC.resetLoBit(6);
}

// res 6, d
void Processor::CB_opcode_0xB2() {
        DE.resetHiBit(6);
}

// res 6, e
void Processor::CB_opcode_0xB3() {
        DE.resetLoBit(6);
}

// res 6, h
void Processor::CB_opcode_0xB4() {
        HL.resetHiBit(6);
}

// res 6, l
void Processor::CB_opcode_0xB5() {
        HL.resetLoBit(6);
}

// res 6, (hl)
void Processor::CB_opcode_0xB6() {
        resetMemoryBit(6);
}

// res 6, a
void Processor::CB_opcode_0xB7() {
        AF.resetHiBit(6);
}

// res 7, b
void Processor::CB_opcode_0xB8() {
        BC.resetHiBit(7);
}

// res 7, c
void Processor::CB_opcode_0xB9() {
        BC.resetLoBit(7);
}

// res 7, d
void Processor::CB_opcode_0xBA() {
        DE.resetHiBit(7);
}

// res 7, e
void Processor::CB_opcode_0xBB() {
        DE.resetLoBit(7);
}

// res 7, h
void Processor::CB_opcode_0xBC() {
        HL.resetHiBit(7);
}

// res 7, l
void Processor::CB_opcode_0xBD() {
        HL.resetLoBit(7);
}

// res 7, (hl)
void Processor::CB_opcode_0xBE() {
        resetMemoryBit(7);
}

// res 7, a
void Processor::CB_opcode_0xBF() {
        AF.resetHiBit(7);
}


////////////////////// OPCODE BLOCK 0xC* //////////////////////


// set 0, b
void Processor::CB_opcode_0xC0() {
	BC.setHiBit(0);
}

// set 0, c
void Processor::CB_opcode_0xC1() {
        BC.setLoBit(0);
}

// set 0, d
void Processor::CB_opcode_0xC2() {
        DE.setHiBit(0);
}

// set 0, e
void Processor::CB_opcode_0xC3() {
        DE.setLoBit(0);
}

// set 0, h
void Processor::CB_opcode_0xC4() {
        HL.setHiBit(0);
}

// set 0, l
void Processor::CB_opcode_0xC5() {
        HL.setLoBit(0);
}

// set 0, (hl)
void Processor::CB_opcode_0xC6() {
	setMemoryBit(0);
}

// set 0, a
void Processor::CB_opcode_0xC7() {
        AF.setHiBit(0);
}

// set 1, b
void Processor::CB_opcode_0xC8() {
        BC.setHiBit(1);
}

// set 1, c
void Processor::CB_opcode_0xC9() {
        BC.setLoBit(1);
}

// set 1, d
void Processor::CB_opcode_0xCA() {
        DE.setHiBit(1);
}

// set 1, e
void Processor::CB_opcode_0xCB() {
        DE.setLoBit(1);
}

// set 1, h
void Processor::CB_opcode_0xCC() {
        HL.setHiBit(1);
}

// set 1, l
void Processor::CB_opcode_0xCD() {
        HL.setLoBit(1);
}

// set 1, (hl)
void Processor::CB_opcode_0xCE() {
        setMemoryBit(1);
}

// set 1, a
void Processor::CB_opcode_0xCF() {
        AF.setHiBit(1);
}


////////////////////// OPCODE BLOCK 0xD* //////////////////////


// set 2, b
void Processor::CB_opcode_0xD0() {
        BC.setHiBit(2);
}

// set 2, c
void Processor::CB_opcode_0xD1() {
        BC.setLoBit(2);
}

// set 2, d
void Processor::CB_opcode_0xD2() {
        DE.setHiBit(2);
}

// set 2, e
void Processor::CB_opcode_0xD3() {
        DE.setLoBit(2);
}

// set 2, h
void Processor::CB_opcode_0xD4() {
        HL.setHiBit(2);
}

// set 2, l
void Processor::CB_opcode_0xD5() {
        HL.setLoBit(2);
}

// set 2, (hl)
void Processor::CB_opcode_0xD6() {
        setMemoryBit(2);
}

// set 2, a
void Processor::CB_opcode_0xD7() {
        AF.setHiBit(2);
}

// set 3, b
void Processor::CB_opcode_0xD8() {
        BC.setHiBit(3);
}

// set 3, c
void Processor::CB_opcode_0xD9() {
        BC.setLoBit(3);
}

// set 3, d
void Processor::CB_opcode_0xDA() {
        DE.setHiBit(3);
}

// set 3, e
void Processor::CB_opcode_0xDB() {
        DE.setLoBit(3);
}

// set 3, h
void Processor::CB_opcode_0xDC() {
        HL.setHiBit(3);

}

// set 3, l
void Processor::CB_opcode_0xDD() {
        HL.setLoBit(3);
}

// set 3, (hl)
void Processor::CB_opcode_0xDE() {
        setMemoryBit(3);
}

// set 3, a
void Processor::CB_opcode_0xDF() {
        AF.setHiBit(3);
}


////////////////////// OPCODE BLOCK 0xE* //////////////////////


// set 4, b
void Processor::CB_opcode_0xE0() {
        BC.setHiBit(4);
}

// set 4, c
void Processor::CB_opcode_0xE1() {
        BC.setLoBit(4);
}

// set 4, d
void Processor::CB_opcode_0xE2() {
        DE.setHiBit(4);
}

// set 4, e
void Processor::CB_opcode_0xE3() {
        DE.setLoBit(4);
}

// set 4, h
void Processor::CB_opcode_0xE4() {
        HL.setHiBit(4);
}

// set 4, l
void Processor::CB_opcode_0xE5() {
        HL.setLoBit(4);
}

// set 4, (hl)
void Processor::CB_opcode_0xE6() {
        setMemoryBit(4);
}

// set 4, a
void Processor::CB_opcode_0xE7() {
        AF.setHiBit(4);
}

// set 5, b
void Processor::CB_opcode_0xE8() {
        BC.setHiBit(5);
}

// set 5, c
void Processor::CB_opcode_0xE9() {
        BC.setLoBit(5);
}

// set 5, d
void Processor::CB_opcode_0xEA() {
        DE.setHiBit(5);
}

// set 5, e
void Processor::CB_opcode_0xEB() {
        DE.setLoBit(5);
}

// set 5, h
void Processor::CB_opcode_0xEC() {
        HL.setHiBit(5);
}

// set 5, l
void Processor::CB_opcode_0xED() {
        HL.setLoBit(5);
}

// set 5, (hl)
void Processor::CB_opcode_0xEE() {
        setMemoryBit(5);
}

// set 5, a
void Processor::CB_opcode_0xEF() {
        AF.setHiBit(5);
}


////////////////////// OPCODE BLOCK 0xF* //////////////////////


// set 6, b
void Processor::CB_opcode_0xF0() {
        BC.setHiBit(6);
}

// set 6, c
void Processor::CB_opcode_0xF1() {
        BC.setLoBit(6);
}

// set 6, d
void Processor::CB_opcode_0xF2() {
        DE.setHiBit(6);
}

// set 6, e
void Processor::CB_opcode_0xF3() {
        DE.setLoBit(6);
}

// set 6, h
void Processor::CB_opcode_0xF4() {
        HL.setHiBit(6);
}

// set 6, l
void Processor::CB_opcode_0xF5() {
        HL.setLoBit(6);
}

// set 6, (hl)
void Processor::CB_opcode_0xF6() {
        setMemoryBit(6);
}

// set 6, a
void Processor::CB_opcode_0xF7() {
        AF.setHiBit(6);
}

// set 7, b
void Processor::CB_opcode_0xF8() {
        BC.setHiBit(7);
}

// set 7, c
void Processor::CB_opcode_0xF9() {
        BC.setLoBit(7);
}

// set 7, d
void Processor::CB_opcode_0xFA() {
        DE.setHiBit(7);
}

// set 7, e
void Processor::CB_opcode_0xFB() {
        DE.setLoBit(7);
}

// set 7, h
void Processor::CB_opcode_0xFC() {
        HL.setHiBit(7);
}

// set 7, l
void Processor::CB_opcode_0xFD() {
        HL.setLoBit(7);
}

// set 7, (hl)
void Processor::CB_opcode_0xFE() {
        setMemoryBit(7);
}

// set 7, a
void Processor::CB_opcode_0xFF() {
        AF.setHiBit(7);
}

void Processor::cb_map_populate() {

        cb_extension_map.insert( std::make_pair(0, &Processor::CB_opcode_0x00) );
        cb_extension_map.insert( std::make_pair(1, &Processor::CB_opcode_0x01) );
        cb_extension_map.insert( std::make_pair(2, &Processor::CB_opcode_0x02) );
        cb_extension_map.insert( std::make_pair(3, &Processor::CB_opcode_0x03) );
        cb_extension_map.insert( std::make_pair(4, &Processor::CB_opcode_0x04) );
        cb_extension_map.insert( std::make_pair(5, &Processor::CB_opcode_0x05) );
        cb_extension_map.insert( std::make_pair(6, &Processor::CB_opcode_0x06) );
        cb_extension_map.insert( std::make_pair(7, &Processor::CB_opcode_0x07) );
        cb_extension_map.insert( std::make_pair(8, &Processor::CB_opcode_0x08) );
        cb_extension_map.insert( std::make_pair(9, &Processor::CB_opcode_0x09) );
        cb_extension_map.insert( std::make_pair(10, &Processor::CB_opcode_0x0A) );
        cb_extension_map.insert( std::make_pair(11, &Processor::CB_opcode_0x0B) );
        cb_extension_map.insert( std::make_pair(12, &Processor::CB_opcode_0x0C) );
        cb_extension_map.insert( std::make_pair(13, &Processor::CB_opcode_0x0D) );
        cb_extension_map.insert( std::make_pair(14, &Processor::CB_opcode_0x0E) );
        cb_extension_map.insert( std::make_pair(15, &Processor::CB_opcode_0x0F) );

        cb_extension_map.insert( std::make_pair(16, &Processor::CB_opcode_0x10) );
        cb_extension_map.insert( std::make_pair(17, &Processor::CB_opcode_0x11) );
        cb_extension_map.insert( std::make_pair(18, &Processor::CB_opcode_0x12) );
        cb_extension_map.insert( std::make_pair(19, &Processor::CB_opcode_0x13) );
        cb_extension_map.insert( std::make_pair(20, &Processor::CB_opcode_0x14) );
        cb_extension_map.insert( std::make_pair(21, &Processor::CB_opcode_0x15) );
        cb_extension_map.insert( std::make_pair(22, &Processor::CB_opcode_0x16) );
        cb_extension_map.insert( std::make_pair(23, &Processor::CB_opcode_0x17) );
        cb_extension_map.insert( std::make_pair(24, &Processor::CB_opcode_0x18) );
        cb_extension_map.insert( std::make_pair(25, &Processor::CB_opcode_0x19) );
        cb_extension_map.insert( std::make_pair(26, &Processor::CB_opcode_0x1A) );
        cb_extension_map.insert( std::make_pair(27, &Processor::CB_opcode_0x1B) );
        cb_extension_map.insert( std::make_pair(28, &Processor::CB_opcode_0x1C) );
        cb_extension_map.insert( std::make_pair(29, &Processor::CB_opcode_0x1D) );
        cb_extension_map.insert( std::make_pair(30, &Processor::CB_opcode_0x1E) );
        cb_extension_map.insert( std::make_pair(31, &Processor::CB_opcode_0x1F) );

        cb_extension_map.insert( std::make_pair(32, &Processor::CB_opcode_0x20) );
        cb_extension_map.insert( std::make_pair(33, &Processor::CB_opcode_0x21) );
        cb_extension_map.insert( std::make_pair(34, &Processor::CB_opcode_0x22) );
        cb_extension_map.insert( std::make_pair(35, &Processor::CB_opcode_0x23) );
        cb_extension_map.insert( std::make_pair(36, &Processor::CB_opcode_0x24) );
        cb_extension_map.insert( std::make_pair(37, &Processor::CB_opcode_0x25) );
        cb_extension_map.insert( std::make_pair(38, &Processor::CB_opcode_0x26) );
        cb_extension_map.insert( std::make_pair(39, &Processor::CB_opcode_0x27) );
        cb_extension_map.insert( std::make_pair(40, &Processor::CB_opcode_0x28) );
        cb_extension_map.insert( std::make_pair(41, &Processor::CB_opcode_0x29) );
        cb_extension_map.insert( std::make_pair(42, &Processor::CB_opcode_0x2A) );
        cb_extension_map.insert( std::make_pair(43, &Processor::CB_opcode_0x2B) );
        cb_extension_map.insert( std::make_pair(44, &Processor::CB_opcode_0x2C) );
        cb_extension_map.insert( std::make_pair(45, &Processor::CB_opcode_0x2D) );
        cb_extension_map.insert( std::make_pair(46, &Processor::CB_opcode_0x2E) );
        cb_extension_map.insert( std::make_pair(47, &Processor::CB_opcode_0x2F) );

        cb_extension_map.insert( std::make_pair(48, &Processor::CB_opcode_0x30) );
        cb_extension_map.insert( std::make_pair(49, &Processor::CB_opcode_0x31) );
        cb_extension_map.insert( std::make_pair(50, &Processor::CB_opcode_0x32) );
        cb_extension_map.insert( std::make_pair(51, &Processor::CB_opcode_0x33) );
        cb_extension_map.insert( std::make_pair(52, &Processor::CB_opcode_0x34) );
        cb_extension_map.insert( std::make_pair(53, &Processor::CB_opcode_0x35) );
        cb_extension_map.insert( std::make_pair(54, &Processor::CB_opcode_0x36) );
        cb_extension_map.insert( std::make_pair(55, &Processor::CB_opcode_0x37) );
        cb_extension_map.insert( std::make_pair(56, &Processor::CB_opcode_0x38) );
        cb_extension_map.insert( std::make_pair(57, &Processor::CB_opcode_0x39) );
        cb_extension_map.insert( std::make_pair(58, &Processor::CB_opcode_0x3A) );
        cb_extension_map.insert( std::make_pair(59, &Processor::CB_opcode_0x3B) );
        cb_extension_map.insert( std::make_pair(60, &Processor::CB_opcode_0x3C) );
        cb_extension_map.insert( std::make_pair(61, &Processor::CB_opcode_0x3D) );
        cb_extension_map.insert( std::make_pair(62, &Processor::CB_opcode_0x3E) );
        cb_extension_map.insert( std::make_pair(63, &Processor::CB_opcode_0x3F) );

        cb_extension_map.insert( std::make_pair(64, &Processor::CB_opcode_0x40) );
        cb_extension_map.insert( std::make_pair(65, &Processor::CB_opcode_0x41) );
        cb_extension_map.insert( std::make_pair(66, &Processor::CB_opcode_0x42) );
        cb_extension_map.insert( std::make_pair(67, &Processor::CB_opcode_0x43) );
        cb_extension_map.insert( std::make_pair(68, &Processor::CB_opcode_0x44) );
        cb_extension_map.insert( std::make_pair(69, &Processor::CB_opcode_0x45) );
        cb_extension_map.insert( std::make_pair(70, &Processor::CB_opcode_0x46) );
        cb_extension_map.insert( std::make_pair(71, &Processor::CB_opcode_0x47) );
        cb_extension_map.insert( std::make_pair(72, &Processor::CB_opcode_0x48) );
        cb_extension_map.insert( std::make_pair(73, &Processor::CB_opcode_0x49) );
        cb_extension_map.insert( std::make_pair(74, &Processor::CB_opcode_0x4A) );
        cb_extension_map.insert( std::make_pair(75, &Processor::CB_opcode_0x4B) );
        cb_extension_map.insert( std::make_pair(76, &Processor::CB_opcode_0x4C) );
        cb_extension_map.insert( std::make_pair(77, &Processor::CB_opcode_0x4D) );
        cb_extension_map.insert( std::make_pair(78, &Processor::CB_opcode_0x4E) );
        cb_extension_map.insert( std::make_pair(79, &Processor::CB_opcode_0x4F) );

        cb_extension_map.insert( std::make_pair(80, &Processor::CB_opcode_0x50) );
        cb_extension_map.insert( std::make_pair(81, &Processor::CB_opcode_0x51) );
        cb_extension_map.insert( std::make_pair(82, &Processor::CB_opcode_0x52) );
        cb_extension_map.insert( std::make_pair(83, &Processor::CB_opcode_0x53) );
        cb_extension_map.insert( std::make_pair(84, &Processor::CB_opcode_0x54) );
        cb_extension_map.insert( std::make_pair(85, &Processor::CB_opcode_0x55) );
        cb_extension_map.insert( std::make_pair(86, &Processor::CB_opcode_0x56) );
        cb_extension_map.insert( std::make_pair(87, &Processor::CB_opcode_0x57) );
        cb_extension_map.insert( std::make_pair(88, &Processor::CB_opcode_0x58) );
        cb_extension_map.insert( std::make_pair(89, &Processor::CB_opcode_0x59) );
        cb_extension_map.insert( std::make_pair(90, &Processor::CB_opcode_0x5A) );
        cb_extension_map.insert( std::make_pair(91, &Processor::CB_opcode_0x5B) );
        cb_extension_map.insert( std::make_pair(92, &Processor::CB_opcode_0x5C) );
        cb_extension_map.insert( std::make_pair(93, &Processor::CB_opcode_0x5D) );
        cb_extension_map.insert( std::make_pair(94, &Processor::CB_opcode_0x5E) );
        cb_extension_map.insert( std::make_pair(95, &Processor::CB_opcode_0x5F) );

        cb_extension_map.insert( std::make_pair(96, &Processor::CB_opcode_0x60) );
        cb_extension_map.insert( std::make_pair(97, &Processor::CB_opcode_0x61) );
        cb_extension_map.insert( std::make_pair(98, &Processor::CB_opcode_0x62) );
        cb_extension_map.insert( std::make_pair(99, &Processor::CB_opcode_0x63) );
        cb_extension_map.insert( std::make_pair(100, &Processor::CB_opcode_0x64) );
        cb_extension_map.insert( std::make_pair(101, &Processor::CB_opcode_0x65) );
        cb_extension_map.insert( std::make_pair(102, &Processor::CB_opcode_0x66) );
        cb_extension_map.insert( std::make_pair(103, &Processor::CB_opcode_0x67) );
        cb_extension_map.insert( std::make_pair(104, &Processor::CB_opcode_0x68) );
        cb_extension_map.insert( std::make_pair(105, &Processor::CB_opcode_0x69) );
        cb_extension_map.insert( std::make_pair(106, &Processor::CB_opcode_0x6A) );
        cb_extension_map.insert( std::make_pair(107, &Processor::CB_opcode_0x6B) );
        cb_extension_map.insert( std::make_pair(108, &Processor::CB_opcode_0x6C) );
        cb_extension_map.insert( std::make_pair(109, &Processor::CB_opcode_0x6D) );
        cb_extension_map.insert( std::make_pair(110, &Processor::CB_opcode_0x6E) );
        cb_extension_map.insert( std::make_pair(111, &Processor::CB_opcode_0x6F) );

        cb_extension_map.insert( std::make_pair(112, &Processor::CB_opcode_0x70) );
        cb_extension_map.insert( std::make_pair(113, &Processor::CB_opcode_0x71) );
        cb_extension_map.insert( std::make_pair(114, &Processor::CB_opcode_0x72) );
        cb_extension_map.insert( std::make_pair(115, &Processor::CB_opcode_0x73) );
        cb_extension_map.insert( std::make_pair(116, &Processor::CB_opcode_0x74) );
        cb_extension_map.insert( std::make_pair(117, &Processor::CB_opcode_0x75) );
        cb_extension_map.insert( std::make_pair(118, &Processor::CB_opcode_0x76) );
        cb_extension_map.insert( std::make_pair(119, &Processor::CB_opcode_0x77) );
        cb_extension_map.insert( std::make_pair(120, &Processor::CB_opcode_0x78) );
        cb_extension_map.insert( std::make_pair(121, &Processor::CB_opcode_0x79) );
        cb_extension_map.insert( std::make_pair(122, &Processor::CB_opcode_0x7A) );
        cb_extension_map.insert( std::make_pair(123, &Processor::CB_opcode_0x7B) );
        cb_extension_map.insert( std::make_pair(124, &Processor::CB_opcode_0x7C) );
        cb_extension_map.insert( std::make_pair(125, &Processor::CB_opcode_0x7D) );
        cb_extension_map.insert( std::make_pair(126, &Processor::CB_opcode_0x7E) );
        cb_extension_map.insert( std::make_pair(127, &Processor::CB_opcode_0x7F) );

        cb_extension_map.insert( std::make_pair(128, &Processor::CB_opcode_0x80) );
        cb_extension_map.insert( std::make_pair(129, &Processor::CB_opcode_0x81) );
        cb_extension_map.insert( std::make_pair(130, &Processor::CB_opcode_0x82) );
        cb_extension_map.insert( std::make_pair(131, &Processor::CB_opcode_0x83) );
        cb_extension_map.insert( std::make_pair(132, &Processor::CB_opcode_0x84) );
        cb_extension_map.insert( std::make_pair(133, &Processor::CB_opcode_0x85) );
        cb_extension_map.insert( std::make_pair(134, &Processor::CB_opcode_0x86) );
        cb_extension_map.insert( std::make_pair(135, &Processor::CB_opcode_0x87) );
        cb_extension_map.insert( std::make_pair(136, &Processor::CB_opcode_0x88) );
        cb_extension_map.insert( std::make_pair(137, &Processor::CB_opcode_0x89) );
        cb_extension_map.insert( std::make_pair(138, &Processor::CB_opcode_0x8A) );
        cb_extension_map.insert( std::make_pair(139, &Processor::CB_opcode_0x8B) );
        cb_extension_map.insert( std::make_pair(140, &Processor::CB_opcode_0x8C) );
        cb_extension_map.insert( std::make_pair(141, &Processor::CB_opcode_0x8D) );
        cb_extension_map.insert( std::make_pair(142, &Processor::CB_opcode_0x8E) );
        cb_extension_map.insert( std::make_pair(143, &Processor::CB_opcode_0x8F) );

        cb_extension_map.insert( std::make_pair(144, &Processor::CB_opcode_0x90) );
        cb_extension_map.insert( std::make_pair(145, &Processor::CB_opcode_0x91) );
        cb_extension_map.insert( std::make_pair(146, &Processor::CB_opcode_0x92) );
        cb_extension_map.insert( std::make_pair(147, &Processor::CB_opcode_0x93) );
        cb_extension_map.insert( std::make_pair(148, &Processor::CB_opcode_0x94) );
        cb_extension_map.insert( std::make_pair(149, &Processor::CB_opcode_0x95) );
        cb_extension_map.insert( std::make_pair(150, &Processor::CB_opcode_0x96) );
        cb_extension_map.insert( std::make_pair(151, &Processor::CB_opcode_0x97) );
        cb_extension_map.insert( std::make_pair(152, &Processor::CB_opcode_0x98) );
        cb_extension_map.insert( std::make_pair(153, &Processor::CB_opcode_0x99) );
        cb_extension_map.insert( std::make_pair(154, &Processor::CB_opcode_0x9A) );
        cb_extension_map.insert( std::make_pair(155, &Processor::CB_opcode_0x9B) );
        cb_extension_map.insert( std::make_pair(156, &Processor::CB_opcode_0x9C) );
        cb_extension_map.insert( std::make_pair(157, &Processor::CB_opcode_0x9D) );
        cb_extension_map.insert( std::make_pair(158, &Processor::CB_opcode_0x9E) );
        cb_extension_map.insert( std::make_pair(159, &Processor::CB_opcode_0x9F) );

        cb_extension_map.insert( std::make_pair(160, &Processor::CB_opcode_0xA0) );
        cb_extension_map.insert( std::make_pair(161, &Processor::CB_opcode_0xA1) );
        cb_extension_map.insert( std::make_pair(162, &Processor::CB_opcode_0xA2) );
        cb_extension_map.insert( std::make_pair(163, &Processor::CB_opcode_0xA3) );
        cb_extension_map.insert( std::make_pair(164, &Processor::CB_opcode_0xA4) );
        cb_extension_map.insert( std::make_pair(165, &Processor::CB_opcode_0xA5) );
        cb_extension_map.insert( std::make_pair(166, &Processor::CB_opcode_0xA6) );
        cb_extension_map.insert( std::make_pair(167, &Processor::CB_opcode_0xA7) );
        cb_extension_map.insert( std::make_pair(168, &Processor::CB_opcode_0xA8) );
        cb_extension_map.insert( std::make_pair(169, &Processor::CB_opcode_0xA9) );
        cb_extension_map.insert( std::make_pair(170, &Processor::CB_opcode_0xAA) );
        cb_extension_map.insert( std::make_pair(171, &Processor::CB_opcode_0xAB) );
        cb_extension_map.insert( std::make_pair(172, &Processor::CB_opcode_0xAC) );
        cb_extension_map.insert( std::make_pair(173, &Processor::CB_opcode_0xAD) );
        cb_extension_map.insert( std::make_pair(174, &Processor::CB_opcode_0xAE) );
        cb_extension_map.insert( std::make_pair(175, &Processor::CB_opcode_0xAF) );

        cb_extension_map.insert( std::make_pair(176, &Processor::CB_opcode_0xB0) );
        cb_extension_map.insert( std::make_pair(177, &Processor::CB_opcode_0xB1) );
        cb_extension_map.insert( std::make_pair(178, &Processor::CB_opcode_0xB2) );
        cb_extension_map.insert( std::make_pair(179, &Processor::CB_opcode_0xB3) );
        cb_extension_map.insert( std::make_pair(180, &Processor::CB_opcode_0xB4) );
        cb_extension_map.insert( std::make_pair(181, &Processor::CB_opcode_0xB5) );
        cb_extension_map.insert( std::make_pair(182, &Processor::CB_opcode_0xB6) );
        cb_extension_map.insert( std::make_pair(183, &Processor::CB_opcode_0xB7) );
        cb_extension_map.insert( std::make_pair(184, &Processor::CB_opcode_0xB8) );
        cb_extension_map.insert( std::make_pair(185, &Processor::CB_opcode_0xB9) );
        cb_extension_map.insert( std::make_pair(186, &Processor::CB_opcode_0xBA) );
        cb_extension_map.insert( std::make_pair(187, &Processor::CB_opcode_0xBB) );
        cb_extension_map.insert( std::make_pair(188, &Processor::CB_opcode_0xBC) );
        cb_extension_map.insert( std::make_pair(189, &Processor::CB_opcode_0xBD) );
        cb_extension_map.insert( std::make_pair(190, &Processor::CB_opcode_0xBE) );
        cb_extension_map.insert( std::make_pair(191, &Processor::CB_opcode_0xBF) );

        cb_extension_map.insert( std::make_pair(192, &Processor::CB_opcode_0xC0) );
        cb_extension_map.insert( std::make_pair(193, &Processor::CB_opcode_0xC1) );
        cb_extension_map.insert( std::make_pair(194, &Processor::CB_opcode_0xC2) );
        cb_extension_map.insert( std::make_pair(195, &Processor::CB_opcode_0xC3) );
        cb_extension_map.insert( std::make_pair(196, &Processor::CB_opcode_0xC4) );
        cb_extension_map.insert( std::make_pair(197, &Processor::CB_opcode_0xC5) );
        cb_extension_map.insert( std::make_pair(198, &Processor::CB_opcode_0xC6) );
        cb_extension_map.insert( std::make_pair(199, &Processor::CB_opcode_0xC7) );
        cb_extension_map.insert( std::make_pair(200, &Processor::CB_opcode_0xC8) );
        cb_extension_map.insert( std::make_pair(201, &Processor::CB_opcode_0xC9) );
        cb_extension_map.insert( std::make_pair(202, &Processor::CB_opcode_0xCA) );
        cb_extension_map.insert( std::make_pair(203, &Processor::CB_opcode_0xCB) );
        cb_extension_map.insert( std::make_pair(204, &Processor::CB_opcode_0xCC) );
        cb_extension_map.insert( std::make_pair(205, &Processor::CB_opcode_0xCD) );
        cb_extension_map.insert( std::make_pair(206, &Processor::CB_opcode_0xCE) );
        cb_extension_map.insert( std::make_pair(207, &Processor::CB_opcode_0xCF) );

        cb_extension_map.insert( std::make_pair(208, &Processor::CB_opcode_0xD0) );
        cb_extension_map.insert( std::make_pair(209, &Processor::CB_opcode_0xD1) );
        cb_extension_map.insert( std::make_pair(210, &Processor::CB_opcode_0xD2) );
        cb_extension_map.insert( std::make_pair(211, &Processor::CB_opcode_0xD3) );
        cb_extension_map.insert( std::make_pair(212, &Processor::CB_opcode_0xD4) );
        cb_extension_map.insert( std::make_pair(213, &Processor::CB_opcode_0xD5) );
        cb_extension_map.insert( std::make_pair(214, &Processor::CB_opcode_0xD6) );
        cb_extension_map.insert( std::make_pair(215, &Processor::CB_opcode_0xD7) );
        cb_extension_map.insert( std::make_pair(216, &Processor::CB_opcode_0xD8) );
        cb_extension_map.insert( std::make_pair(217, &Processor::CB_opcode_0xD9) );
        cb_extension_map.insert( std::make_pair(218, &Processor::CB_opcode_0xDA) );
        cb_extension_map.insert( std::make_pair(219, &Processor::CB_opcode_0xDB) );
        cb_extension_map.insert( std::make_pair(220, &Processor::CB_opcode_0xDC) );
        cb_extension_map.insert( std::make_pair(221, &Processor::CB_opcode_0xDD) );
        cb_extension_map.insert( std::make_pair(222, &Processor::CB_opcode_0xDE) );
        cb_extension_map.insert( std::make_pair(223, &Processor::CB_opcode_0xDF) );

        cb_extension_map.insert( std::make_pair(224, &Processor::CB_opcode_0xE0) );
        cb_extension_map.insert( std::make_pair(225, &Processor::CB_opcode_0xE1) );
        cb_extension_map.insert( std::make_pair(226, &Processor::CB_opcode_0xE2) );
        cb_extension_map.insert( std::make_pair(227, &Processor::CB_opcode_0xE3) );
        cb_extension_map.insert( std::make_pair(228, &Processor::CB_opcode_0xE4) );
        cb_extension_map.insert( std::make_pair(229, &Processor::CB_opcode_0xE5) );
        cb_extension_map.insert( std::make_pair(230, &Processor::CB_opcode_0xE6) );
        cb_extension_map.insert( std::make_pair(231, &Processor::CB_opcode_0xE7) );
        cb_extension_map.insert( std::make_pair(232, &Processor::CB_opcode_0xE8) );
        cb_extension_map.insert( std::make_pair(233, &Processor::CB_opcode_0xE9) );
        cb_extension_map.insert( std::make_pair(234, &Processor::CB_opcode_0xEA) );
        cb_extension_map.insert( std::make_pair(235, &Processor::CB_opcode_0xEB) );
        cb_extension_map.insert( std::make_pair(236, &Processor::CB_opcode_0xEC) );
        cb_extension_map.insert( std::make_pair(237, &Processor::CB_opcode_0xED) );
        cb_extension_map.insert( std::make_pair(238, &Processor::CB_opcode_0xEE) );
        cb_extension_map.insert( std::make_pair(239, &Processor::CB_opcode_0xEF) );

        cb_extension_map.insert( std::make_pair(240, &Processor::CB_opcode_0xF0) );
        cb_extension_map.insert( std::make_pair(241, &Processor::CB_opcode_0xF1) );
        cb_extension_map.insert( std::make_pair(242, &Processor::CB_opcode_0xF2) );
        cb_extension_map.insert( std::make_pair(243, &Processor::CB_opcode_0xF3) );
        cb_extension_map.insert( std::make_pair(244, &Processor::CB_opcode_0xF4) );
        cb_extension_map.insert( std::make_pair(245, &Processor::CB_opcode_0xF5) );
        cb_extension_map.insert( std::make_pair(246, &Processor::CB_opcode_0xF6) );
        cb_extension_map.insert( std::make_pair(247, &Processor::CB_opcode_0xF7) );
        cb_extension_map.insert( std::make_pair(248, &Processor::CB_opcode_0xF8) );
        cb_extension_map.insert( std::make_pair(249, &Processor::CB_opcode_0xF9) );
        cb_extension_map.insert( std::make_pair(250, &Processor::CB_opcode_0xFA) );
        cb_extension_map.insert( std::make_pair(251, &Processor::CB_opcode_0xFB) );
        cb_extension_map.insert( std::make_pair(252, &Processor::CB_opcode_0xFC) );
        cb_extension_map.insert( std::make_pair(253, &Processor::CB_opcode_0xFD) );
        cb_extension_map.insert( std::make_pair(254, &Processor::CB_opcode_0xFE) );
        cb_extension_map.insert( std::make_pair(255, &Processor::CB_opcode_0xFF) );

}
