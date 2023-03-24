#include <xinu.h>

volatile extern int msclkcounter2;

syscall responsetime(pid32 pid) {
    if (isbadpid(pid)) {
		return SYSERR;
	}

    
    struct	procent	*prptr;
    prptr = &proctab[pid];
    uint32 responseTime = prptr->prresptime;
    
    /* A process has become ready but not current */
    if (prptr->prstate == PR_READY && prptr->prctxswcount == 0) {
        return msclkcounter2 - prptr->prbeginready;
    }

    if (prptr->prstate == PR_READY) {
        return (responseTime + msclkcounter2 - prptr->prbeginready) / (prptr->prctxswcount + 1);
    }

    return responseTime / prptr->prctxswcount;
}