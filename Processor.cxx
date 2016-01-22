#include "Processor.h"

// STARTUP STATE (Static Member Initialization)
bool Processor::halted = false;
bool Processor::interrupt_enable = true;
bool Processor::stopped = false;

Register Processor::AF;
Register Processor::BC;
Register Processor::DE;
Register Processor::HL;
Register Processor::SP;
Register Processor::PC;

CPU_Stack Processor::call_stack(&SP);

bool Processor::zeroFlag;
bool Processor::addSubFlag;
bool Processor::halfCarryFlag;
bool Processor::carryFlag;

Memory* Processor::main_memory;
VideoMemory* Processor::video_memory;

// DEFAULT MEMBERS
Processor::Processor(Memory* RAM) {
	main_memory = RAM;
	opcode_map_populate();
}

Processor::~Processor() {

}


////////////////////// OPCODE BLOCK 0x0* //////////////////////


// nop
void Processor::opcode_0x00() {}

// ld bc, **
void Processor::opcode_0x01() {
	BC.setLoByte( (*main_memory)[PC.getValue()] );
	++PC;
	BC.setHiByte( (*main_memory)[PC.getValue()] );
	++PC;
}

// ld (bc), a
void Processor::opcode_0x02() {
	main_memory->putByte(AF.getHiByte(), BC.getValue());	
}

// inc bc
void Processor::opcode_0x03() {
	++BC;	
}

// inc b
void Processor::opcode_0x04() {
	BC.IncrementHi();	
}

// dec b
void Processor::opcode_0x05() {
	BC.DecrementHi();
}

// ld b, *
void Processor::opcode_0x06() {
	BC.setHiByte( (*main_memory)[PC.getValue()] );
	++PC;
}

// rlca
void Processor::opcode_0x07() {
	uint8_t flag = AF.RotateLeftHi();
	carryFlag = (bool) flag;	
}

// ld **, sp
void Processor::opcode_0x08() {
	uint8_t loByte = (*main_memory)[PC.getValue()];
	++PC;
	uint8_t hiByte = (*main_memory)[PC.getValue()];
	++PC;
	uint16_t writeAddr = (uint16_t)(loByte) + (uint16_t)(hiByte << 8);
	main_memory->putByte(SP.getLoByte(), writeAddr);
	main_memory->putByte(SP.getHiByte(), writeAddr + 1);
}

// add hl, bc
void Processor::opcode_0x09() {
	uint16_t sum = BC.getValue() + HL.getValue();
        HL.setValue(sum);
}

// ld a,(bc) 
void Processor::opcode_0x0A() {
        AF.setHiByte( (*main_memory)[BC.getValue()] );	
}

// dec bc
void Processor::opcode_0x0B() {
	--BC;
}

// inc c
void Processor::opcode_0x0C() {
	BC.IncrementLo();
}

// dec c
void Processor::opcode_0x0D() {
	BC.DecrementLo();
}

// ld c, *
void Processor::opcode_0x0E() {
        BC.setLoByte( (*main_memory)[PC.getValue()] );
        ++PC;	
}

// rrca
void Processor::opcode_0x0F() {
	uint8_t flag = AF.RotateRightHi();
	carryFlag = (bool)flag;	
}


////////////////////// OPCODE BLOCK 0x1* //////////////////////


// stop
void Processor::opcode_0x10() {
	stopped = true;
}

// ld de, **
void Processor::opcode_0x11() {
        DE.setLoByte( (*main_memory)[PC.getValue()] );
        ++PC;
        DE.setHiByte( (*main_memory)[PC.getValue()] );
        ++PC;
}

// ld de, a
void Processor::opcode_0x12() {
        main_memory->putByte(AF.getHiByte(), BC.getValue());
}

// inc de
void Processor::opcode_0x13() {
	++DE;
}

// inc d
void Processor::opcode_0x14() {
	DE.IncrementHi();
}

// dec d
void Processor::opcode_0x15() {
	DE.DecrementHi();
}

// ld d, *
void Processor::opcode_0x16() {
        DE.setHiByte( (*main_memory)[PC.getValue()] );
        ++PC;
}

// rla
void Processor::opcode_0x17() {
	uint8_t oldCarry = (uint8_t)carryFlag;
	uint8_t operand = AF.getHiByte();
	uint8_t newCarry = operand & (1 << 7);

	operand = (operand << 1) | (oldCarry);
	carryFlag = (bool) newCarry;
	AF.setHiByte(operand);
}

// jr
void Processor::opcode_0x18() {
	uint16_t startAddr = PC.getValue() - 1;
	int8_t jump = (*main_memory)[PC.getValue()];
        uint16_t newAddr = (uint16_t)((int16_t)startAddr + (int16_t)jump);
        PC.setValue(newAddr);
}

// add hl, de
void Processor::opcode_0x19() {
        uint16_t sum = DE.getValue() + HL.getValue();
        HL.setValue(sum);
}

// ld a, (de)
void Processor::opcode_0x1A() {
        AF.setHiByte( (*main_memory)[BC.getValue()] );
}

// dec de
void Processor::opcode_0x1B() {
	--DE;
}

// inc e
void Processor::opcode_0x1C() {
	DE.IncrementLo();
}

// dec e
void Processor::opcode_0x1D() {
	DE.DecrementLo();
}

// ld e, *
void Processor::opcode_0x1E() {
        DE.setLoByte( (*main_memory)[PC.getValue()] );
        ++PC;
}

// rra
void Processor::opcode_0x1F() {
        uint8_t oldCarry = (uint8_t)carryFlag;
        uint8_t operand = AF.getHiByte();
        uint8_t newCarry = operand & 1;

        operand = (operand >> 1) | (oldCarry << 7);
        carryFlag = (bool) newCarry;
        AF.setHiByte(operand);			
}


////////////////////// OPCODE BLOCK 0x2* //////////////////////


// jr nz, *
void Processor::opcode_0x20() {
	uint16_t startAddr = PC.getValue() - 1;
	if(zeroFlag == false) {
		int8_t jump = (*main_memory)[PC.getValue()];
		uint16_t newAddr = (uint16_t)((int16_t)startAddr + (int16_t)jump);
		PC.setValue(newAddr);
	} else {
		++PC;
	}
}

// ld hl, **
void Processor::opcode_0x21() {
        HL.setLoByte( (*main_memory)[PC.getValue()] );
        ++PC;
        HL.setHiByte( (*main_memory)[PC.getValue()] );
        ++PC;	
}

// ldi (hl), a
void Processor::opcode_0x22() {
	uint16_t address = HL.getValue();
	main_memory->putByte(AF.getHiByte(), (int)address);	
	++HL;
}

// inc hl
void Processor::opcode_0x23() {
	++HL;
}

// inc h
void Processor::opcode_0x24() {
	HL.IncrementHi();
}

// dec h
void Processor::opcode_0x25() {
	HL.DecrementHi();
}

// ld h, *
void Processor::opcode_0x26() {
        HL.setHiByte( (*main_memory)[PC.getValue()] );
        ++PC;	
}

// daa
void Processor::opcode_0x27() {
	uint8_t lower_nibble = AF.getHiByte() & 0x0F;
	uint8_t higher_nibble = (AF.getHiByte() & 0xF0) >> 4;

	if(lower_nibble > 9 || halfCarryFlag == true) {
		lower_nibble = (lower_nibble + 6) & 0x0F;
		carryFlag = true;
	}		

        if(carryFlag) {
                higher_nibble += 1;
        }

	if(higher_nibble > 9) {
		higher_nibble = (higher_nibble + 6) & 0x0F;
	}

	AF.setHiByte(lower_nibble + (higher_nibble << 4));
}

// jr z, *
void Processor::opcode_0x28() {
        uint16_t startAddr = PC.getValue() - 1;
        if(zeroFlag == true) {
                int8_t jump = (*main_memory)[PC.getValue()];
                uint16_t newAddr = (uint16_t)((int16_t)startAddr + (int16_t)jump);
                PC.setValue(newAddr);
        } else {
                ++PC;
        }
}

// add hl, hl
void Processor::opcode_0x29() {
        uint16_t sum = HL.getValue() + HL.getValue();
        HL.setValue(sum);
}

// ldi a, (hl)
void Processor::opcode_0x2A() {
	uint16_t address = HL.getValue();
        AF.setHiByte( (*main_memory)[address] );
	++HL;
}

// dec hl
void Processor::opcode_0x2B() {
	--HL;
}

// inc l
void Processor::opcode_0x2C() {
	HL.IncrementLo();
}
// dec l
void Processor::opcode_0x2D() {
	HL.DecrementLo();
}

// ld l, *
void Processor::opcode_0x2E() {
        HL.setLoByte( (*main_memory)[PC.getValue()] );
        ++PC;	
}

// cpl
void Processor::opcode_0x2F() {
	uint8_t value = AF.getHiByte();
	AF.setHiByte(~value);
}


////////////////////// OPCODE BLOCK 0x3* //////////////////////


// jr nc, *
void Processor::opcode_0x30() {
        uint16_t startAddr = PC.getValue() - 1;
        if(carryFlag == false) {
                int8_t jump = (*main_memory)[PC.getValue()];
                uint16_t newAddr = (uint16_t)((int16_t)startAddr + (int16_t)jump);
                PC.setValue(newAddr);
        } else {
                ++PC;
        }
}

// ld sp, **
void Processor::opcode_0x31() {
        SP.setLoByte( (*main_memory)[PC.getValue()] );
        ++PC;
        SP.setHiByte( (*main_memory)[PC.getValue()] );
        ++PC;
}

// ldd (hl), a
void Processor::opcode_0x32() {
        uint16_t address = HL.getValue();
        main_memory->putByte(AF.getHiByte(), (int)address);
        --HL;
}

// inc sp
void Processor::opcode_0x33() {
	++SP;
}

// inc (hl)
void Processor::opcode_0x34() {
	uint8_t value = (*main_memory)[HL.getValue()];
	main_memory->putByte(value + 1, HL.getValue()); 
}

// dec (hl)
void Processor::opcode_0x35() {
        uint8_t value = (*main_memory)[HL.getValue()];
        main_memory->putByte(value - 1, HL.getValue());
}

// ld (hl), *
void Processor::opcode_0x36() {
	uint8_t value = (*main_memory)[PC.getValue()];
	++PC;
	main_memory->putByte(value, HL.getValue());
}

// scf
void Processor::opcode_0x37() {
	carryFlag = true;	
}

// jr c, *
void Processor::opcode_0x38() {
        uint16_t startAddr = PC.getValue() - 1;
        if(carryFlag == true) {
                int8_t jump = (*main_memory)[PC.getValue()];
                uint16_t newAddr = (uint16_t)((int16_t)startAddr + (int16_t)jump);
                PC.setValue(newAddr);
        } else {
                ++PC;
        }
}

// add hl, sp
void Processor::opcode_0x39() {
        uint16_t sum = SP.getValue() + HL.getValue();
        HL.setValue(sum);
}

// ldd a, (hl)
void Processor::opcode_0x3A() {
        uint16_t address = HL.getValue();
        AF.setHiByte( (*main_memory)[address] );
        --HL;
}

// dec sp
void Processor::opcode_0x3B() {
	--SP;
}

// inc a
void Processor::opcode_0x3C() {
	AF.IncrementHi();
}

// dec a
void Processor::opcode_0x3D() {
	AF.DecrementHi();
}

// ld a, *
void Processor::opcode_0x3E() {
        AF.setHiByte( (*main_memory)[PC.getValue()] );
        ++PC;
}

// ccf
void Processor::opcode_0x3F() {
	carryFlag = !carryFlag;	
}


////////////////////// OPCODE BLOCK 0x4* //////////////////////


// ld b, b
void Processor::opcode_0x40() {}

// ld b, c 
void Processor::opcode_0x41() {
	BC.setHiByte(BC.getLoByte());
}

// ld b, d
void Processor::opcode_0x42() {
	BC.setHiByte(DE.getHiByte());
}

// ld b, e
void Processor::opcode_0x43() {
	BC.setHiByte(DE.getLoByte());
}

// ld b, h
void Processor::opcode_0x44() {
	BC.setHiByte(HL.getHiByte());
}

// ld b, l
void Processor::opcode_0x45() {
	BC.setHiByte(HL.getLoByte());
}

// ld b, (hl)
void Processor::opcode_0x46() {
	uint8_t value = (*main_memory)[HL.getValue()];
	BC.setHiByte(value);	
}

// ld b, a
void Processor::opcode_0x47() {
	BC.setHiByte(AF.getHiByte());
}

// ld c, b
void Processor::opcode_0x48() {
	BC.setLoByte(BC.getHiByte());
}

// ld c, c
void Processor::opcode_0x49() {}

// ld c, d
void Processor::opcode_0x4A() {
        BC.setLoByte(DE.getHiByte());
}

// ld c, e
void Processor::opcode_0x4B() {
        BC.setLoByte(DE.getLoByte());
}

// ld c, h
void Processor::opcode_0x4C() {
        BC.setLoByte(HL.getHiByte());
}

// ld c, l
void Processor::opcode_0x4D() {
        BC.setLoByte(HL.getLoByte());
}

// ld c, (hl)
void Processor::opcode_0x4E() {
        uint8_t value = (*main_memory)[HL.getValue()];
        BC.setLoByte(value);
}

// ld c, a
void Processor::opcode_0x4F() {
        BC.setLoByte(AF.getHiByte());
}


////////////////////// OPCODE BLOCK 0x5* //////////////////////


// ld d, b
void Processor::opcode_0x50() {
	DE.setHiByte(BC.getHiByte());
}

// ld d, c
void Processor::opcode_0x51() {
        DE.setHiByte(BC.getLoByte());
}

// ld d, d
void Processor::opcode_0x52() {}

// ld d, e
void Processor::opcode_0x53() {
        DE.setHiByte(DE.getLoByte());
}

// ld d, h
void Processor::opcode_0x54() {
        DE.setHiByte(HL.getHiByte());
}

// ld d, l
void Processor::opcode_0x55() {
        DE.setHiByte(HL.getLoByte());
}

// ld d, (hl)
void Processor::opcode_0x56() {
        uint8_t value = (*main_memory)[HL.getValue()];
        DE.setHiByte(value);	
}

// ld d, a
void Processor::opcode_0x57() {
        DE.setHiByte(AF.getHiByte());
}

// ld e, b
void Processor::opcode_0x58() {
        DE.setLoByte(BC.getHiByte());
}

// ld e, c
void Processor::opcode_0x59() {
        DE.setLoByte(BC.getLoByte());
}

// ld e, d
void Processor::opcode_0x5A() {
        DE.setLoByte(DE.getHiByte());
}

// ld e, e
void Processor::opcode_0x5B() {}

// ld e, h
void Processor::opcode_0x5C() {
        DE.setLoByte(HL.getHiByte());
}

// ld e, l
void Processor::opcode_0x5D() {
        DE.setLoByte(HL.getLoByte());
}

// ld e, (hl)
void Processor::opcode_0x5E() {
        uint8_t value = (*main_memory)[HL.getValue()];
        DE.setLoByte(value);
}

// ld e, a
void Processor::opcode_0x5F() {
        DE.setLoByte(AF.getHiByte());
}


////////////////////// OPCODE BLOCK 0x6* //////////////////////


// ld h, b
void Processor::opcode_0x60() {
        HL.setHiByte(BC.getHiByte());
}

// ld h, c
void Processor::opcode_0x61() {
        HL.setHiByte(BC.getLoByte());
}

// ld h, d
void Processor::opcode_0x62() {
        HL.setHiByte(DE.getHiByte());
}

// ld h, e
void Processor::opcode_0x63() {
        HL.setHiByte(DE.getLoByte());
}

// ld h, h
void Processor::opcode_0x64() {}

// ld h, l
void Processor::opcode_0x65() {
        HL.setHiByte(HL.getLoByte());
}

// ld h, (hl)
void Processor::opcode_0x66() {
        uint8_t value = (*main_memory)[HL.getValue()];
        HL.setHiByte(value);
}

// ld h, a
void Processor::opcode_0x67() {
	HL.setHiByte(AF.getHiByte());
}

// ld l, b
void Processor::opcode_0x68() {
        HL.setLoByte(BC.getHiByte());
}

// ld l, c
void Processor::opcode_0x69() {
        HL.setLoByte(BC.getLoByte());
}

// ld l, d
void Processor::opcode_0x6A() {
        HL.setLoByte(DE.getHiByte());
}

// ld l, e
void Processor::opcode_0x6B() {
        HL.setLoByte(DE.getLoByte());
}

// ld l, h
void Processor::opcode_0x6C() {
        HL.setLoByte(HL.getHiByte());
}

// ld l, l
void Processor::opcode_0x6D() {}

// ld l, (hl)
void Processor::opcode_0x6E() {
        uint8_t value = (*main_memory)[HL.getValue()];
        HL.setLoByte(value);
}

// ld l, a
void Processor::opcode_0x6F() {
        HL.setLoByte(AF.getHiByte());
}


////////////////////// OPCODE BLOCK 0x7* //////////////////////


// ld (hl), b
void Processor::opcode_0x70() {
	uint16_t addr = HL.getValue();
	main_memory->putByte(BC.getHiByte(), (int)addr);
}

// ld (hl), c
void Processor::opcode_0x71() {
        uint16_t addr = HL.getValue();
        main_memory->putByte(BC.getLoByte(), (int)addr);
}

// ld (hl), d
void Processor::opcode_0x72() {
        uint16_t addr = HL.getValue();
        main_memory->putByte(DE.getHiByte(), (int)addr);
}

// ld (hl), e
void Processor::opcode_0x73() {
        uint16_t addr = HL.getValue();
        main_memory->putByte(DE.getLoByte(), (int)addr);
}

// ld (hl), h
void Processor::opcode_0x74() {
        uint16_t addr = HL.getValue();
        main_memory->putByte(HL.getHiByte(), (int)addr);
}

// ld (hl), l
void Processor::opcode_0x75() {
        uint16_t addr = HL.getValue();
        main_memory->putByte(HL.getLoByte(), (int)addr);
}

// halt
void Processor::opcode_0x76() {
	halted = true;
}

// ld (hl), a
void Processor::opcode_0x77() {
        uint16_t addr = HL.getValue();
        main_memory->putByte(AF.getHiByte(), (int)addr);
}

// ld a, b
void Processor::opcode_0x78() {
        AF.setHiByte(BC.getHiByte());
}

// ld a, c
void Processor::opcode_0x79() {
        AF.setHiByte(BC.getLoByte());
}

// ld a, d
void Processor::opcode_0x7A() {
        AF.setHiByte(DE.getHiByte());
}

// ld a, e
void Processor::opcode_0x7B() {
        AF.setHiByte(DE.getLoByte());
}

// ld a, h
void Processor::opcode_0x7C() {
        AF.setHiByte(HL.getHiByte());
}

// ld a, l
void Processor::opcode_0x7D() {
        AF.setHiByte(HL.getLoByte());
}

// ld a, (hl)
void Processor::opcode_0x7E() {
        uint8_t value = (*main_memory)[HL.getValue()];
        AF.setHiByte(value);
}

// ld a, a
void Processor::opcode_0x7F() {}


////////////////////// OPCODE BLOCK 0x8* //////////////////////


// add a, b 
void Processor::opcode_0x80() {
	uint8_t sum = AF.getHiByte() + BC.getHiByte();
	AF.setHiByte(sum);
}

// add a, c
void Processor::opcode_0x81() {
        uint8_t sum = AF.getHiByte() + BC.getLoByte();
        AF.setHiByte(sum);
}

// add a, d
void Processor::opcode_0x82() {
        uint8_t sum = AF.getHiByte() + DE.getHiByte();
        AF.setHiByte(sum);
}

// add a, e
void Processor::opcode_0x83() {
        uint8_t sum = AF.getHiByte() + DE.getLoByte();
        AF.setHiByte(sum);
}

// add a, h
void Processor::opcode_0x84() {
        uint8_t sum = AF.getHiByte() + HL.getHiByte();
        AF.setHiByte(sum);
}

// add a, l
void Processor::opcode_0x85() {
        uint8_t sum = AF.getHiByte() + HL.getLoByte();
        AF.setHiByte(sum);
}

// add a, (hl)
void Processor::opcode_0x86() {
	uint8_t value = (*main_memory)[HL.getValue()];
	uint8_t sum = AF.getHiByte() + value;
        AF.setHiByte(sum);
}

// add a, a
void Processor::opcode_0x87() {
        uint8_t sum = AF.getHiByte() + AF.getHiByte();
        AF.setHiByte(sum);
}

// adc a, b
void Processor::opcode_0x88() {
	uint8_t sum = AF.getHiByte() + BC.getHiByte() + (int)carryFlag;
        AF.setHiByte(sum);
}

// adc a, c
void Processor::opcode_0x89() {
        uint8_t sum = AF.getHiByte() + BC.getLoByte() + (int)carryFlag;
        AF.setHiByte(sum);
}

// adc a, d
void Processor::opcode_0x8A() {
        uint8_t sum = AF.getHiByte() + DE.getHiByte() + (int)carryFlag;
        AF.setHiByte(sum);
}

// adc a, e
void Processor::opcode_0x8B() {
        uint8_t sum = AF.getHiByte() + DE.getLoByte() + (int)carryFlag;
        AF.setHiByte(sum);
}

// adc a, h
void Processor::opcode_0x8C() {
        uint8_t sum = AF.getHiByte() + HL.getHiByte() + (int)carryFlag;
        AF.setHiByte(sum);
}

// adc a, l
void Processor::opcode_0x8D() {
        uint8_t sum = AF.getHiByte() + HL.getLoByte() + (int)carryFlag;
        AF.setHiByte(sum);
}

// adc a, (hl)
void Processor::opcode_0x8E() {
        uint8_t value = (*main_memory)[HL.getValue()];
        uint8_t sum = AF.getHiByte() + value + (int)carryFlag;
        AF.setHiByte(sum);
}

// adc a, a
void Processor::opcode_0x8F() {
        uint8_t sum = AF.getHiByte() + AF.getHiByte() + (int)carryFlag;
        AF.setHiByte(sum);
}


////////////////////// OPCODE BLOCK 0x9* //////////////////////


// sub b
void Processor::opcode_0x90() {
        uint8_t difference = AF.getHiByte() - BC.getHiByte();
        AF.setHiByte(difference);
}

// sub c
void Processor::opcode_0x91() {
        uint8_t difference = AF.getHiByte() - BC.getLoByte();
        AF.setHiByte(difference);
}

// sub d
void Processor::opcode_0x92() {
        uint8_t difference = AF.getHiByte() - DE.getHiByte();
        AF.setHiByte(difference);
}

// sub e
void Processor::opcode_0x93() {
        uint8_t difference = AF.getHiByte() - DE.getLoByte();
        AF.setHiByte(difference);
}

// sub h
void Processor::opcode_0x94() {
        uint8_t difference = AF.getHiByte() - HL.getHiByte();
        AF.setHiByte(difference);
}

// sub l
void Processor::opcode_0x95() {
        uint8_t difference = AF.getHiByte() - HL.getLoByte();
        AF.setHiByte(difference);
}

// sub (hl)
void Processor::opcode_0x96() {
        uint8_t value = (*main_memory)[HL.getValue()];
        uint8_t difference = AF.getHiByte() - value;
        AF.setHiByte(difference);
}

// sub a
void Processor::opcode_0x97() {
        uint8_t difference = AF.getHiByte() - AF.getHiByte();
        AF.setHiByte(difference);
}

// sbc a, b
void Processor::opcode_0x98() {
        uint8_t difference = AF.getHiByte() - BC.getHiByte() - (int)carryFlag;
        AF.setHiByte(difference);
}

// sbc a, c
void Processor::opcode_0x99() {
        uint8_t difference = AF.getHiByte() - BC.getLoByte() - (int)carryFlag;
        AF.setHiByte(difference);
}

// sbc a, d
void Processor::opcode_0x9A() {
        uint8_t difference = AF.getHiByte() - DE.getHiByte() - (int)carryFlag;
        AF.setHiByte(difference);
}

// sbc a, e
void Processor::opcode_0x9B() {
        uint8_t difference = AF.getHiByte() - DE.getLoByte() - (int)carryFlag;
        AF.setHiByte(difference);
}

// sbc a, h
void Processor::opcode_0x9C() {
        uint8_t difference = AF.getHiByte() - HL.getHiByte() - (int)carryFlag;
        AF.setHiByte(difference);
}

// sbc a, l
void Processor::opcode_0x9D() {
        uint8_t difference = AF.getHiByte() - HL.getHiByte() - (int)carryFlag;
        AF.setHiByte(difference);
}

// sbc a, (hl)
void Processor::opcode_0x9E() {
        uint8_t value = (*main_memory)[HL.getValue()];
        uint8_t sum = AF.getHiByte() - value - (int)carryFlag;
        AF.setHiByte(sum);       
}

// sbc a, a
void Processor::opcode_0x9F() {
        uint8_t difference = AF.getHiByte() - AF.getHiByte() - (int)carryFlag;
        AF.setHiByte(difference);
}


////////////////////// OPCODE BLOCK 0xA* //////////////////////


// and b
void Processor::opcode_0xA0() {
        uint8_t result = AF.getHiByte() & BC.getHiByte();
        AF.setHiByte(result);
}

// and c
void Processor::opcode_0xA1() {
        uint8_t result = AF.getHiByte() & BC.getLoByte();
        AF.setHiByte(result);
}

// and d
void Processor::opcode_0xA2() {
        uint8_t result = AF.getHiByte() & DE.getHiByte();
        AF.setHiByte(result);
}

// and e
void Processor::opcode_0xA3() {
        uint8_t result = AF.getHiByte() & DE.getLoByte();
        AF.setHiByte(result);
}

// and h
void Processor::opcode_0xA4() {
        uint8_t result = AF.getHiByte() & HL.getHiByte();
        AF.setHiByte(result);
}

// and l
void Processor::opcode_0xA5() {
        uint8_t result = AF.getHiByte() & HL.getLoByte();
        AF.setHiByte(result);
}

// and (hl)
void Processor::opcode_0xA6() {
        uint8_t value = (*main_memory)[HL.getValue()];
        uint8_t result = AF.getHiByte() & value;
        AF.setHiByte(result);
}

// and a
void Processor::opcode_0xA7() {
        uint8_t result = AF.getHiByte() & AF.getHiByte();
        AF.setHiByte(result);
}

// xor b
void Processor::opcode_0xA8() {
        uint8_t result = AF.getHiByte() ^ BC.getHiByte();
        AF.setHiByte(result);
}

// xor c
void Processor::opcode_0xA9() {
        uint8_t result = AF.getHiByte() ^ BC.getLoByte();
        AF.setHiByte(result);
}

// xor d
void Processor::opcode_0xAA() {
        uint8_t result = AF.getHiByte() ^ DE.getHiByte();
        AF.setHiByte(result);
}

// xor e
void Processor::opcode_0xAB() {
        uint8_t result = AF.getHiByte() ^ DE.getLoByte();
        AF.setHiByte(result);
}

// xor h
void Processor::opcode_0xAC() {
        uint8_t result = AF.getHiByte() ^ HL.getHiByte();
        AF.setHiByte(result);
}

// xor l
void Processor::opcode_0xAD() {
        uint8_t result = AF.getHiByte() ^ HL.getLoByte();
        AF.setHiByte(result);
}

// xor (hl)
void Processor::opcode_0xAE() {
        uint8_t value = (*main_memory)[HL.getValue()];
        uint8_t result = AF.getHiByte() ^ value;
        AF.setHiByte(result);       
}

// xor a
void Processor::opcode_0xAF() {
        uint8_t result = AF.getHiByte() ^ AF.getHiByte();
        AF.setHiByte(result);
}


////////////////////// OPCODE BLOCK 0xB* //////////////////////


// or b
void Processor::opcode_0xB0() {
        uint8_t result = AF.getHiByte() | BC.getHiByte();
        AF.setHiByte(result);
}

// or c
void Processor::opcode_0xB1() {
        uint8_t result = AF.getHiByte() | BC.getLoByte();
        AF.setHiByte(result);
}

// or d
void Processor::opcode_0xB2() {
        uint8_t result = AF.getHiByte() | DE.getHiByte();
        AF.setHiByte(result);
}

// or e
void Processor::opcode_0xB3() {
        uint8_t result = AF.getHiByte() | DE.getLoByte();
        AF.setHiByte(result);
}

// or h
void Processor::opcode_0xB4() {
        uint8_t result = AF.getHiByte() | HL.getHiByte();
        AF.setHiByte(result);
}

// or l
void Processor::opcode_0xB5() {
        uint8_t result = AF.getHiByte() | HL.getLoByte();
        AF.setHiByte(result);
}

// or (hl)
void Processor::opcode_0xB6() {
        uint8_t value = (*main_memory)[HL.getValue()];
        uint8_t result = AF.getHiByte() | value;
        AF.setHiByte(result);
}

// or a
void Processor::opcode_0xB7() {
        uint8_t result = AF.getHiByte() | AF.getHiByte();
        AF.setHiByte(result);
}

void Processor::opcode_0xB8() {}
void Processor::opcode_0xB9() {}
void Processor::opcode_0xBA() {}
void Processor::opcode_0xBB() {}
void Processor::opcode_0xBC() {}
void Processor::opcode_0xBD() {}
void Processor::opcode_0xBE() {}
void Processor::opcode_0xBF() {}


////////////////////// OPCODE BLOCK 0xC* //////////////////////


// ret nz
void Processor::opcode_0xC0() {
	if(zeroFlag == false) {
		uint16_t value = call_stack.pop();
		PC.setValue(value);	
	}
}

// pop bc
void Processor::opcode_0xC1() {
	uint16_t value = call_stack.pop();
	BC.setValue(value);
}

// jp nz, **
void Processor::opcode_0xC2() {
	if(zeroFlag == false) {
		uint16_t startPC = PC.getValue();
        	PC.setLoByte( (*main_memory)[startPC] );
        	PC.setHiByte( (*main_memory)[startPC+1] );
	} else {
		++PC;
		++PC;
	}
}

// jp, **
void Processor::opcode_0xC3() {
	PC.setLoByte( (*main_memory)[PC.getValue()] );
	++PC;
	PC.setHiByte( (*main_memory)[PC.getValue()] );
	++PC;
}

// call nz, **
void Processor::opcode_0xC4() {
	if(zeroFlag == false) {
		call_stack.push(PC.getValue() + 2);
		uint16_t startPC = PC.getValue();
                PC.setLoByte( (*main_memory)[startPC] );
                PC.setHiByte( (*main_memory)[startPC+1] );
	} else {
		++PC;
		++PC;
	}
}

// push bc
void Processor::opcode_0xC5() {
	call_stack.push(BC.getValue());
}

// add a, *
void Processor::opcode_0xC6() {
	uint8_t immediate = (*main_memory)[PC.getValue()];
	AF.setHiByte(immediate + AF.getHiByte());
}

// rst 00
void Processor::opcode_0xC7() {
	call_stack.push(PC.getValue());
	PC.setValue(0x00);
}

// ret z
void Processor::opcode_0xC8() {
        if(zeroFlag == true) {
                uint16_t value = call_stack.pop();
                PC.setValue(value);
        }
}

// ret
void Processor::opcode_0xC9() {
        uint16_t value = call_stack.pop();
	PC.setValue(value);	
}

// jp z, **
void Processor::opcode_0xCA() {
        if(zeroFlag == true) {
                uint16_t startPC = PC.getValue();
                PC.setLoByte( (*main_memory)[startPC] );
                PC.setHiByte( (*main_memory)[startPC+1] );
        } else {
                ++PC;
                ++PC;
        }
}

// CB INSTRUCTION SET ACCESSOR
void Processor::opcode_0xCB() {}

// call z, **
void Processor::opcode_0xCC() {
        if(zeroFlag == true) {
                uint16_t startPC = PC.getValue();
                PC.setLoByte( (*main_memory)[startPC] );
                PC.setHiByte( (*main_memory)[startPC+1] );
	} else {
                ++PC;
                ++PC;
        }
}

// call **
void Processor::opcode_0xCD() {
        call_stack.push(PC.getValue() + 2);
        uint16_t startPC = PC.getValue();
        PC.setLoByte( (*main_memory)[startPC] );
        PC.setHiByte( (*main_memory)[startPC+1] );
}

// adc a, *
void Processor::opcode_0xCE() {
        uint8_t immediate = (*main_memory)[PC.getValue()];
        AF.setHiByte(immediate + AF.getHiByte() + (int) carryFlag);
}

// rst 08
void Processor::opcode_0xCF() {
        call_stack.push(PC.getValue());
        PC.setValue(0x08);
}


////////////////////// OPCODE BLOCK 0xD* //////////////////////


// ret nc
void Processor::opcode_0xD0() {
        if(carryFlag == false) {
                uint16_t value = call_stack.pop();
                PC.setValue(value);
        }
}

// pop de
void Processor::opcode_0xD1() {
        uint16_t value = call_stack.pop();
        DE.setValue(value);
}

// jp nc, **
void Processor::opcode_0xD2() {
        if(carryFlag == false) {
                uint16_t startPC = PC.getValue();
                PC.setLoByte( (*main_memory)[startPC] );
                PC.setHiByte( (*main_memory)[startPC+1] );
        } else {
                ++PC;
                ++PC;
        }
}

//out (*), a
void Processor::opcode_0xD3() {} // UNUSED 

// call nc, **
void Processor::opcode_0xD4() {
        if(carryFlag == false) {
                call_stack.push(PC.getValue() + 2);
                uint16_t startPC = PC.getValue();
                PC.setLoByte( (*main_memory)[startPC] );
                PC.setHiByte( (*main_memory)[startPC+1] );
        } else {
                ++PC;
                ++PC;
        }
}

// push de
void Processor::opcode_0xD5() {
        call_stack.push(DE.getValue());
}

// sub *
void Processor::opcode_0xD6() {
        uint8_t immediate = (*main_memory)[PC.getValue()];
        AF.setHiByte(AF.getHiByte() - immediate);
}

// rst 10h
void Processor::opcode_0xD7() {
        call_stack.push(PC.getValue());
        PC.setValue(0x10);
}

// ret c
void Processor::opcode_0xD8() {
        if(carryFlag == true) {
                uint16_t value = call_stack.pop();
                PC.setValue(value);
        }
}

// reti
void Processor::opcode_0xD9() {
        uint16_t value = call_stack.pop();
        PC.setValue(value);
	interrupt_enable = true;
}

// jp c, **
void Processor::opcode_0xDA() {
        if(carryFlag == true) {
                call_stack.push(PC.getValue() + 2);
                uint16_t startPC = PC.getValue();
                PC.setLoByte( (*main_memory)[startPC] );
                PC.setHiByte( (*main_memory)[startPC+1] );
        } else {
                ++PC;
                ++PC;
        }
}

// in a, (*)
void Processor::opcode_0xDB() {} // UNUSED 

// call c, *
void Processor::opcode_0xDC() {
        if(carryFlag == true) {
                call_stack.push(PC.getValue() + 2);
                uint16_t startPC = PC.getValue();
                PC.setLoByte( (*main_memory)[startPC] );
                PC.setHiByte( (*main_memory)[startPC+1] );
        } else {
                ++PC;
                ++PC;
        }
}

// IX INSTRUCTION SET ACCESSOR
void Processor::opcode_0xDD() {} // UNUSED

// sbc a, *
void Processor::opcode_0xDE() {
        uint8_t immediate = (*main_memory)[PC.getValue()];
        AF.setHiByte(AF.getHiByte() - immediate - (int) carryFlag);
}

// rst 18h
void Processor::opcode_0xDF() {
        call_stack.push(PC.getValue());
        PC.setValue(0x18);
}


////////////////////// OPCODE BLOCK 0xE* //////////////////////


// ld (FF00 + *), a 
void Processor::opcode_0xE0() {
	uint16_t addr = 0xFF00 + (*main_memory)[PC.getValue()];
	++PC;
	main_memory -> putByte(AF.getHiByte(), (int)addr);
}

// pop hl
void Processor::opcode_0xE1() {
        uint16_t value = call_stack.pop();
        HL.setValue(value);
}

// ld (FF00 + c), a
void Processor::opcode_0xE2() {
        uint16_t addr = 0xFF00 + BC.getLoByte();
        main_memory -> putByte(AF.getHiByte(), (int)addr);
}

// jp po, **
void Processor::opcode_0xE3() {} // UNUSED

// ex (sp), hl
void Processor::opcode_0xE4() {} // UNUSED

// push hl
void Processor::opcode_0xE5() {
        call_stack.push(HL.getValue());
}

// and *
void Processor::opcode_0xE6() {
        uint8_t immediate = (*main_memory)[PC.getValue()];
        AF.setHiByte(AF.getHiByte() & immediate);
}

// rst 20h
void Processor::opcode_0xE7() {
        call_stack.push(PC.getValue());
        PC.setValue(0x20);
}

// add sp, *
void Processor::opcode_0xE8() {
        uint8_t immediate = (*main_memory)[PC.getValue()];
	SP.setValue( immediate + SP.getValue() );
}

//jp (hl) 
void Processor::opcode_0xE9() {
	PC.setValue(HL.getValue());
}

// ld **, a
void Processor::opcode_0xEA() {
        uint16_t startAddr = PC.getValue();
        uint8_t loByte = (*main_memory)[startAddr];
        ++PC;
        uint8_t hiByte = (*main_memory)[startAddr + 1];
        ++PC;

        uint16_t writeAddr = (uint16_t)(loByte) + (uint16_t)(hiByte << 8);
        main_memory->putByte(AF.getHiByte(), writeAddr);
}

// ex de, hl
void Processor::opcode_0xEB() {} // UNUSED

// call pe, **
void Processor::opcode_0xEC() {} // UNUSED

// EXTD INSTRUCTION SET ACCESSOR
void Processor::opcode_0xED() {} // UNUSED

// xor *
void Processor::opcode_0xEE() {
        uint8_t immediate = (*main_memory)[PC.getValue()];
        AF.setHiByte(AF.getHiByte() ^ immediate);
}

// rst 28h
void Processor::opcode_0xEF() {
        call_stack.push(PC.getValue());
        PC.setValue(0x28);
}


////////////////////// OPCODE BLOCK 0xF* //////////////////////

// ld A, (0xFF00 + n)
void Processor::opcode_0xF0() {
	uint8_t n = (*main_memory)[PC.getValue()];
	++PC;
	uint16_t addr = 0xFF00 + (uint16_t)n;
	uint8_t value = (*main_memory)[addr];
	AF.setHiByte(value);
}

// pop af
void Processor::opcode_0xF1() {
        uint16_t value = call_stack.pop();
        AF.setValue(value);	
}

// ld a, (0xFF00 + c)
void Processor::opcode_0xF2() {
	uint8_t c = BC.getLoByte();
        uint16_t addr = 0xFF00 + (uint16_t)c;
        uint8_t value = (*main_memory)[addr];
        AF.setHiByte(value);
}

// di
void Processor::opcode_0xF3() {
	interrupt_enable = false;
}

// call p, **
void Processor::opcode_0xF4() {} // UNUSED

// push af
void Processor::opcode_0xF5() {
        call_stack.push(HL.getValue());
}

// or *
void Processor::opcode_0xF6() {
        uint8_t immediate = (*main_memory)[PC.getValue()];
        AF.setHiByte(AF.getHiByte() | immediate);
}

// rst 30h
void Processor::opcode_0xF7() {
        call_stack.push(PC.getValue());
        PC.setValue(0x30);
}

// ld hl, sp + *
void Processor::opcode_0xF8() {
        uint8_t n = (*main_memory)[PC.getValue()];
	++PC;
	HL.setValue( SP.getValue() + (uint16_t)n );	
}

// ld sp, hl
void Processor::opcode_0xF9() {
	SP.setValue(HL.getValue());
}

// ld a, ** 
void Processor::opcode_0xFA() {
        uint8_t loByte = (*main_memory)[PC.getValue()];
        ++PC;
        uint8_t hiByte = (*main_memory)[PC.getValue()];
        ++PC;

        uint16_t readAddr = (uint16_t)(loByte) + (uint16_t)(hiByte << 8);
	uint8_t value = (*main_memory)[readAddr];
	AF.setHiByte(value);
}

// ei 
void Processor::opcode_0xFB() {
	interrupt_enable = true;
}

// call m, **
void Processor::opcode_0xFC() {} // UNUSED

// IY INSTRUCTION SET ACCESSOR
void Processor::opcode_0xFD() {} // UNUSED

// cp a, *
void Processor::opcode_0xFE() {}

// rst 38h
void Processor::opcode_0xFF() {
        call_stack.push(PC.getValue());
        PC.setValue(0x38);
}

void Processor::opcode_map_populate() {

        opcode_map.insert( std::make_pair(0, &Processor::opcode_0x00) );
        opcode_map.insert( std::make_pair(1, &Processor::opcode_0x01) );
        opcode_map.insert( std::make_pair(2, &Processor::opcode_0x02) );
        opcode_map.insert( std::make_pair(3, &Processor::opcode_0x03) );
        opcode_map.insert( std::make_pair(4, &Processor::opcode_0x04) );
        opcode_map.insert( std::make_pair(5, &Processor::opcode_0x05) );
        opcode_map.insert( std::make_pair(6, &Processor::opcode_0x06) );
        opcode_map.insert( std::make_pair(7, &Processor::opcode_0x07) );
        opcode_map.insert( std::make_pair(8, &Processor::opcode_0x08) );
        opcode_map.insert( std::make_pair(9, &Processor::opcode_0x09) );
        opcode_map.insert( std::make_pair(10, &Processor::opcode_0x0A) );
        opcode_map.insert( std::make_pair(11, &Processor::opcode_0x0B) );
        opcode_map.insert( std::make_pair(12, &Processor::opcode_0x0C) );
        opcode_map.insert( std::make_pair(13, &Processor::opcode_0x0D) );
        opcode_map.insert( std::make_pair(14, &Processor::opcode_0x0E) );
        opcode_map.insert( std::make_pair(15, &Processor::opcode_0x0F) );

        opcode_map.insert( std::make_pair(16, &Processor::opcode_0x10) );
        opcode_map.insert( std::make_pair(17, &Processor::opcode_0x11) );
        opcode_map.insert( std::make_pair(18, &Processor::opcode_0x12) );
        opcode_map.insert( std::make_pair(19, &Processor::opcode_0x13) );
        opcode_map.insert( std::make_pair(20, &Processor::opcode_0x14) );
        opcode_map.insert( std::make_pair(21, &Processor::opcode_0x15) );
        opcode_map.insert( std::make_pair(22, &Processor::opcode_0x16) );
        opcode_map.insert( std::make_pair(23, &Processor::opcode_0x17) );
        opcode_map.insert( std::make_pair(24, &Processor::opcode_0x18) );
        opcode_map.insert( std::make_pair(25, &Processor::opcode_0x19) );
        opcode_map.insert( std::make_pair(26, &Processor::opcode_0x1A) );
        opcode_map.insert( std::make_pair(27, &Processor::opcode_0x1B) );
        opcode_map.insert( std::make_pair(28, &Processor::opcode_0x1C) );
        opcode_map.insert( std::make_pair(29, &Processor::opcode_0x1D) );
        opcode_map.insert( std::make_pair(30, &Processor::opcode_0x1E) );
        opcode_map.insert( std::make_pair(31, &Processor::opcode_0x1F) );

        opcode_map.insert( std::make_pair(32, &Processor::opcode_0x20) );
        opcode_map.insert( std::make_pair(33, &Processor::opcode_0x21) );
        opcode_map.insert( std::make_pair(34, &Processor::opcode_0x22) );
        opcode_map.insert( std::make_pair(35, &Processor::opcode_0x23) );
        opcode_map.insert( std::make_pair(36, &Processor::opcode_0x24) );
        opcode_map.insert( std::make_pair(37, &Processor::opcode_0x25) );
        opcode_map.insert( std::make_pair(38, &Processor::opcode_0x26) );
        opcode_map.insert( std::make_pair(39, &Processor::opcode_0x27) );
        opcode_map.insert( std::make_pair(40, &Processor::opcode_0x28) );
        opcode_map.insert( std::make_pair(41, &Processor::opcode_0x29) );
        opcode_map.insert( std::make_pair(42, &Processor::opcode_0x2A) );
        opcode_map.insert( std::make_pair(43, &Processor::opcode_0x2B) );
        opcode_map.insert( std::make_pair(44, &Processor::opcode_0x2C) );
        opcode_map.insert( std::make_pair(45, &Processor::opcode_0x2D) );
        opcode_map.insert( std::make_pair(46, &Processor::opcode_0x2E) );
        opcode_map.insert( std::make_pair(47, &Processor::opcode_0x2F) );

        opcode_map.insert( std::make_pair(48, &Processor::opcode_0x30) );
        opcode_map.insert( std::make_pair(49, &Processor::opcode_0x31) );
        opcode_map.insert( std::make_pair(50, &Processor::opcode_0x32) );
        opcode_map.insert( std::make_pair(51, &Processor::opcode_0x33) );
        opcode_map.insert( std::make_pair(52, &Processor::opcode_0x34) );
        opcode_map.insert( std::make_pair(53, &Processor::opcode_0x35) );
        opcode_map.insert( std::make_pair(54, &Processor::opcode_0x36) );
        opcode_map.insert( std::make_pair(55, &Processor::opcode_0x37) );
        opcode_map.insert( std::make_pair(56, &Processor::opcode_0x38) );
        opcode_map.insert( std::make_pair(57, &Processor::opcode_0x39) );
        opcode_map.insert( std::make_pair(58, &Processor::opcode_0x3A) );
        opcode_map.insert( std::make_pair(59, &Processor::opcode_0x3B) );
        opcode_map.insert( std::make_pair(60, &Processor::opcode_0x3C) );
        opcode_map.insert( std::make_pair(61, &Processor::opcode_0x3D) );
        opcode_map.insert( std::make_pair(62, &Processor::opcode_0x3E) );
        opcode_map.insert( std::make_pair(63, &Processor::opcode_0x3F) );

        opcode_map.insert( std::make_pair(64, &Processor::opcode_0x40) );
        opcode_map.insert( std::make_pair(65, &Processor::opcode_0x41) );
        opcode_map.insert( std::make_pair(66, &Processor::opcode_0x42) );
        opcode_map.insert( std::make_pair(67, &Processor::opcode_0x43) );
        opcode_map.insert( std::make_pair(68, &Processor::opcode_0x44) );
        opcode_map.insert( std::make_pair(69, &Processor::opcode_0x45) );
        opcode_map.insert( std::make_pair(70, &Processor::opcode_0x46) );
        opcode_map.insert( std::make_pair(71, &Processor::opcode_0x47) );
        opcode_map.insert( std::make_pair(72, &Processor::opcode_0x48) );
        opcode_map.insert( std::make_pair(73, &Processor::opcode_0x49) );
        opcode_map.insert( std::make_pair(74, &Processor::opcode_0x4A) );
        opcode_map.insert( std::make_pair(75, &Processor::opcode_0x4B) );
        opcode_map.insert( std::make_pair(76, &Processor::opcode_0x4C) );
        opcode_map.insert( std::make_pair(77, &Processor::opcode_0x4D) );
        opcode_map.insert( std::make_pair(78, &Processor::opcode_0x4E) );
        opcode_map.insert( std::make_pair(79, &Processor::opcode_0x4F) );

        opcode_map.insert( std::make_pair(80, &Processor::opcode_0x50) );
        opcode_map.insert( std::make_pair(81, &Processor::opcode_0x51) );
        opcode_map.insert( std::make_pair(82, &Processor::opcode_0x52) );
        opcode_map.insert( std::make_pair(83, &Processor::opcode_0x53) );
        opcode_map.insert( std::make_pair(84, &Processor::opcode_0x54) );
        opcode_map.insert( std::make_pair(85, &Processor::opcode_0x55) );
        opcode_map.insert( std::make_pair(86, &Processor::opcode_0x56) );
        opcode_map.insert( std::make_pair(87, &Processor::opcode_0x57) );
        opcode_map.insert( std::make_pair(88, &Processor::opcode_0x58) );
        opcode_map.insert( std::make_pair(89, &Processor::opcode_0x59) );
        opcode_map.insert( std::make_pair(90, &Processor::opcode_0x5A) );
        opcode_map.insert( std::make_pair(91, &Processor::opcode_0x5B) );
        opcode_map.insert( std::make_pair(92, &Processor::opcode_0x5C) );
        opcode_map.insert( std::make_pair(93, &Processor::opcode_0x5D) );
        opcode_map.insert( std::make_pair(94, &Processor::opcode_0x5E) );
        opcode_map.insert( std::make_pair(95, &Processor::opcode_0x5F) );

        opcode_map.insert( std::make_pair(96, &Processor::opcode_0x60) );
        opcode_map.insert( std::make_pair(97, &Processor::opcode_0x61) );
        opcode_map.insert( std::make_pair(98, &Processor::opcode_0x62) );
        opcode_map.insert( std::make_pair(99, &Processor::opcode_0x63) );
        opcode_map.insert( std::make_pair(100, &Processor::opcode_0x64) );
        opcode_map.insert( std::make_pair(101, &Processor::opcode_0x65) );
        opcode_map.insert( std::make_pair(102, &Processor::opcode_0x66) );
        opcode_map.insert( std::make_pair(103, &Processor::opcode_0x67) );
        opcode_map.insert( std::make_pair(104, &Processor::opcode_0x68) );
        opcode_map.insert( std::make_pair(105, &Processor::opcode_0x69) );
        opcode_map.insert( std::make_pair(106, &Processor::opcode_0x6A) );
        opcode_map.insert( std::make_pair(107, &Processor::opcode_0x6B) );
        opcode_map.insert( std::make_pair(108, &Processor::opcode_0x6C) );
        opcode_map.insert( std::make_pair(109, &Processor::opcode_0x6D) );
        opcode_map.insert( std::make_pair(110, &Processor::opcode_0x6E) );
        opcode_map.insert( std::make_pair(111, &Processor::opcode_0x6F) );

        opcode_map.insert( std::make_pair(112, &Processor::opcode_0x70) );
        opcode_map.insert( std::make_pair(113, &Processor::opcode_0x71) );
        opcode_map.insert( std::make_pair(114, &Processor::opcode_0x72) );
        opcode_map.insert( std::make_pair(115, &Processor::opcode_0x73) );
        opcode_map.insert( std::make_pair(116, &Processor::opcode_0x74) );
        opcode_map.insert( std::make_pair(117, &Processor::opcode_0x75) );
        opcode_map.insert( std::make_pair(118, &Processor::opcode_0x76) );
        opcode_map.insert( std::make_pair(119, &Processor::opcode_0x77) );
        opcode_map.insert( std::make_pair(120, &Processor::opcode_0x78) );
        opcode_map.insert( std::make_pair(121, &Processor::opcode_0x79) );
        opcode_map.insert( std::make_pair(122, &Processor::opcode_0x7A) );
        opcode_map.insert( std::make_pair(123, &Processor::opcode_0x7B) );
        opcode_map.insert( std::make_pair(124, &Processor::opcode_0x7C) );
        opcode_map.insert( std::make_pair(125, &Processor::opcode_0x7D) );
        opcode_map.insert( std::make_pair(126, &Processor::opcode_0x7E) );
        opcode_map.insert( std::make_pair(127, &Processor::opcode_0x7F) );

        opcode_map.insert( std::make_pair(128, &Processor::opcode_0x80) );
        opcode_map.insert( std::make_pair(129, &Processor::opcode_0x81) );
        opcode_map.insert( std::make_pair(130, &Processor::opcode_0x82) );
        opcode_map.insert( std::make_pair(131, &Processor::opcode_0x83) );
        opcode_map.insert( std::make_pair(132, &Processor::opcode_0x84) );
        opcode_map.insert( std::make_pair(133, &Processor::opcode_0x85) );
        opcode_map.insert( std::make_pair(134, &Processor::opcode_0x86) );
        opcode_map.insert( std::make_pair(135, &Processor::opcode_0x87) );
        opcode_map.insert( std::make_pair(136, &Processor::opcode_0x88) );
        opcode_map.insert( std::make_pair(137, &Processor::opcode_0x89) );
        opcode_map.insert( std::make_pair(138, &Processor::opcode_0x8A) );
        opcode_map.insert( std::make_pair(139, &Processor::opcode_0x8B) );
        opcode_map.insert( std::make_pair(140, &Processor::opcode_0x8C) );
        opcode_map.insert( std::make_pair(141, &Processor::opcode_0x8D) );
        opcode_map.insert( std::make_pair(142, &Processor::opcode_0x8E) );
        opcode_map.insert( std::make_pair(143, &Processor::opcode_0x8F) );

        opcode_map.insert( std::make_pair(144, &Processor::opcode_0x90) );
        opcode_map.insert( std::make_pair(145, &Processor::opcode_0x91) );
        opcode_map.insert( std::make_pair(146, &Processor::opcode_0x92) );
        opcode_map.insert( std::make_pair(147, &Processor::opcode_0x93) );
        opcode_map.insert( std::make_pair(148, &Processor::opcode_0x94) );
        opcode_map.insert( std::make_pair(149, &Processor::opcode_0x95) );
        opcode_map.insert( std::make_pair(150, &Processor::opcode_0x96) );
        opcode_map.insert( std::make_pair(151, &Processor::opcode_0x97) );
        opcode_map.insert( std::make_pair(152, &Processor::opcode_0x98) );
        opcode_map.insert( std::make_pair(153, &Processor::opcode_0x99) );
        opcode_map.insert( std::make_pair(154, &Processor::opcode_0x9A) );
        opcode_map.insert( std::make_pair(155, &Processor::opcode_0x9B) );
        opcode_map.insert( std::make_pair(156, &Processor::opcode_0x9C) );
        opcode_map.insert( std::make_pair(157, &Processor::opcode_0x9D) );
        opcode_map.insert( std::make_pair(158, &Processor::opcode_0x9E) );
        opcode_map.insert( std::make_pair(159, &Processor::opcode_0x9F) );

        opcode_map.insert( std::make_pair(160, &Processor::opcode_0xA0) );
        opcode_map.insert( std::make_pair(161, &Processor::opcode_0xA1) );
        opcode_map.insert( std::make_pair(162, &Processor::opcode_0xA2) );
        opcode_map.insert( std::make_pair(163, &Processor::opcode_0xA3) );
        opcode_map.insert( std::make_pair(164, &Processor::opcode_0xA4) );
        opcode_map.insert( std::make_pair(165, &Processor::opcode_0xA5) );
        opcode_map.insert( std::make_pair(166, &Processor::opcode_0xA6) );
        opcode_map.insert( std::make_pair(167, &Processor::opcode_0xA7) );
        opcode_map.insert( std::make_pair(168, &Processor::opcode_0xA8) );
        opcode_map.insert( std::make_pair(169, &Processor::opcode_0xA9) );
        opcode_map.insert( std::make_pair(170, &Processor::opcode_0xAA) );
        opcode_map.insert( std::make_pair(171, &Processor::opcode_0xAB) );
        opcode_map.insert( std::make_pair(172, &Processor::opcode_0xAC) );
        opcode_map.insert( std::make_pair(173, &Processor::opcode_0xAD) );
        opcode_map.insert( std::make_pair(174, &Processor::opcode_0xAE) );
        opcode_map.insert( std::make_pair(175, &Processor::opcode_0xAF) );

        opcode_map.insert( std::make_pair(176, &Processor::opcode_0xB0) );
        opcode_map.insert( std::make_pair(177, &Processor::opcode_0xB1) );
        opcode_map.insert( std::make_pair(178, &Processor::opcode_0xB2) );
        opcode_map.insert( std::make_pair(179, &Processor::opcode_0xB3) );
        opcode_map.insert( std::make_pair(180, &Processor::opcode_0xB4) );
        opcode_map.insert( std::make_pair(181, &Processor::opcode_0xB5) );
        opcode_map.insert( std::make_pair(182, &Processor::opcode_0xB6) );
        opcode_map.insert( std::make_pair(183, &Processor::opcode_0xB7) );
        opcode_map.insert( std::make_pair(184, &Processor::opcode_0xB8) );
        opcode_map.insert( std::make_pair(185, &Processor::opcode_0xB9) );
        opcode_map.insert( std::make_pair(186, &Processor::opcode_0xBA) );
        opcode_map.insert( std::make_pair(187, &Processor::opcode_0xBB) );
        opcode_map.insert( std::make_pair(188, &Processor::opcode_0xBC) );
        opcode_map.insert( std::make_pair(189, &Processor::opcode_0xBD) );
        opcode_map.insert( std::make_pair(190, &Processor::opcode_0xBE) );
        opcode_map.insert( std::make_pair(191, &Processor::opcode_0xBF) );

        opcode_map.insert( std::make_pair(192, &Processor::opcode_0xC0) );
        opcode_map.insert( std::make_pair(193, &Processor::opcode_0xC1) );
        opcode_map.insert( std::make_pair(194, &Processor::opcode_0xC2) );
        opcode_map.insert( std::make_pair(195, &Processor::opcode_0xC3) );
        opcode_map.insert( std::make_pair(196, &Processor::opcode_0xC4) );
        opcode_map.insert( std::make_pair(197, &Processor::opcode_0xC5) );
        opcode_map.insert( std::make_pair(198, &Processor::opcode_0xC6) );
        opcode_map.insert( std::make_pair(199, &Processor::opcode_0xC7) );
        opcode_map.insert( std::make_pair(200, &Processor::opcode_0xC8) );
        opcode_map.insert( std::make_pair(201, &Processor::opcode_0xC9) );
        opcode_map.insert( std::make_pair(202, &Processor::opcode_0xCA) );
        opcode_map.insert( std::make_pair(203, &Processor::opcode_0xCB) );
        opcode_map.insert( std::make_pair(204, &Processor::opcode_0xCC) );
        opcode_map.insert( std::make_pair(205, &Processor::opcode_0xCD) );
        opcode_map.insert( std::make_pair(206, &Processor::opcode_0xCE) );
        opcode_map.insert( std::make_pair(207, &Processor::opcode_0xCF) );

        opcode_map.insert( std::make_pair(208, &Processor::opcode_0xD0) );
        opcode_map.insert( std::make_pair(209, &Processor::opcode_0xD1) );
        opcode_map.insert( std::make_pair(210, &Processor::opcode_0xD2) );
        opcode_map.insert( std::make_pair(211, &Processor::opcode_0xD3) );
        opcode_map.insert( std::make_pair(212, &Processor::opcode_0xD4) );
        opcode_map.insert( std::make_pair(213, &Processor::opcode_0xD5) );
        opcode_map.insert( std::make_pair(214, &Processor::opcode_0xD6) );
        opcode_map.insert( std::make_pair(215, &Processor::opcode_0xD7) );
        opcode_map.insert( std::make_pair(216, &Processor::opcode_0xD8) );
        opcode_map.insert( std::make_pair(217, &Processor::opcode_0xD9) );
        opcode_map.insert( std::make_pair(218, &Processor::opcode_0xDA) );
        opcode_map.insert( std::make_pair(219, &Processor::opcode_0xDB) );
        opcode_map.insert( std::make_pair(220, &Processor::opcode_0xDC) );
        opcode_map.insert( std::make_pair(221, &Processor::opcode_0xDD) );
        opcode_map.insert( std::make_pair(222, &Processor::opcode_0xDE) );
        opcode_map.insert( std::make_pair(223, &Processor::opcode_0xDF) );

        opcode_map.insert( std::make_pair(224, &Processor::opcode_0xE0) );
        opcode_map.insert( std::make_pair(225, &Processor::opcode_0xE1) );
        opcode_map.insert( std::make_pair(226, &Processor::opcode_0xE2) );
        opcode_map.insert( std::make_pair(227, &Processor::opcode_0xE3) );
        opcode_map.insert( std::make_pair(228, &Processor::opcode_0xE4) );
        opcode_map.insert( std::make_pair(229, &Processor::opcode_0xE5) );
        opcode_map.insert( std::make_pair(230, &Processor::opcode_0xE6) );
        opcode_map.insert( std::make_pair(231, &Processor::opcode_0xE7) );
        opcode_map.insert( std::make_pair(232, &Processor::opcode_0xE8) );
        opcode_map.insert( std::make_pair(233, &Processor::opcode_0xE9) );
        opcode_map.insert( std::make_pair(234, &Processor::opcode_0xEA) );
        opcode_map.insert( std::make_pair(235, &Processor::opcode_0xEB) );
        opcode_map.insert( std::make_pair(236, &Processor::opcode_0xEC) );
        opcode_map.insert( std::make_pair(237, &Processor::opcode_0xED) );
        opcode_map.insert( std::make_pair(238, &Processor::opcode_0xEE) );
        opcode_map.insert( std::make_pair(239, &Processor::opcode_0xEF) );

        opcode_map.insert( std::make_pair(240, &Processor::opcode_0xF0) );
        opcode_map.insert( std::make_pair(241, &Processor::opcode_0xF1) );
        opcode_map.insert( std::make_pair(242, &Processor::opcode_0xF2) );
        opcode_map.insert( std::make_pair(243, &Processor::opcode_0xF3) );
        opcode_map.insert( std::make_pair(244, &Processor::opcode_0xF4) );
        opcode_map.insert( std::make_pair(245, &Processor::opcode_0xF5) );
        opcode_map.insert( std::make_pair(246, &Processor::opcode_0xF6) );
        opcode_map.insert( std::make_pair(247, &Processor::opcode_0xF7) );
        opcode_map.insert( std::make_pair(248, &Processor::opcode_0xF8) );
        opcode_map.insert( std::make_pair(249, &Processor::opcode_0xF9) );
        opcode_map.insert( std::make_pair(250, &Processor::opcode_0xFA) );
        opcode_map.insert( std::make_pair(251, &Processor::opcode_0xFB) );
        opcode_map.insert( std::make_pair(252, &Processor::opcode_0xFC) );
        opcode_map.insert( std::make_pair(253, &Processor::opcode_0xFD) );
        opcode_map.insert( std::make_pair(254, &Processor::opcode_0xFE) );
        opcode_map.insert( std::make_pair(255, &Processor::opcode_0xFF) );

}
