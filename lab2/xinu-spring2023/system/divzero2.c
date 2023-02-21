/* divzero2.c - divzero2 */

#include <xinu.h>

static int counter = 0;
void divzero2(void) {
    counter++;
    kprintf("You are trying to divide by 0 - %d times\n", counter);
    if (counter > 10) {
        kill(getpid());
    }
    return;
}