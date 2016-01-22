#include "CPU_Stack.h"

CPU_Stack::CPU_Stack(Register* SP) {
	stack_pointer = SP;
}

CPU_Stack::~CPU_Stack() {

}

void CPU_Stack::push(uint16_t value) {
	uint8_t hiByte = (uint8_t)((value & 0xFF00) >> 8);
	uint8_t loByte = (uint8_t)(value & 0x00FF);
	call_stack.push(hiByte);
	call_stack.push(loByte);

	stack_pointer->setValue( stack_pointer -> getValue() - 2 );	
}

uint16_t CPU_Stack::pop() {
	uint8_t loByte, hiByte;

	if(!call_stack.empty()) {
		loByte = call_stack.top();
		call_stack.pop();
		hiByte = call_stack.top();
		call_stack.pop();
	} else {
		return 0;
	}

	uint16_t extLo = (uint16_t)loByte;
	uint16_t extHi = ((uint16_t)hiByte) << 8;

	stack_pointer->setValue( stack_pointer -> getValue() + 2 );
	
	return extLo + extHi;

}
