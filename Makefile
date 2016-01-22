test : test.o Register.o Processor.o Memory.o VideoMemory.o CPU_Stack.o
  g++ test.o Register.o Processor.o Memory.o VideoMemory.o CPU_Stack.o -o test

test.o : test.cxx
  g++ -Wall -g -c test.cxx -o test.o 

Register.o : Register.cxx Register.h
	g++ -Wall -g -c Register.cxx -o Register.o

Processor.o : Processor.cxx Processor.h
	g++ -Wall -g -c Processor.cxx -o Processor.o

Memory.o : Memory.cxx Memory.h
	g++ -Wall -g -c Memory.cxx -o Memory.o

VideoMemory.o : VideoMemory.cxx VideoMemory.h
	g++ -Wall -g -c VideoMemory.cxx -o VideoMemory.o

CPU_Stack.o : CPU_Stack.cxx CPU_Stack.h
	g++ -Wall -g -c CPU_Stack.cxx -o CPU_Stack.o

clean:
	rm *.o test
