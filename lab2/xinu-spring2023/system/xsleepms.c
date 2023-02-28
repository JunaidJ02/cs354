/* xsleepms.c - xsleepms */

#include <xinu.h>

syscall xsleepms(int32	delay) {
    syscall retval;
    asm("movl %1, %%ebx;\n\t"
        "movl %2, %%eax;\n\t"
        "int $46;\n\t"
        "movl %%eax, %0;\n\t"
        : "=m" (retval)
        : "g" (delay), "g" (SYSSLP)
        : "eax", "ebx");
    return retval;
}