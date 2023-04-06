/*  main.c  - main */

#include <xinu.h>

void testBonus(void);
void childProcess(void);

process main(void)
{
    recvclr();
    resume(create(testBonus, INITSTK, 20, "Bonus function check", 0));
    return OK;
    
}

void testBonus(void) {
    if (cbchildregister(&childcb) == SYSERR) {
        #if XINUDEBUG == 1
            kprintf("\n Failed to setup callback function\n");
        #endif
        return;
    }

    resume(create(childProcess, INITSTK, 20, "child process doing nothing", 0));
    
    mynonreentrant();
}

void childProcess(void) {
    return;
}