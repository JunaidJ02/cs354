/* divzero2.c - divzero2 */

#include <xinu.h>

void divzero2(void) {
    static int counter = 0;
    
    counter++;
    
    #ifdef XINUTEST
    kprintf("You are trying to divide by 0 - %d\n", counter);
    #endif

    if (counter > 10) {
        kill(getpid());
    }
    return;
}