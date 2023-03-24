#include <xinu.h>

volatile extern int msclkcounter2;
void chameleon(void) {
	while (msclkcounter2 < STOPPINGTIME) {
		sleepms(0);
	}

	struct	procent	*prptr;
    prptr = &proctab[currpid];

	#ifdef XINUTEST
		kprintf("\nPID: %d, Chameleon, CLKCounter: %d, CPU: %d, Response: %d, Priority: %d\n", getpid(), msclkcounter2, cpuusage(getpid()), responsetime(getpid()), prptr->prprio);
	#endif
}