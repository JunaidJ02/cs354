
/* childrennum.c - childrennum */

#include <xinu.h>

syscall childrennum(pid32 pid) {
    struct	procent	*prptr;		/* Pointer to proc. table entry */
    /* Return the number of child processes if any, otherwise SYSERR*/
    prptr = &proctab[pid];
    if (prptr->prstate != PR_FREE) {
        return prptr->pr_children;
    }
    return SYSERR;
}