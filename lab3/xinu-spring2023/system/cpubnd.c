#include <xinu.h>

volatile extern int msclkcounter2;
void cpubnd(void) {
    int i = 0;
    while (msclkcounter2 < STOPPINGTIME) {
        i++;
    }

    struct	procent	*prptr;
    prptr = &proctab[currpid];

    #ifdef XINUTEST
        kprintf("\nPID: %d, CPU-bound, CLKCounter: %d, CPU: %d, Response: %d, Priority %d\n", getpid(), msclkcounter2, cpuusage(getpid()), responsetime(getpid()), prptr->prprio);
    #endif
    return;
}