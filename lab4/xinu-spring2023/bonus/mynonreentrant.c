#include <xinu.h>

void mynonreentrant(void) {
    kprintf("\nStarting mynonreentrant()\n");

    /* Do something to waste time */
    int i;
    for (i = 0; i < 5; i++) {
        kprintf("Computing... %d\n", i);
        sleep(3);
    }

    kprintf("Finished mynonreentrant()\n");
}