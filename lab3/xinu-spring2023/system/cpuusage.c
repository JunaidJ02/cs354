#include <xinu.h>

syscall cpuusage(pid32 pid) {
    if (isbadpid(pid)) {
		return SYSERR;
	}
    
    struct	procent	*prptr;
    prptr = &proctab[pid];
    
    if (prptr->prstate == PR_CURR) {
        return prptr->prcpu + currcpu;
    } else {
        return prptr->prcpu;
    }

}