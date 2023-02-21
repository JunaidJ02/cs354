/* xchprio.c - xchprio */

#include <xinu.h>

syscall xchprio(pid32 pid, pri16 newprio) {
    int32 retval;
    asm("movl %1, %%ecx;\n\t"
        "movl %2, %%ebx;\n\t"
        "movl %3, %%eax;\n\t"
        "int $46;\n\t"
        "movl %%eax, %0;\n\t"
        : "=m" (retval)
        : "g" (pid), "g" (newprio), "g" (14)
        : "eax", "ebx", "ecx");
    return retval;
}