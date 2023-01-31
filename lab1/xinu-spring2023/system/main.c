/*  main.c  - main */

#include <xinu.h>

void sndA(void), sndB(void);


process	main(void)
{
	/* Run the Xinu shell */

	kprintf("\nExecuting main() by test process: %d\n", getpid());

	recvclr();
	resume(create(sndA, 1024, 20, "process 1", 0));
	resume(create(sndB, 1024, 20, "process 2", 0));
	// resume(createmod(shell, 69, 8192, 50, "shell", 1, CONSOLE));

	// /* Wait for shell to exit and recreate it */

	// while (TRUE) {
	// 	receive();
	// 	sleepms(200);
	// 	kprintf("\n\nMain process recreating shell\n\n");
	// 	resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	// }
	return OK;
    
}

/*------------------------------------------------------------------------
 * sndA - Repeatedly emit 'A' on the console without terminating 
 *------------------------------------------------------------------------
 */
void sndA(void) {
	while(1) {
		kputc(CONSOLE, 'A');
	}
}

/*------------------------------------------------------------------------
 * sndB - Repeatedly emit 'B' on the console without terminating 
 *------------------------------------------------------------------------
 */
void sndB(void) {
	while(1) {
		kputc(CONSOLE, 'B');
	}
}
