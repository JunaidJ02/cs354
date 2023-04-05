#include <xinu.h>

void mynonreentrant(void) {
    #if XINUDEBUG == 1
        kprintf("\nStarting mynonreentrant()\n");
    #endif

    /* Do something to waste time */
    int i;
    for (i = 0; i < 5; i++) {
        #if XINUDEBUG == 1
            kprintf("Computing... %d\n", i);
        #endif
        sleep(3);
    }
    #if XINUDEBUG == 1
        kprintf("Finished mynonreentrant()\n");
    #endif
}