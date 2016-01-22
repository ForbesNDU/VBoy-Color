#include <iostream>
#include "Processor.h"
#include "Register.h"
#include "Memory.h"
#include "CPU_Stack.h"
#include "VideoMemory.h"

int main(int argc, char **argv) {
	
	Register reg;
	Memory mem(5);
	Processor proc(&mem);
	VideoMemory vmem;
	CPU_Stack stack(&reg);

	return 0;

}
