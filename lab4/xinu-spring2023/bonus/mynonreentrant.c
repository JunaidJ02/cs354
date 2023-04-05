#include <xinu.h>

void mynonreentrant(void) {
    kprintf("\nStarting mynonreentrant()\n");

    // Perform some computation
    int i;
    for (i = 0; i < 5; i++) {
        kprintf("Computing... %d\n", i);
        sleep(3);
    }

    kprintf("Finished mynonreentrant()\n");
}