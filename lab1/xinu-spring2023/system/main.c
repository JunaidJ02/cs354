/*  main.c  - main */

#include <xinu.h>

void sndch(char ch);
void test_createmod();
void test_pr_children();
void test_pr_children_valid();
void test_pr_children_error();
void test_addtwo();
void test_mintwo();
void test_multhree();
void printAssertMessage(char *message, bool8 pass);
extern int msclkcounter1;
extern int msclkcounter2;
pid32 orphan_pid; 
pid32 dead_parent_pid;

#ifndef XINUTEST
#define XINUTEST	FALSE
#endif

#ifndef XINUTEST
#define XINUDEBUG	FALSE
#endif

process	main(void)
{
	/* Run the Xinu shell */
	kprintf("\nExecuting main() by test process: %d\n", getpid());

	recvclr();

	#if XINUTEST
		// Tests for createmod
		test_createmod();
		// Tests for pr_children
		test_pr_children();
		// Tests for addtwo
		test_addtwo();
		// Tests for mintwo
		test_mintwo();
		// Tests for multhree
		test_multhree();
	#endif

	return OK;    
}

void test_addtwo() {
	kprintf("\n=======ADDTWO TESTS=======\n");
	// Test adding two number
	int result = addtwo(5, 7);
	// We should expect 12
	printAssertMessage("Test 1", result == (5 + 7));

	// Test adding two number
	result = addtwo(12, 18);
	// We should expect 30
	printAssertMessage("Test 2", result == (12 + 18));

	// Test adding two number
	result = addtwo(-1, 5);
	// We should expect 4
	printAssertMessage("Test 3", result == (-1 + 5));

	// Test adding two number
	result = addtwo(-101, -237);
	// We should expect -338
	printAssertMessage("Test 4", result == (-101 + -237));
}

void test_mintwo() {
	kprintf("\n=======MINTWO TESTS=======\n");
	// Test getting the smaller number
	int result = mintwo(5, 3);
	// We should expect 3
	printAssertMessage("Test 1", result == 3);

	// Test getting the smaller number
	result = mintwo(3, 5);
	// We should expect 3
	printAssertMessage("Test 2", result == 3);

	// Test getting the smaller number
	result = mintwo(10, -10);
	// We should expect -10
	printAssertMessage("Test 3", result == -10);

	// Test getting the smaller number
	result = mintwo(999998, 999997);
	// We should expect 999997
	printAssertMessage("Test 4", result == 999997);
}

void test_multhree() {
	kprintf("\n=======MULTHREE TESTS=======\n");
	int result = testmulthree(1, 2, 3);
	// We should expect 6
	printAssertMessage("Test 1", result == (1 * 2 * 3));

	result = testmulthree(3, 3, 3);
	// We should expect 27
	printAssertMessage("Test 2", result == (3 * 3 * 3));

	result = testmulthree(100, 24, 12);
	// We should expect 28,800
	printAssertMessage("Test 3", result == (100 * 24 * 12));

	result = testmulthree(20, 93, 64);
	// We should expect 119,040
	printAssertMessage("Test 4", result == (20 * 93 * 64));
}

void test_createmod() {
	kprintf("\n=======CREATEMOD TESTS=======\n");
	// Test giving a specific pid that is free
	pid32 createmodA = createmod(sndch, 6, 1024, 17, "test create mod A", 1, 'X');
	// We should expect the pid to be 6
	printAssertMessage("Test 1", createmodA == 6);

	// Test giving 0 as pid 
	pid32 createmodB = createmod(sndch, 0, 1024, 17, "test create mod B", 1, 'X');
	// We should expect the next free pid
	printAssertMessage("Test 2", createmodB > 0); // Check to make sure it is not 0 or -1

	// Test giving a pid that is taken, 6
	pid32 createmodC = createmod(sndch, 6, 1024, 17, "test create mod C", 1, 'X');
	// We should return SYSERR
	printAssertMessage("Test 3", createmodC == -1); // -1 since no pid was assigned

	// Test freeing up pid 6 and assigning it again
	resume(createmodA);
	pid32 createmodD = createmod(sndch, 6, 1024, 17, "test create mod D", 1, 'X');
	// We should expect a pid of 6 to be assigened assigned again
	printAssertMessage("Test 4", createmodD == 6);

	// Test requesting a pid that is out of range of pids
	pid32 createmodE = createmod(sndch, 420, 1024, 17, "test create mod E", 1, 'X');
	// We should get a valid pid
	printAssertMessage("Test 5", createmodE > 0); // Check to make sure it is not 0 or -1
	resume(createmodE);

}

void test_pr_children() {
	resume(createmod(test_pr_children_valid, 0, 1024, 17, "test pr children valid", 0));
	resume(createmod(test_pr_children_error, 0, 1024, 17, "test pr children error", 0));
}

void test_pr_children_valid() {
	kprintf("\n=======PR CHILDREN TESTS=======\n");
	pid32 pidA = createmod(sndch, 0, 1024, 20, "send A", 1, 'X');
	pid32 pidB = createmod(sndch, 0, 1024, 20, "send B", 1, 'X');

	// There should be 2 children
	printAssertMessage("Test 1", childrennum(getpid()) == 2);
	resume(pidA);

	// There should be 1 child
	printAssertMessage("Test 2", childrennum(getpid()) == 1);
	resume(pidB);

	// There should 0 children
	printAssertMessage("Test 3", childrennum(getpid()) == 0);

	pid32 pidC = createmod(sndch, 0, 1024, 20, "send C", 1, 'X');
	pid32 pidD = createmod(sndch, 0, 1024, 20, "send D", 1, 'X');
	pid32 pidE = createmod(sndch, 0, 1024, 20, "send E", 1, 'X');
	pid32 pidF = createmod(sndch, 0, 1024, 20, "send F", 1, 'X');

	// There should 4 children
	printAssertMessage("Test 4", childrennum(getpid()) == 4);

	resume(pidC);
	resume(pidD);
	resume(pidE);

	// There should be 1 child
	printAssertMessage("Test 5", childrennum(getpid()) == 1);

	resume(pidF);

	// Create another process and let its parent process finish. Then check if resuming this will cause any issues
	orphan_pid = createmod(sndch, 0, 1024, 20, "test child process", 1, 'X');
	dead_parent_pid = getpid();

}

void test_pr_children_error() {
	// This should not decrement anything since its parent process has already terminated
	resume(orphan_pid);
	// Should return SYSERR since the process does not exist
	printAssertMessage("Test 6", childrennum(dead_parent_pid) == 65535); // 65535 is SYSERR
}

/*------------------------------------------------------------------------
 * sndch - Output a character on a serial device indefinitely
 *------------------------------------------------------------------------
 */
void sndch(char ch) {
	#if XINUDEBUG == TRUE
		int counter = 0;
		while (counter < 10) {
			kputc(ch);
			counter += 1;
		}
		kputc('\n');
	#endif
}

/*----------------------------------------------------------------------------
 * printCounters - Repeatedly prints the two counters we use to test clock interrupts
 *----------------------------------------------------------------------------
 */
void printCounters(void) {
	while (1) {
		#if XINUDEBUG == TRUE
			kprintf("\nCounter1: %d\n", msclkcounter1);
			kprintf("\nCounter2: %d\n", msclkcounter2);
		#endif
	}
}

void printAssertMessage(char *message, bool8 pass) {
	#if XINUTEST == TRUE
		if (pass) {
			kprintf("\033[1;32m"); 
			kprintf(message); 
		} else {
			kprintf("\033[1;31m"); 
			kprintf(message); 
		}
		kprintf("\033[0m\n");
	#endif
}
