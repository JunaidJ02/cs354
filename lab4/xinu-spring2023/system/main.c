/*  main.c  - main */

#include <xinu.h>

void wasteTime(void);
void testXChildWaitBlocking(void);
void testXChildWaitNonBlocking(void);
void testAsyncChildCallbackFunction(void);
void callbackFunction(void);

pid32 childFunctionPID = 0;

process main(void)
{
    recvclr();

    // resume(create(testXChildWaitBlocking, INITSTK, 16, "Child process", 0));
    // resume(create(testXChildWaitNonBlocking, INITSTK, 20, "Non blocking check", 0));
    resume(create(testAsyncChildCallbackFunction, INITSTK, 20, "Async callback function check", 0));

    return OK;
    
}

/* Passes */
void testXChildWaitBlocking(void) {
    /* Create a child process */
    pid32 childProcess1 = create(wasteTime, INITSTK, 15, "Child process", 0);
    pid32 childProcess2 = create(wasteTime, INITSTK, 15, "Child process", 0);
    /* Call xchildwait() as a blocking call and pass in the created child processes PID */
    pid32 returnVal1 = xchildwait(0, childProcess1);
    pid32 returnVal2 = xchildwait(0, childProcess2);
    kprintf("\nPID 1: %d\n", returnVal1);
    kprintf("\nPID 2: %d\n", returnVal2);
    /* Check to make sure that xchildwait() returns the child PID only after the child process has terminated*/
    kprintf("\nDone with test, we should expect Done wasting time to be printed first and then the PID of the child process\n");
}

/* Passes */
void testXChildWaitNonBlocking(void) {
    // Create a child process
    pid32 cpid = create(wasteTime, 1024, 21, "Child Process", 0);

    if (cpid == SYSERR) { kprintf("\nError: Failed to create child process.\n"); }

    // Call xchildwait() with non-blocking mode (1) before the child process completes
    pid32 result = xchildwait(1, cpid);
    kprintf("\nFirst call to xchildwait, expected: %d - acutal: %d\n", SYSERR, result);

	resume(cpid);

    // Call xchildwait() with non-blocking mode (1) after the child process completes
    result = xchildwait(1, cpid);
    kprintf("\nSecond call to xchildwait, expected: %d - acutal: %d\n", cpid, result);
}

void wasteTime(void) {
    kprintf("\nEntered wasteTime()\n");
    int i;
    int j = 0;
    for (i = 0; i < 9999999; i++) {
        j *= i;
    }
    kprintf("\nDone wasting time\n");
}

void wasteMoreTime(void) {
    kprintf("\nEntered wasteMoreTime()\n");
    int i;
    int j = 0;
    for (i = 0; i < 99999999; i++) {
        j *= i;
    }
    kprintf("\nDone wasting time\n");
}

void testAsyncChildCallbackFunction(void) {
    if (cbchildregister(&callbackFunction) == SYSERR) {
        kprintf("\n Failed to setup callback function\n");
        return;
    }

    childFunctionPID = create(wasteTime, 1024, 20, "waste time", 0);
    resume(childFunctionPID);
    while (1);
}

void callbackFunction(void) {
    int x;
    x = xchildwait(1, childFunctionPID);
    kprintf("Child process %d has terminated.\n", x);
}
