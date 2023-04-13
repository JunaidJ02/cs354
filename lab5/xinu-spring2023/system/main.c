/*  main.c  - main */

#include <xinu.h>
void cpuCallback(void);
void wallCallback(void);

process	main(void)
{
	kprintf("good!\n"); 
	if (cbcpuxregister(&cpuCallback, 100) == SYSERR) {
		kprintf("An error occured while trying to set cpu callback function");
	}

	if (cbwallxregister(&wallCallback, 2000) == SYSERR) {
		kprintf("An error occured while trying to set wall callback function");
	}

	while(1);
	return OK;   
}

void cpuCallback(void) {
	kprintf("inside cpu callback function\n");
	return;
}

void wallCallback(void) {
	kprintf("inside wall callback function %d\n", clktime);
	return;
}
