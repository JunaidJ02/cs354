#include <xinu.h>

volatile extern int msclkcounter2;
void iobnd9(void) {
    int startTime = msclkcounter2;
    while (msclkcounter2 - startTime < STOPPINGTIME) {
		sleepms(0);
	}
    #ifdef XINUTEST
		kprintf("\nPID: %d, IO-9, CLKCounter: %d, CPU: %d, Response: %d\n", getpid(), msclkcounter2, cpuusage(getpid()), responsetime(getpid()));
	#endif
}