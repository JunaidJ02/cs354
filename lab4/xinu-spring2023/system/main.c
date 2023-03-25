/*  main.c  - main */

#include <xinu.h>

void wasteTime(void);
void testXChildWaitBlocking(void);

process	main(void)
{
	recvclr();
	resume(create(testXChildWaitBlocking, INITSTK, 16, "Child process", 0));

	return OK;
    
}

/* Passes */
void testXChildWaitBlocking(void) {
	/* Create a child process */
	pid32 childProcess = create(wasteTime, INITSTK, 15, "Child process", 0);
	/* Call xchildwait() as a blocking call and pass in the created child processes PID */
	pid32 returnVal = xchildwait(0, childProcess);
	kprintf("\nPID: %d\n", returnVal);
	/* Check to make sure that xchildwait() returns the child PID only after the child process has terminated*/
	kprintf("\nDone with test, we should expect Done wasting time to be printed first and then the PID of the child process\n");
}

void wasteTime(void) {
	kprintf("\nEntered wasteTime()\n");
	int i;
	int j = 0;
	for (i = 0; i < 999999; i++) {
		j *= i;
	}
	kprintf("\nDone wasting time\n");
	return;
}