/*  main.c  - main */

#include <xinu.h>

void wasteTime(void);
void wasteMoreTime(void);
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
    testAsyncChildCallbackFunction();

    return OK;
    
}

/* Part 3 - Test making blocking calls to xchildwait() - Passes */
void testXChildWaitBlocking(void) {
    /* Create a child process */
    pid32 childProcess1 = create(wasteTime, INITSTK, 15, "Child process", 0);
    pid32 childProcess2 = create(wasteMoreTime, INITSTK, 15, "Child process", 0);
    resume(childProcess1);
    resume(childProcess2);
    /* Call xchildwait() as a blocking call and pass in the created child processes PID */
    pid32 returnVal1 = xchildwait(0, childProcess1);
    pid32 returnVal2 = xchildwait(0, childProcess2);
    #if XINUDEBUG == 1
        kprintf("\nPID 1: %d\n", returnVal1);
        kprintf("\nPID 2: %d\n", returnVal2);
        /* Check to make sure that xchildwait() returns the child PID only after the child process has terminated*/
        kprintf("\nDone with test, we should expect Done wasting time to be printed first and then the PID of the child process\n");
    #endif
}

/* Part 3 - Test making non-blocking calls to xchildwait() - Passes */
void testXChildWaitNonBlocking(void) {
    // Create a child process
    pid32 cpid = create(wasteTime, 1024, 21, "Child Process", 0);

    if (cpid == SYSERR) {
        #if XINUDEBUG == 1
            kprintf("\nError: Failed to create child process.\n"); 
        #endif
    }

    // Call xchildwait() with non-blocking mode (1) before the child process completes
    pid32 result = xchildwait(1, cpid);
    #if XINUDEBUG == 1
        kprintf("\nFirst call to xchildwait, expected: %d - acutal: %d\n", SYSERR, result);
    #endif

	resume(cpid);

    // Call xchildwait() with non-blocking mode (1) after the child process completes
    result = xchildwait(1, cpid);
    #if XINUDEBUG == 1
        kprintf("\nSecond call to xchildwait, expected: %d - acutal: %d\n", cpid, result);
    #endif
}

/* Part 4 - Tests to ensure that the callback function runs after a child is terminated - Passes */
void testAsyncChildCallbackFunction(void) {
    if (cbchildregister(&callbackFunction) == SYSERR) {
        #if XINUDEBUG == 1
            kprintf("\n Failed to setup callback function\n");
        #endif
        return;
    }

    childFunctionPID = create(wasteTime, 1024, 20, "waste time", 0);
    resume(childFunctionPID);
    #if XINUDEBUG == 1
        kprintf("\nFinished async call back\n");
    #endif
    while (1);
}


/* Helper function for part 4 that acts as the callback function*/
void callbackFunction(void) {
    int x;
    x = xchildwait(0, childFunctionPID);
    #if XINUDEBUG == 1
        kprintf("Child process %d has terminated.\n", x);
    #endif
}

/* Helper functions */

/* Waste some time, around */
void wasteTime(void) {
    #if XINUDEBUG == 1
        kprintf("\nEntered wasteTime()\n");
    #endif
    int i;
    int j = 0;
    for (i = 0; i < 9999999; i++) {
        j *= i;
    }
    #if XINUDEBUG == 1
        kprintf("\nDone wasting time\n");
    #endif
}


/* Waste some more time, around */
void wasteMoreTime(void) {
    #if XINUDEBUG == 1
        kprintf("\nEntered wasteMoreTime()\n");
    #endif
    int i;
    int j = 0;
    for (i = 0; i < 99999999; i++) {
        j *= i;
    }
    #if XINUDEBUG == 1
        kprintf("\nDone wasting time\n");
    #endif
}


