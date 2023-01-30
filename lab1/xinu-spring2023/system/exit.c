/* exit.c - exit */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  exit  -  Cause the calling process to exit
 *------------------------------------------------------------------------
 */
void	exit(void)
{
	prptr = &proctab[getpid()];
	parentptr = &proctab[prptr->prparent];
	if (parentptr->prstate != PR_FREE) {
		parentptr->pr_children -= 1;
    }
	
	kill(getpid());		/* Kill the current process */
}
