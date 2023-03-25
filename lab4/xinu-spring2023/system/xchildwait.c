#include <xinu.h>

syscall xchildwait(uint16 call, pid32 cpid) {
    struct procent *prchild;
    struct procent *prparent;
    // Blocking call
    if (!isbadpid(cpid)) {
        prparent = &proctab[currpid];
        prchild = &proctab[cpid];
        if (call == 0) {
            if (cpid > 0) {
                prparent->prstate = PR_CHLDWAIT;
                prparent->prchildstatus[cpid] = 2;
                resume(cpid);
                kprintf("\nReturning from xchildwait()\n");
                return cpid;
            }
        // Non Blocking call
        } else if (call == 1) {
            if (prchild->prstate == PR_FREE) {
                return cpid;
            }
        }
    }
    
    return SYSERR;
}