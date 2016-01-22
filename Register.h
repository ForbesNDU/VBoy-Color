#ifndef REGISTER_H
#define REGISTER_H

#include <stdlib.h>
#include <stdint.h>

class Register {
	public:
		Register();
		~Register();
		
		void setHiByte(uint8_t);
		void setLoByte(uint8_t);
		void setValue(uint16_t);	

		uint8_t getHiByte() const;
		uint8_t getLoByte() const;
		uint16_t getValue() const;
		
		void operator=(const Register&);
		Register& operator++();
		Register& operator--();	

		void IncrementLo();
		void DecrementLo();
		void IncrementHi();
		void DecrementHi();
		uint8_t RotateLeftHi();		// rotate ops return the dropped bit for flagging
		uint8_t RotateLeftLo();
		uint8_t RotateRightHi();
    uint8_t RotateRightLo();

		bool testHiBit(int);
		bool testLoBit(int);

		void resetHiBit(int);
		void resetLoBit(int);

		void setHiBit(int);
		void setLoBit(int);

	private:
		uint8_t HI;
		uint8_t LO;
};

#endif
