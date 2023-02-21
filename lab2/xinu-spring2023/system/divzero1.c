/* divzero1.c - divzero1 */

#include <xinu.h>

void divzero1(void) {
    kprintf("You are trying to divide by 0\n");
    kill(getpid());
}