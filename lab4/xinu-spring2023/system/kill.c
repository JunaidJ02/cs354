/* kill.c - kill */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  kill  -  Kill a process and remove it from the system
 *------------------------------------------------------------------------
 */
syscall	kill(
	  pid32		pid		/* ID of process to kill	*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process's table entry	*/
	int32	i;			/* Index into descriptors	*/
	pid32 currChildPID; /* PID of the current child, used for looping over all children of parent */
	struct	procent *currChild; /* The current child process, used for looping over all children of parent */
	int j;  /* Looping variable */

	mask = disable();
	if (isbadpid(pid) || (pid == NULLPROC)
	    || ((prptr = &proctab[pid])->prstate) == PR_FREE) {
		restore(mask);
		return SYSERR;
	}

	if (--prcount <= 1) {		/* Last user process completes	*/
		xdone();
	}

	send(prptr->prparent, pid);
	for (i=0; i<3; i++) {
		close(prptr->prdesc[i]);
	}
	freestk(prptr->prstkbase, prptr->prstklen);

	switch (prptr->prstate) {
	case PR_CURR:
		prptr->prstate = PR_FREE;	/* Suicide */
		/* Check that the parent is not the null process */
		if (prptr->prparent != 0) {
			/* Get the parent process */
			struct	procent *parentptr;
			parentptr = &proctab[prptr->prparent];
			/* If the parent is waiting on the child to finish*/
			if (parentptr->prchildstatus[pid] == 2) {
				/* Ready the parent process */
				ready(prptr->prparent);
				/* Set the status of the child process to 4, terminated */
				parentptr->prchildstatus[pid] == 4;
			} else if (parentptr->prchildstatus[pid] == 1) {
				/* Set the status of the child process to 3, terminated without blocking */
				parentptr->prchildstatus[pid] = 3;
				/* Reset child so that it is no longer a process in the process list */
				prptr->prstate = PR_FREE;
				prptr->prprio = 0;
				if (prptr->prchildcount != 0) {
					/* Loop over all children of this process */
					for(j = 0; j < NPROC; j++) {
						/* Get the PID and then the child struct */
						currChildPID = prptr->prchildpid[j];
						currChild = &proctab[currChildPID];
						/* Set the parent of the child process to 0 since the parent is now dead */
						currChild->prparent = 0;
					}
				}
			}
		}
		resched();

	case PR_SLEEP:
	case PR_RECTIM:
		unsleep(pid);
		prptr->prstate = PR_FREE;
		break;

	case PR_WAIT:
		semtab[prptr->prsem].scount++;
		/* Fall through */

	case PR_READY:
		getitem(pid);		/* Remove from queue */
		/* Fall through */

	default:
		prptr->prstate = PR_FREE;
	}

	restore(mask);
	return OK;
}
