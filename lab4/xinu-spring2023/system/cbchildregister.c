#include <xinu.h>

/*
    Register a call back function for the current process.
    The call back function will get called whenever a child process of this process is terminated 
    
    Arguments: 
    cbf - The call back function
*/

syscall cbchildregister(void (* cbf) (void)) {
    struct procent *prchild; /* Child process */
    prchild = &proctab[getpid()]; /* Get child process */
    /* Confirm that there is not a call back function already saved */
    if (prchild->cbf == NULL) {
        /* Set the processes call back function to the one passed in*/
        prchild->cbf = cbf;
        /* Successfully set the call back function, return 0 */
        return 0;
    } 
    /* If a call back function has been registered and we try to set it again, return SYSERR*/
    return SYSERR;
}