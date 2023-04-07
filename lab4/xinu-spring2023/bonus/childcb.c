#include <xinu.h>

void childcb(void) {
    // Perform some callback operation
    #if XINUDEBUG == 1
        kprintf("Callback: Performing operation\n");
    #endif

    // Call mynonreentrant()
    mynonreentrant();

    #if XINUDEBUG == 1
        kprintf("Callback: Finished\n");
    #endif
}