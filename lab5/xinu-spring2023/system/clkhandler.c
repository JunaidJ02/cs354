/* clkhandler.c - clkhandler */

#include <xinu.h>

/*------------------------------------------------------------------------
 * clkhandler - high level clock interrupt handler
 *------------------------------------------------------------------------
 */
volatile extern uint32 currcpu;
extern  void (*globalCPUCBF)(void);
extern  void (*globalWALLCBF)(void);
void	clkhandler()
{
	static	uint32	count1000 = 1000;	/* Count to 1000 ms	*/

	/* Increment the curr cpu usage time */
	currcpu++;
	ctr1000++;

	/* Trigger callback function if cpu usage is above threshold */
	struct procent *prptr = &proctab[currpid];
	if (prptr->cpuCBF != NULL && prptr->prcpu + currcpu >= prptr->cputhreshold) {
		kprintf("Triggering cpux callback function\n");
		globalCPUCBF = prptr->cpuCBF;
		prptr->cpuCBF = NULL;
	}

	if (prptr->wallCBF != NULL && ctr1000 >= prptr->wallthreshold) {
		kprintf("Triggering wallx callback function\n");
		globalWALLCBF = prptr->wallCBF;
		prptr->wallCBF = NULL;
	}
	
	/* Decrement the ms counter, and see if a second has passed */
	if((--count1000) <= 0) {

		/* One second has passed, so increment seconds count */

		clktime++;

		/* Reset the local ms counter for the next second */

		count1000 = 1000;
	}

	/* Handle sleeping processes if any exist */

	if(!isempty(sleepq)) {

		/* Decrement the delay for the first process on the	*/
		/*   sleep queue, and awaken if the count reaches zero	*/

		if((--queuetab[firstid(sleepq)].qkey) <= 0) {
			wakeup();
		}
	}

	/* Decrement the preemption counter, and reschedule when the */
	/*   remaining time reaches zero			     */

	if((--preempt) <= 0) {
		preempt = QUANTUM;
		resched();
	}
}
