/*  main.c  - main */

#include <xinu.h>
void nothing(void);

process	main(void)
{
	kprintf("good!\n"); 
	if (cbcpuxregister(&nothing, 100) == SYSERR) {
		kprintf("An error occured while trying to set cpu callback function");
	}

	while(1);
	return OK;   
}

void nothing(void) {
	kprintf("inside callback function\n");
	return;
}
