/*  main.c  - main */

#include <xinu.h>
void testCPUXRegister();
void CPU50Check();
void CPU600Check();
void CPU4000Check();
void CPU4500Check();

void testWALLXRegister();
void WALL1000Check();
void WALL2000Check();
void WALL4000Check();

void testBothRegisters();
void testFailRegistration();
void failRegistrationHelper();

uint32 score = 0;

process	main(void)
{
	#if XINUTEST == 1
		resume(create(testWALLXRegister, INITSTK, 24, "testWALLXRegister", 0, NULL));
		resume(create(testCPUXRegister, INITSTK, 23, "testCPUXRegister", 0, NULL));
		resume(create(testBothRegisters, INITSTK, 22, "testBothRegisters", 0, NULL));
		resume(create(testFailRegistration, INITSTK, 21, "testFailRegistration", 0, NULL));
	#endif

	kprintf("Score: %d/10", score);

	while(1);
	return OK;   
}

/* ----------- WALLXRegister Tests Start ----------- */

void testWALLXRegister() {
	if (cbcpuxregister(&WALL1000Check, 1000) == SYSERR) {
		kprintf("Test 1: An error occured trying to set callback function");
	}
	kprintf("Running Test 1:\n");
	if (cbcpuxregister(&WALL1000Check, 1000) == SYSERR) {
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
	if (cbcpuxregister(&CPU50Check, 50) == SYSERR) {
		kprintf("Test 3: An error occured trying to set callback function\n");
	}
	int i;
	int j = 0;
	for (i = 0; i < 9999999; i++) {
		j *= i;
	}
	kprintf("Running Test 4:\n");
	if (cbcpuxregister(&CPU600Check, 600) == SYSERR) {
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
	if (cbcpuxregister(&CPU50Check, 50) == SYSERR) {
		kprintf("Test 5: An error occured trying to set callback function\n\n");
	}

	if (cbwallxregister(&WALL4000Check, 4000) == SYSERR) {
		kprintf("Test 6: An error occured trying to set callback function\n\n");
	}

	int i;
	int j = 0;
	for (i = 0; i < 9999999; i++) {
		j *= i;
	}
}

void testFailRegistration() {
	kprintf("Running Test 7:\n");
	kprintf("Expected: Fail\n");
	if (cbcpuxregister(&failRegistrationHelper, 9999999999) == SYSERR) {
		kprintf("Actual: Fail\n\n");
		score += 1;
	} else {
		kprintf("Actual: Pass\n\n");
	}

	kprintf("Running Test 8:\n");
	kprintf("Expected: Fail\n");
	if (cbcpuxregister(&failRegistrationHelper, -10) == SYSERR) {
		kprintf("Actual: Fail\n\n");
		score += 1;
	} else {
		kprintf("Actual: Pass\n\n");
	}
	
	kprintf("Running Test 9:\n");
	kprintf("Expected: Fail\n");
	if (cbcpuxregister(&failRegistrationHelper, cpuusage(currpid) - 1) == SYSERR) {
		kprintf("Actual: Fail\n\n");
		score += 1;
	} else {
		kprintf("Actual: Pass\n\n");
	}

	kprintf("Running Test 10:\n");
	kprintf("Expected: Fail\n");
	if (cbwallxregister(&failRegistrationHelper, ctr1000 - 1) == SYSERR) {
		kprintf("Actual: Fail\n\n");
		score += 1;
	} else {
		kprintf("Actual: Pass\n\n");
	}
}
/* ----------- Robustness Tests End ----------- */

/* ----------- Helper Functions Start ----------- */

void CPU50Check() {
	uint32 usage = cpuusage(currpid);
	kprintf("Expected: 50\nActual: %d\n\n", usage);
	if (usage > 40 && usage < 60) {
		score += 1;
	}
	return;
}

void CPU600Check() {
	uint32 usage = cpuusage(currpid);
	kprintf("Expected: 600\nActual: %d\n\n", usage);
	if (usage > 590 && usage < 610) {
		score += 1;
	}
	return;
}

void CPU4000Check() {
	uint32 usage = cpuusage(currpid);
	kprintf("Expected: 4000\nActual: %d\n\n", usage);
	if (usage > 3990 && usage < 4010) {
		score += 1;
	}
	return;
}

void WALL1000Check() {
	kprintf("Expected: 1000\nActual: %d\n\n", ctr1000);
	if (ctr1000 > 990 && ctr1000 < 1010) {
		score += 1;
	}
	kprintf("Running Test 2:\n");
	if (cbcpuxregister(&WALL2000Check, 2000) == SYSERR) {
		kprintf("Test 2: An error occured trying to set callback function");
	}
	return;
}

void WALL2000Check() {
	kprintf("Expected: 2000\nActual: %d\n\n", ctr1000);
	if (ctr1000 > 1990 && ctr1000 < 2010) {
		score += 1;
	}
	return;
}

void WALL4000Check() {
	kprintf("Running Test 6:\n");
	kprintf("Expected: 4000\nActual: %d\n\n", ctr1000);
	if (ctr1000 > 3990 && ctr1000 < 4010) {
		score += 1;
	}
	return;
}

void failRegistrationHelper() {
	return;
}

/* ----------- Helper Functions End ----------- */