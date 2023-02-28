/* divzero1.c - divzero1 */

#include <xinu.h>

void divzero1(void) {
    #ifdef XINUTEST
    kprintf("You are trying to divide by 0\n");
    #endif
    kill(getpid());
}