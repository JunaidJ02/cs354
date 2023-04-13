#include <xinu.h>

syscall cbwallxregister(void (* cbf) (void), uint32 wallthr) {
    uint32 startText = (uint32)&text;
    uint32 endText =  (uint32)&etext - 1;
    uint32 cbfAddress = (uint32)&cbf;
  
    /* Get the current process */
    struct procent *prptr = &proctab[currpid];
    /* Confirm that the requested threshold is above the current clktime */
    if (ctr1000 < wallthr) {
        /* Update the threshold for when we trigger the callback function*/
        prptr->wallthreshold = wallthr;
        /* Set the callback function that will be triggered when clktime is above threshold */
        prptr->wallCBF = cbf;
        /* Successfully set the callback function and threshold */
        return 0;
    }
    #if XINUDEBUG == 1
        kprintf("[WALLX] Requested threshold (%d) is above clktime (%d)\n", wallthr, clktime);
    #endif
    return SYSERR;
}

