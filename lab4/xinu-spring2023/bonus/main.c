/*  main.c  - main */

#include <xinu.h>

void testBonus(void);
void childProcess(void);
void callbackFunction(void);

process main(void)
{
    recvclr();
    resume(create(testBonus, INITSTK, 20, "Bonus function check", 0));
    return OK;
    
}

void testBonus(void) {
    if (cbchildregister(&callbackFunction) == SYSERR) {
        kprintf("\n Failed to setup callback function\n");
        return;
    }

    resume(create(childProcess, INITSTK, 20, "child process doing nothing", 0));
    
    mynonreentrant();
}

void childProcess(void) {
    return;
}

void callbackFunction(void) {
    // Perform some callback operation
    printf("Callback: Performing operation\n");

    // Call mynonreentrant()
    mynonreentrant();

    printf("Callback: Finished\n");
}

