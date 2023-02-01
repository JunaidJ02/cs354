/*  main.c  - main */

#include <xinu.h>

void sndch(char ch);
extern int msclkcounter1;
extern int msclkcounter2;

process	main(void)
{
	/* Run the Xinu shell */

	kprintf("\nExecuting main() by test process: %d\n", getpid());

	recvclr();

	// Used for 3.2 - Process priority
	resume( create(sndch, 1024, 20, "send A", 1, 'A') );
	resume( create(sndch, 1024, 20, "send B", 1, 'B') );
	
	// Used for 4.1 - Testing clock interupts
	// resume(create(printCounters, 1024, 50, "print counters", 0));

	/* Wait for shell to exit and recreate it */

	// while (TRUE) {
	// 	receive();
	// 	sleepms(200);
	// 	kprintf("\n\nMain process recreating shell\n\n");
	// 	resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	// }
	return OK;
    
}

/*------------------------------------------------------------------------
 * sndch - Output a character on a serial device indefinitely
 *------------------------------------------------------------------------
 */
void sndch(char ch) {
	while (1) {
		kputc(ch);
	}
}

/*----------------------------------------------------------------------------
 * printCounters - Repeatedly prints the two counters we use to test clock interrupts
 *----------------------------------------------------------------------------
 */
void printCounters(void) {
	while (1) {
		kprintf("\nCounter1: %d\n", msclkcounter1);
		kprintf("\nCounter2: %d\n", msclkcounter2);
	}
}
