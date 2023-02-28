/* xkill.c - xkill */

#include <xinu.h>

syscall xkill(pid32 pid) {
    syscall retval;
    asm("movl %1, %%ebx;\n\t"
        "movl %2, %%eax;\n\t"
        "int $46;\n\t"
        "movl %%eax, %0;\n\t"
        : "=m" (retval)
        : "g" (pid), "g" (22)
        : "eax", "ebx");
    return retval;
}