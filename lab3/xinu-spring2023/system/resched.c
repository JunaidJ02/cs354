/* resched.c - resched, resched_cntl */

#include <xinu.h>

struct	defer	Defer;
volatile extern int msclkcounter2;
volatile extern uint32 currcpu;

/*------------------------------------------------------------------------
 *  resched  -  Reschedule processor to highest priority eligible process
 *------------------------------------------------------------------------
 */
void	resched(void)		/* Assumes interrupts are disabled	*/
{
	struct procent *ptold;	/* Ptr to table entry for old process	*/
	struct procent *ptnew;	/* Ptr to table entry for new process	*/

	/* If rescheduling is deferred, record attempt and return */

	if (Defer.ndefers > 0) {
		Defer.attempt = TRUE;
		return;
	}

	/* Point to process table entry for the current (old) process */
	ptold = &proctab[currpid];

	if (ptold->prstate == PR_CURR)	 { 
		/* Process remains eligible */
		if (ptold->prprio > firstkey(readylist)) {
			/* Reset preempt to how long this proccess deserves */
			#if DYNSCHEDENABLE == 1
				preempt = xdynprio[ptold->prprio].xquantum;
			#endif
			return;
		}

		/* Save the quantum if there is any left */
			if (preempt != 0) {
				ptold->prquantum = preempt;
			}

		/* Old process will no longer remain current */	
		ptold->prstate = PR_READY;
		ptold->prbeginready = msclkcounter2;
		insert(currpid, readylist, ptold->prprio);
	}

	/* Update prcpu */
	ptold->prcpu = ptold->prcpu + currcpu;

	/* Force context switch to highest priority ready process */
	currpid = dequeue(readylist);
	ptnew = &proctab[currpid];
	ptnew->prstate = PR_CURR;
	
	ptnew->prresptime += (msclkcounter2 - ptnew->prbeginready == 0 ? 1 : msclkcounter2 - ptnew->prbeginready);

	preempt = QUANTUM;
	#if DYNSCHEDENABLE == 1
		/* If a process with higher priorty took over this process before, give the timeslice it had left back*/
		if (ptnew->prquantum != 0) {
			preempt = ptnew->prquantum;
			ptnew->prquantum = 0;
		} else {
			preempt = xdynprio[ptnew->prprio].xquantum;		/* Reset time slice for process	*/
		}
	#endif

	/* Update prctxswcount */
	ptnew->prctxswcount++;
	currcpu = 0;

	ctxsw(&ptold->prstkptr, &ptnew->prstkptr);

	/* Old process returns here when resumed */
	return;
}

/*------------------------------------------------------------------------
 *  resched_cntl  -  Control whether rescheduling is deferred or allowed
 *------------------------------------------------------------------------
 */
status	resched_cntl(		/* Assumes interrupts are disabled	*/
	  int32	defer		/* Either DEFER_START or DEFER_STOP	*/
	)
{
	switch (defer) {

	    case DEFER_START:	/* Handle a deferral request */

		if (Defer.ndefers++ == 0) {
			Defer.attempt = FALSE;
		}
		return OK;

	    case DEFER_STOP:	/* Handle end of deferral */
		if (Defer.ndefers <= 0) {
			return SYSERR;
		}
		if ( (--Defer.ndefers == 0) && Defer.attempt ) {
			resched();
		}
		return OK;

	    default:
		return SYSERR;
	}
}
