#include <xinu.h>

volatile extern int msclkcounter2;
void iobnd(void) {
    while (msclkcounter2 < STOPPINGTIME) {
        int i;
        for (i = 0; i < 242069; i++) {}
        sleepms(80);
    }

    struct	procent	*prptr;
    prptr = &proctab[currpid];

    #ifdef XINUTEST
        kprintf("\nPID: %d, IO-bound, CLKCounter: %d, CPU: %d, Response: %d, Priority: %d\n", getpid(), msclkcounter2, cpuusage(getpid()), responsetime(getpid()), prptr->prprio);
    #endif
}