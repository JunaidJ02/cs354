/*  main.c  - main */

#include <xinu.h>
void testCPUXRegister();
void CPU3200Check();
void CPU3700Check();
void CPU4000Check();
void CPU4500Check();

void testWALLXRegister();
void WALL1000Check();
void WALL2000Check();
void WALL5000Check();

void testBothRegisters();

process	main(void)
{
	#if XINUTEST == 1
		testWALLXRegister();
		testCPUXRegister();
		testBothRegisters();
	#endif

	while(1);
	return OK;   
}

/* ----------- WALLXRegister Tests Start ----------- */

void testWALLXRegister() {
	kprintf("Running Test 1:\n");
	if (cbcpuxregister(&WALL1000Check, 994) == SYSERR) {
		kprintf("Test 1: An error occured trying to set callback function");
	}

	int i;
	int j = 0;
	for (i = 0; i < 49999999; i++) {
		j *= i;
	}
}

/* ----------- WALLXRegister Tests End ----------- */

/* ----------- CPUXRegister Tests Start ----------- */

void testCPUXRegister() {
	kprintf("Running Test 3:\n");
	if (cbcpuxregister(&CPU3200Check, 3200) == SYSERR) {
		kprintf("Test 3: An error occured trying to set callback function\n");
	}
	int i;
	int j = 0;
	for (i = 0; i < 9999999; i++) {
		j *= i;
	}
	kprintf("Running Test 4:\n");
	if (cbcpuxregister(&CPU3700Check, 3700) == SYSERR) {
		kprintf("Test 4: An error occured trying to set callback function\n");
	}
	for (i = 0; i < 9999999; i++) {
		j *= i;
	}
}

/* ----------- CPUXRegister Tests End ----------- */

/* ----------- Robustness Tests Start ----------- */

void testBothRegisters() {
	kprintf("Running Test 5:\n");
	if (cbcpuxregister(&CPU4000Check, 4000) == SYSERR) {
		kprintf("Test 5: An error occured trying to set callback function\n");
	}

	if (cbwallxregister(&WALL5000Check, 4999) == SYSERR) {
		kprintf("Test 6: An error occured trying to set callback function\n");
	}

	int i;
	int j = 0;
	for (i = 0; i < 9999999; i++) {
		j *= i;
	}
}
/* ----------- Robustness Tests End ----------- */

/* ----------- Helper Functions Start ----------- */

void CPU3200Check() {
	uint32 usage = cpuusage(currpid);
	kprintf("Expected: 3200\nActual: %d\n\n", usage);
	return;
}

void CPU3700Check() {
	uint32 usage = cpuusage(currpid);
	kprintf("Expected: 3700\nActual: %d\n\n", usage);
	return;
}

void CPU4000Check() {
	uint32 usage = cpuusage(currpid);
	kprintf("Expected: 4000\nActual: %d\n\n", usage);
	return;
}

void WALL1000Check() {
	kprintf("Expected: 1000\nActual: %d\n\n", ctr1000);
	kprintf("Running Test 2:\n");
	if (cbcpuxregister(&WALL2000Check, 1994) == SYSERR) {
		kprintf("Test 2: An error occured trying to set callback function");
	}
	return;
}

void WALL2000Check() {
	kprintf("Expected: 2000\nActual: %d\n\n", ctr1000);
	return;
}

void WALL5000Check() {
	kprintf("Running Test 6:\n");
	kprintf("Expected: 5000\nActual: %d\n\n", ctr1000);
	return;
}

/* ----------- Helper Functions End ----------- */