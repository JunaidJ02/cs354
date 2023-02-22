
/* childrennum.c - childrennum */

#include <xinu.h>

/* Pointer to proc. table entry */
struct	procent	*prptr;
syscall childrennum(pid32 pid) {
    
    /* Return the number of child processes if any, otherwise SYSERR*/
    if (pid > 0 && pid >= NPROC) {   
        prptr = &proctab[pid];
        if (prptr->prstate != PR_FREE) {
            return prptr->pr_children;
        }
    }    
    
    return SYSERR;
}