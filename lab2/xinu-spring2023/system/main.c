/*  main.c  - main */

#include <xinu.h>

void test(void);
void testDivzero1(void);
void testDivzero2(void);
void testChildrenNum(void);
void testChprio(void);
void testSleepms(void);
void testKill(void);
void testKillHelper(void);

process	main(void)
{
	/* Run the Xinu shell */
	kprintf("\nExecuting main() by test process: %d\n", getpid());

	recvclr();

	#ifdef XINUDEBUG
	testKill();
	testChildrenNum();
	testChprio();
	testSleepms();
	/* Test divzero1 */
	// testDivzero1();
	/* Test divzero2 */
	testDivzero2();
	#endif

	return OK;    
}

void testKill(void) {
	kprintf("\n----Kill Test----\n");
	/* Create some test processes */
	pid32 process1 = create((void *)testKillHelper, INITSTK, 10, "test process", 0, NULL);
	pid32 process2 = create((void *)testKillHelper, INITSTK, 10, "test process", 0, NULL);
	pid32 process3 = create((void *)testKillHelper, INITSTK, 10, "test process", 0, NULL);
	pid32 process4 = create((void *)testKillHelper, INITSTK, 10, "test process", 0, NULL);

	/* Kill all test processes */
	xkill(process1);
	kprintf("1: Passed");
	xkill(process2);
	kprintf("2: Passed");
	xkill(process3);
	kprintf("3: Passed");
	xkill(process4);
	kprintf("4: Passed");
	kprintf("----Kill Test----\n");
}

void testDivzero1(void) {
	kprintf("\n----Test Divzero 1----\n");
	kprintf("1: Expect it to hang\n");
	int r, s = 5;
	r = s / 0;
	kprintf("----Test Divzero 1----\n");
}

void testDivzero2(void) {
	kprintf("\n----Test Divzero 2----\n");
	kprintf("1:Expect it print divide by 0 - 1\n");
	asm("int $0");
	kprintf("1:Expect it print divide by 0 - 2\n");
	asm("int $0");
	kprintf("1:Expect it print divide by 0 - 3 through 11 and then hang\n");
	int r, s = 5;
	r = s / 0;
	kprintf("----Test Divzero 2----\n");
	return;
}

void testChildrenNum(void) {
	kprintf("\n----Num Children Tests----\n");
	pid32 process1 = create((void *)test, INITSTK, 15, "test process", 0, NULL);
	
	int testChildrenNum1 = xchildrennum(getpid());
	kprintf("1:Expexted 1 - Actual %d\n", testChildrenNum1);
	pid32 process2 = create((void *)test, INITSTK, 15, "test process", 0, NULL);
	pid32 process3 = create((void *)test, INITSTK, 15, "test process", 0, NULL);
	
	int testChildrenNum2 = xchildrennum(getpid());
	kprintf("2:Expexted 3 - Actual %d\n", testChildrenNum2);
	
	resume(process1);
	int testChildrenNum3 = xchildrennum(getpid());
	kprintf("3:Expexted 2 - Actual %d\n", testChildrenNum3);
	
	resume(process2);
	resume(process3);
	int testChildrenNum4 = xchildrennum(getpid());
	kprintf("4:Expexted 0 - Actual %d\n", testChildrenNum4);
	kprintf("----Num Children Tests----\n");
}

void testChprio(void) {
	kprintf("\n----Change Priority Tests----\n");
	/* 
		Change priority to 4 so we know what the oldPrio will be 
		oldPrio is the return value of xchprio() and chprio()
	*/
	xchprio(getpid(), 4);
	int testChprio1 = xchprio(getpid(), 5);
	kprintf("1:Expexted 4 - Actual %d\n", testChprio1);

	int testChprio2 = xchprio(getpid(), 6);
	kprintf("2:Expexted 5 - Actual %d\n", testChprio2);

	int testChprio3 = xchprio(getpid(), 7);
	kprintf("3:Expexted 6 - Actual %d\n", testChprio3);

	int testChprio4 = xchprio(getpid(), 8);
	kprintf("4:Expexted 7 - Actual %d\n", testChprio4);

	kprintf("----Change Priority Tests----\n");
}

void testSleepms(void) {
	kprintf("\n----Sleep MS----\n");
	
	kprintf("Start - Sleeping for 0.1 second\n");
	xsleepms(100);
	kprintf("Awake! - Sleeping for 0.2 seconds\n");
	xsleepms(200);
	kprintf("Awake! - Sleeping for 0.3 seconds\n");
	xsleepms(300);
	kprintf("Awake!\n");

	kprintf("----Sleep MS----\n");
}

void test(void) {
	return;
}

void testKillHelper(void) {
	xkill(getpid());
}