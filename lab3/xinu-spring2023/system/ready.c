/* ready.c - ready */

#include <xinu.h>

qid16	readylist;			/* Index of ready list		*/
volatile extern int msclkcounter2;
/*------------------------------------------------------------------------
 *  ready  -  Make a process eligible for CPU service
 *------------------------------------------------------------------------
 */
status	ready(
	  pid32		pid		/* ID of process to make ready	*/
	)
{
	register struct procent *prptr;

	if (isbadpid(pid)) {
		return SYSERR;
	}

	/* Set process state to indicate ready and add to ready list */
	prptr = &proctab[pid];
	prptr->prbeginready = msclkcounter2;
	prptr->prstate = PR_READY;
	insert(pid, readylist, prptr->prprio);
	resched();

	return OK;
}
