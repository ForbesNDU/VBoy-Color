#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "boost/function.hpp"
#include "CPU_Stack.h"
#include <map>
#include "Memory.h"
#include "Register.h"
#include "VideoMemory.h"

class Processor {
	public:
		Processor(Memory*);
		~Processor();

	private:
		// Opcode Mapping Utils
		typedef void (*opcode_functor)(void);
		
		std::map<uint8_t, opcode_functor> opcode_map;		
		void opcode_map_populate();

		std::map<uint8_t, opcode_functor> cb_extension_map;
		void cb_map_populate();

		// High-Level Abstractions
		static bool halted;
		static bool interrupt_enable;
		static bool stopped;

		// Internal Storage (Locally Defined & Managed)
		static CPU_Stack call_stack;		

		static Register AF;
		static Register BC;
		static Register DE;
		static Register HL;
		static Register SP;
		static Register PC;

		static bool zeroFlag;
		static bool addSubFlag;
		static bool halfCarryFlag;
		static bool carryFlag;

		// Peripheral Storage (Externally Defined & Managed)
		static Memory *main_memory;
		static VideoMemory *video_memory;

		// Opcode Helpers
		bool testMemoryBit(int);
		void resetMemoryBit(int);
		void setMemoryBit(int);

		// Primary Opcode Function Defs
		static void opcode_0x00();
		static void opcode_0x01();
		static void opcode_0x02();
		static void opcode_0x03();
		static void opcode_0x04();
		static void opcode_0x05();
		static void opcode_0x06();
		static void opcode_0x07();
		static void opcode_0x08();
		static void opcode_0x09();
		static void opcode_0x0A();
		static void opcode_0x0B();
		static void opcode_0x0C();
		static void opcode_0x0D();
		static void opcode_0x0E();
		static void opcode_0x0F();

		static void opcode_0x10();
		static void opcode_0x11();
		static void opcode_0x12();
		static void opcode_0x13();
		static void opcode_0x14();
		static void opcode_0x15();
		static void opcode_0x16();
		static void opcode_0x17();
		static void opcode_0x18();
		static void opcode_0x19();
		static void opcode_0x1A();
		static void opcode_0x1B();
		static void opcode_0x1C();
		static void opcode_0x1D();
		static void opcode_0x1E();
		static void opcode_0x1F();

		static void opcode_0x20();
		static void opcode_0x21();
		static void opcode_0x22();
		static void opcode_0x23();
		static void opcode_0x24();
		static void opcode_0x25();
		static void opcode_0x26();
		static void opcode_0x27();
		static void opcode_0x28();
		static void opcode_0x29();
		static void opcode_0x2A();
		static void opcode_0x2B();
		static void opcode_0x2C();
		static void opcode_0x2D();
		static void opcode_0x2E();
		static void opcode_0x2F();

		static void opcode_0x30();
		static void opcode_0x31();
		static void opcode_0x32();
		static void opcode_0x33();
		static void opcode_0x34();
		static void opcode_0x35();
		static void opcode_0x36();
		static void opcode_0x37();
		static void opcode_0x38();
		static void opcode_0x39();
		static void opcode_0x3A();
		static void opcode_0x3B();
		static void opcode_0x3C();
		static void opcode_0x3D();
		static void opcode_0x3E();
		static void opcode_0x3F();

		static void opcode_0x40();
		static void opcode_0x41();
		static void opcode_0x42();
		static void opcode_0x43();
		static void opcode_0x44();
		static void opcode_0x45();
		static void opcode_0x46();
		static void opcode_0x47();
		static void opcode_0x48();
		static void opcode_0x49();
		static void opcode_0x4A();
		static void opcode_0x4B();
		static void opcode_0x4C();
		static void opcode_0x4D();
		static void opcode_0x4E();
		static void opcode_0x4F();

		static void opcode_0x50();
		static void opcode_0x51();
		static void opcode_0x52();
		static void opcode_0x53();
		static void opcode_0x54();
		static void opcode_0x55();
		static void opcode_0x56();
		static void opcode_0x57();
		static void opcode_0x58();
		static void opcode_0x59();
		static void opcode_0x5A();
		static void opcode_0x5B();
		static void opcode_0x5C();
		static void opcode_0x5D();
		static void opcode_0x5E();
		static void opcode_0x5F();

		static void opcode_0x60();
		static void opcode_0x61();
		static void opcode_0x62();
		static void opcode_0x63();
		static void opcode_0x64();
		static void opcode_0x65();
		static void opcode_0x66();
		static void opcode_0x67();
		static void opcode_0x68();
		static void opcode_0x69();
		static void opcode_0x6A();
		static void opcode_0x6B();
		static void opcode_0x6C();
		static void opcode_0x6D();
		static void opcode_0x6E();
		static void opcode_0x6F();

		static void opcode_0x70();
		static void opcode_0x71();
		static void opcode_0x72();
		static void opcode_0x73();
		static void opcode_0x74();
		static void opcode_0x75();
		static void opcode_0x76();
		static void opcode_0x77();
		static void opcode_0x78();
		static void opcode_0x79();
		static void opcode_0x7A();
		static void opcode_0x7B();
		static void opcode_0x7C();
		static void opcode_0x7D();
		static void opcode_0x7E();
		static void opcode_0x7F();

		static void opcode_0x80();
		static void opcode_0x81();
		static void opcode_0x82();
		static void opcode_0x83();
		static void opcode_0x84();
		static void opcode_0x85();
		static void opcode_0x86();
		static void opcode_0x87();
		static void opcode_0x88();
		static void opcode_0x89();
		static void opcode_0x8A();
		static void opcode_0x8B();
		static void opcode_0x8C();
		static void opcode_0x8D();
		static void opcode_0x8E();
		static void opcode_0x8F();

		static void opcode_0x90();
		static void opcode_0x91();
		static void opcode_0x92();
		static void opcode_0x93();
		static void opcode_0x94();
		static void opcode_0x95();
		static void opcode_0x96();
		static void opcode_0x97();
		static void opcode_0x98();
		static void opcode_0x99();
		static void opcode_0x9A();
		static void opcode_0x9B();
		static void opcode_0x9C();
		static void opcode_0x9D();
		static void opcode_0x9E();
		static void opcode_0x9F();

		static void opcode_0xA0();
		static void opcode_0xA1();
		static void opcode_0xA2();
		static void opcode_0xA3();
		static void opcode_0xA4();
		static void opcode_0xA5();
		static void opcode_0xA6();
		static void opcode_0xA7();
		static void opcode_0xA8();
		static void opcode_0xA9();
		static void opcode_0xAA();
		static void opcode_0xAB();
		static void opcode_0xAC();
		static void opcode_0xAD();
		static void opcode_0xAE();
		static void opcode_0xAF();

		static void opcode_0xB0();
		static void opcode_0xB1();
		static void opcode_0xB2();
		static void opcode_0xB3();
		static void opcode_0xB4();
		static void opcode_0xB5();
		static void opcode_0xB6();
		static void opcode_0xB7();
		static void opcode_0xB8();
		static void opcode_0xB9();
		static void opcode_0xBA();
		static void opcode_0xBB();
		static void opcode_0xBC();
		static void opcode_0xBD();
		static void opcode_0xBE();
		static void opcode_0xBF();

		static void opcode_0xC0();
		static void opcode_0xC1();
		static void opcode_0xC2();
		static void opcode_0xC3();
		static void opcode_0xC4();
		static void opcode_0xC5();
		static void opcode_0xC6();
		static void opcode_0xC7();
		static void opcode_0xC8();
		static void opcode_0xC9();
		static void opcode_0xCA();
		static void opcode_0xCB();
		static void opcode_0xCC();
		static void opcode_0xCD();
		static void opcode_0xCE();
		static void opcode_0xCF();

		static void opcode_0xD0();
		static void opcode_0xD1();
		static void opcode_0xD2();
		static void opcode_0xD3();
		static void opcode_0xD4();
		static void opcode_0xD5();
		static void opcode_0xD6();
		static void opcode_0xD7();
		static void opcode_0xD8();
		static void opcode_0xD9();
		static void opcode_0xDA();
		static void opcode_0xDB();
		static void opcode_0xDC();
		static void opcode_0xDD();
		static void opcode_0xDE();
		static void opcode_0xDF();

		static void opcode_0xE0();
		static void opcode_0xE1();
		static void opcode_0xE2();
		static void opcode_0xE3();
		static void opcode_0xE4();
		static void opcode_0xE5();
		static void opcode_0xE6();
		static void opcode_0xE7();
		static void opcode_0xE8();
		static void opcode_0xE9();
		static void opcode_0xEA();
		static void opcode_0xEB();
		static void opcode_0xEC();
		static void opcode_0xED();
		static void opcode_0xEE();
		static void opcode_0xEF();

		static void opcode_0xF0();
		static void opcode_0xF1();
		static void opcode_0xF2();
		static void opcode_0xF3();
		static void opcode_0xF4();
		static void opcode_0xF5();
		static void opcode_0xF6();
		static void opcode_0xF7();
		static void opcode_0xF8();
		static void opcode_0xF9();
		static void opcode_0xFA();
		static void opcode_0xFB();
		static void opcode_0xFC();
		static void opcode_0xFD();
		static void opcode_0xFE();
		static void opcode_0xFF();

		// CB Opcode Definitions

		static void CB_opcode_0x00();
		static void CB_opcode_0x01();
		static void CB_opcode_0x02();
		static void CB_opcode_0x03();
		static void CB_opcode_0x04();
		static void CB_opcode_0x05();
		static void CB_opcode_0x06();
		static void CB_opcode_0x07();
		static void CB_opcode_0x08();
		static void CB_opcode_0x09();
		static void CB_opcode_0x0A();
		static void CB_opcode_0x0B();
		static void CB_opcode_0x0C();
		static void CB_opcode_0x0D();
		static void CB_opcode_0x0E();
		static void CB_opcode_0x0F();

		static void CB_opcode_0x10();
		static void CB_opcode_0x11();
		static void CB_opcode_0x12();
		static void CB_opcode_0x13();
		static void CB_opcode_0x14();
		static void CB_opcode_0x15();
		static void CB_opcode_0x16();
		static void CB_opcode_0x17();
		static void CB_opcode_0x18();
		static void CB_opcode_0x19();
		static void CB_opcode_0x1A();
		static void CB_opcode_0x1B();
		static void CB_opcode_0x1C();
		static void CB_opcode_0x1D();
		static void CB_opcode_0x1E();
		static void CB_opcode_0x1F();

		static void CB_opcode_0x20();
		static void CB_opcode_0x21();
		static void CB_opcode_0x22();
		static void CB_opcode_0x23();
		static void CB_opcode_0x24();
		static void CB_opcode_0x25();
		static void CB_opcode_0x26();
		static void CB_opcode_0x27();
		static void CB_opcode_0x28();
		static void CB_opcode_0x29();
		static void CB_opcode_0x2A();
		static void CB_opcode_0x2B();
		static void CB_opcode_0x2C();
		static void CB_opcode_0x2D();
		static void CB_opcode_0x2E();
		static void CB_opcode_0x2F();

		static void CB_opcode_0x30();
		static void CB_opcode_0x31();
		static void CB_opcode_0x32();
		static void CB_opcode_0x33();
		static void CB_opcode_0x34();
		static void CB_opcode_0x35();
		static void CB_opcode_0x36();
		static void CB_opcode_0x37();
		static void CB_opcode_0x38();
		static void CB_opcode_0x39();
		static void CB_opcode_0x3A();
		static void CB_opcode_0x3B();
		static void CB_opcode_0x3C();
		static void CB_opcode_0x3D();
		static void CB_opcode_0x3E();
		static void CB_opcode_0x3F();

		static void CB_opcode_0x40();
		static void CB_opcode_0x41();
		static void CB_opcode_0x42();
		static void CB_opcode_0x43();
		static void CB_opcode_0x44();
		static void CB_opcode_0x45();
		static void CB_opcode_0x46();
		static void CB_opcode_0x47();
		static void CB_opcode_0x48();
		static void CB_opcode_0x49();
		static void CB_opcode_0x4A();
		static void CB_opcode_0x4B();
		static void CB_opcode_0x4C();
		static void CB_opcode_0x4D();
		static void CB_opcode_0x4E();
		static void CB_opcode_0x4F();

		static void CB_opcode_0x50();
		static void CB_opcode_0x51();
		static void CB_opcode_0x52();
		static void CB_opcode_0x53();
		static void CB_opcode_0x54();
		static void CB_opcode_0x55();
		static void CB_opcode_0x56();
		static void CB_opcode_0x57();
		static void CB_opcode_0x58();
		static void CB_opcode_0x59();
		static void CB_opcode_0x5A();
		static void CB_opcode_0x5B();
		static void CB_opcode_0x5C();
		static void CB_opcode_0x5D();
		static void CB_opcode_0x5E();
		static void CB_opcode_0x5F();

		static void CB_opcode_0x60();
		static void CB_opcode_0x61();
		static void CB_opcode_0x62();
		static void CB_opcode_0x63();
		static void CB_opcode_0x64();
		static void CB_opcode_0x65();
		static void CB_opcode_0x66();
		static void CB_opcode_0x67();
		static void CB_opcode_0x68();
		static void CB_opcode_0x69();
		static void CB_opcode_0x6A();
		static void CB_opcode_0x6B();
		static void CB_opcode_0x6C();
		static void CB_opcode_0x6D();
		static void CB_opcode_0x6E();
		static void CB_opcode_0x6F();

		static void CB_opcode_0x70();
		static void CB_opcode_0x71();
		static void CB_opcode_0x72();
		static void CB_opcode_0x73();
		static void CB_opcode_0x74();
		static void CB_opcode_0x75();
		static void CB_opcode_0x76();
		static void CB_opcode_0x77();
		static void CB_opcode_0x78();
		static void CB_opcode_0x79();
		static void CB_opcode_0x7A();
		static void CB_opcode_0x7B();
		static void CB_opcode_0x7C();
		static void CB_opcode_0x7D();
		static void CB_opcode_0x7E();
		static void CB_opcode_0x7F();

		static void CB_opcode_0x80();
		static void CB_opcode_0x81();
		static void CB_opcode_0x82();
		static void CB_opcode_0x83();
		static void CB_opcode_0x84();
		static void CB_opcode_0x85();
		static void CB_opcode_0x86();
		static void CB_opcode_0x87();
		static void CB_opcode_0x88();
		static void CB_opcode_0x89();
		static void CB_opcode_0x8A();
		static void CB_opcode_0x8B();
		static void CB_opcode_0x8C();
		static void CB_opcode_0x8D();
		static void CB_opcode_0x8E();
		static void CB_opcode_0x8F();

		static void CB_opcode_0x90();
		static void CB_opcode_0x91();
		static void CB_opcode_0x92();
		static void CB_opcode_0x93();
		static void CB_opcode_0x94();
		static void CB_opcode_0x95();
		static void CB_opcode_0x96();
		static void CB_opcode_0x97();
		static void CB_opcode_0x98();
		static void CB_opcode_0x99();
		static void CB_opcode_0x9A();
		static void CB_opcode_0x9B();
		static void CB_opcode_0x9C();
		static void CB_opcode_0x9D();
		static void CB_opcode_0x9E();
		static void CB_opcode_0x9F();

		static void CB_opcode_0xA0();
		static void CB_opcode_0xA1();
		static void CB_opcode_0xA2();
		static void CB_opcode_0xA3();
		static void CB_opcode_0xA4();
		static void CB_opcode_0xA5();
		static void CB_opcode_0xA6();
		static void CB_opcode_0xA7();
		static void CB_opcode_0xA8();
		static void CB_opcode_0xA9();
		static void CB_opcode_0xAA();
		static void CB_opcode_0xAB();
		static void CB_opcode_0xAC();
		static void CB_opcode_0xAD();
		static void CB_opcode_0xAE();
		static void CB_opcode_0xAF();

		static void CB_opcode_0xB0();
		static void CB_opcode_0xB1();
		static void CB_opcode_0xB2();
		static void CB_opcode_0xB3();
		static void CB_opcode_0xB4();
		static void CB_opcode_0xB5();
		static void CB_opcode_0xB6();
		static void CB_opcode_0xB7();
		static void CB_opcode_0xB8();
		static void CB_opcode_0xB9();
		static void CB_opcode_0xBA();
		static void CB_opcode_0xBB();
		static void CB_opcode_0xBC();
		static void CB_opcode_0xBD();
		static void CB_opcode_0xBE();
		static void CB_opcode_0xBF();

		static void CB_opcode_0xC0();
		static void CB_opcode_0xC1();
		static void CB_opcode_0xC2();
		static void CB_opcode_0xC3();
		static void CB_opcode_0xC4();
		static void CB_opcode_0xC5();
		static void CB_opcode_0xC6();
		static void CB_opcode_0xC7();
		static void CB_opcode_0xC8();
		static void CB_opcode_0xC9();
		static void CB_opcode_0xCA();
		static void CB_opcode_0xCB();
		static void CB_opcode_0xCC();
		static void CB_opcode_0xCD();
		static void CB_opcode_0xCE();
		static void CB_opcode_0xCF();

		static void CB_opcode_0xD0();
		static void CB_opcode_0xD1();
		static void CB_opcode_0xD2();
		static void CB_opcode_0xD3();
		static void CB_opcode_0xD4();
		static void CB_opcode_0xD5();
		static void CB_opcode_0xD6();
		static void CB_opcode_0xD7();
		static void CB_opcode_0xD8();
		static void CB_opcode_0xD9();
		static void CB_opcode_0xDA();
		static void CB_opcode_0xDB();
		static void CB_opcode_0xDC();
		static void CB_opcode_0xDD();
		static void CB_opcode_0xDE();
		static void CB_opcode_0xDF();

		static void CB_opcode_0xE0();
		static void CB_opcode_0xE1();
		static void CB_opcode_0xE2();
		static void CB_opcode_0xE3();
		static void CB_opcode_0xE4();
		static void CB_opcode_0xE5();
		static void CB_opcode_0xE6();
		static void CB_opcode_0xE7();
		static void CB_opcode_0xE8();
		static void CB_opcode_0xE9();
		static void CB_opcode_0xEA();
		static void CB_opcode_0xEB();
		static void CB_opcode_0xEC();
		static void CB_opcode_0xED();
		static void CB_opcode_0xEE();
		static void CB_opcode_0xEF();

		static void CB_opcode_0xF0();
		static void CB_opcode_0xF1();
		static void CB_opcode_0xF2();
		static void CB_opcode_0xF3();
		static void CB_opcode_0xF4();
		static void CB_opcode_0xF5();
		static void CB_opcode_0xF6();
		static void CB_opcode_0xF7();
		static void CB_opcode_0xF8();
		static void CB_opcode_0xF9();
		static void CB_opcode_0xFA();
		static void CB_opcode_0xFB();
		static void CB_opcode_0xFC();
		static void CB_opcode_0xFD();
		static void CB_opcode_0xFE();
		static void CB_opcode_0xFF();

};

#endif
