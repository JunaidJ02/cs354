#include <xinu.h>

syscall cbcpuxregister(void (* cbf) (void), uint32 cputhr) {
    uint32 startText = (uint32)&text;
    uint32 endText =  (uint32)&etext - 1;
    uint32 cbfAddress = (uint32)&cbf;

    /* Check if threshold is too small or too large and to make sure that the callback function is within text segment */
    // TODO: Add && cbfAddress >= startText && cbfAddress <= endText
    if (cputhr >= 0 && cputhr <= 8000) {    
        /* Get the current process */
        struct procent *prptr = &proctab[currpid];
        /* Get the cpu usage of the current process */
        uint32 currCPUUsage = cpuusage(currpid);
        /* Confirm that the requested threshold is above the current usage of this process */
        if (currCPUUsage < cputhr) {
            /* Update the threshold for when we trigger the callback function*/
            prptr->cputhreshold = cputhr;
            /* Set the callback function that will be triggered when cpu usage is above threshold */
            prptr->cpuCBF = cbf;
            /* Successfully set the callback function and threshold */
            return 0;
        } else {
            kprintf("[CPUX] Requested threshold (%d) is above current cpu usage (%d)\n", cputhr, currCPUUsage);
            return SYSERR;
        }
    } else {
        kprintf("[CPUX] Requested threshold (%d) is too small (0) or too large (8000) or cbdAddress (%08X) is not in text segment (%08X - %08X)\n", cputhr, cbfAddress, startText, endText);
        return SYSERR;
    }

    return SYSERR;
}

