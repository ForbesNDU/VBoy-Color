#include "Register.h"

Register::Register() {
	HI = 0;
	LO = 0;
}

Register::~Register() {

}

// VALUE ACCESSORS 

void Register::setHiByte(uint8_t newValue) {
	HI = newValue;
}

void Register::setLoByte(uint8_t newValue) {
	LO = newValue;
}

void Register::setValue(uint16_t newValue) {
	LO = (uint8_t)(newValue & 0x00FF);
	HI = (uint8_t)((newValue & 0xFF00) >> 8);
}

uint8_t Register::getHiByte() const{
	return HI;
}

uint8_t Register::getLoByte() const{
	return LO;
}

uint16_t Register::getValue() const{
	uint16_t ext_hi = (uint16_t)HI;
	uint16_t ext_lo = (uint16_t)LO;
	return ext_lo + (ext_hi << 8);
}

// OVERLOADED OPERATIONS

void Register::operator=(const Register &source) {
	LO = source.getLoByte();
	HI = source.getHiByte();
}

Register& Register::operator++() {
	if(LO == 255) {
		LO = 0;
		HI++;
	} else {
		LO++;
	}
	return *this;
}

Register& Register::operator--() {
	if(LO == 0 && HI != 0) {
		LO = 255;
		HI--;
	} 
	else if (LO == 0 && HI == 0) {
		LO = 255;
		HI = 255;
	}
	else {
		LO--;
	}	
	return *this;
}

// INCREMENT AND DECREMENT

void Register::IncrementLo() {
	LO++;
}	

void Register::DecrementLo() {
	LO--;
}

void Register::IncrementHi() {
	HI++;
}

void Register::DecrementHi() {
	HI--;
}

// ROTATIONS

uint8_t Register::RotateLeftHi() {
	uint8_t mask = 1 << 7;
	uint8_t flag = (mask & HI) >> 7;
	HI = (HI << 1) | flag;

	return flag;			
}

uint8_t Register::RotateLeftLo() {
	uint8_t mask = 1 << 7;
        uint8_t flag = (mask & LO) >> 7;
        LO = (LO << 1) | flag;

        return flag;
}

uint8_t Register::RotateRightHi() {
	uint8_t mask = 1;
	uint8_t flag = (mask & HI);
	HI = (HI >> 1) | (flag << 7);

	return flag;
}

uint8_t Register::RotateRightLo() {
        uint8_t mask = 1;
        uint8_t flag = (mask & LO);
        LO = (LO >> 1) | (flag << 7);

        return flag;
}

// BIT OPERATIONS

bool Register::testHiBit(int idx) {
	int value = (1 << idx) & HI;
	return (bool)value;	
}

bool Register::testLoBit(int idx) {
	int value = (1 << idx) & LO;
	return (bool)value;
}

void Register::resetHiBit(int idx) {
	uint8_t mask = ~(1 << idx);
	HI = HI & mask;
}

void Register::resetLoBit(int idx) {
	uint8_t mask = ~(1 << idx);
	LO = LO & mask;
}

void Register::setHiBit(int idx) {
	uint8_t mask = 1 << idx;
        HI = HI | mask;
}

void Register::setLoBit(int idx) {
        uint8_t mask = 1 << idx;
        LO = LO | mask;
}





