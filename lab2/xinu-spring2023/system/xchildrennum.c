
/* xchildrennum.c - xchildrennum */

#include <xinu.h>

syscall xchildrennum(pid32 pid) {
    int32 retval;
    asm("movl %1, %%ebx;\n\t"
        "movl %2, %%eax;\n\t"
        "int $46;\n\t"
        "movl %%eax, %0;\n\t"
        : "=m" (retval)
        : "g" (pid), "g" (10)
        : "eax", "ebx");
    return retval;
}