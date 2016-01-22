#ifndef CPU_STACK_H
#define CPU_STACK_H

#include "Register.h"
#include <stack>

class CPU_Stack {
	public:
		CPU_Stack(Register*);
		~CPU_Stack();

		void push(uint16_t);
		uint16_t pop();

	private:
		std::stack<uint8_t> call_stack;
		Register* stack_pointer;	

};

#endif
