#include <xinu.h>

/*
    Arguments: 
        - call: 0 - Blocking call, 1 - Non-blocking call
        - cpid: The pid of the child process
    If call == 0:
        - It will act as a blocking call
        - Wait for the child process to finish and then return cpid
    If call == 1:
        - It will act as a non blocking call
        - If the child process is complete, return cpid
*/
syscall xchildwait(uint16 call, pid32 cpid) {
    struct procent *prchild; /* Parent process */
    struct procent *prparent; /* Child process */
    if (!isbadpid(cpid)) { /* Confirm that its a valid PID */
        prparent = &proctab[currpid]; /* Get parent process */
        prchild = &proctab[cpid]; /* Get child process */
        if (call == 0) { /* Blocking call */
            if (cpid > 0) { /* Check that its not the null process */
                prparent->prstate = PR_CHLDWAIT; /* Set parents status to waiting on child */
                prparent->prchildstatus[cpid] = 2; /* Set child status to 2, child has not terminated and parent made a blocking call */
                resume(cpid); /* Resume the child process */
                return cpid; /* Once the child process is complete, return the child process PID to the parent process */
            }
        } else if (call == 1) { /* Non blocking call */
            if (prchild->prstate == PR_FREE) { /* If the child has already been terminated */
                return cpid; /* Return the child process PID */
            }
        }
    }
    return SYSERR; /* An error occured, return SYSERR */
}