/* xdetour.s - xdetour (x86) */

/*------------------------------------------------------------------------
 * xdetour  - 
 *------------------------------------------------------------------------
 */
#include <icu.s>
    .text
    .globl	xdetour		# Clock interrupt dispatcher
xdetour:
        cmpl $0, globalCBF 
        jne cpuDetour

        ret             # Remove xdetour from stack and return to clkdisp

cpuDetour:

    # Save the current registers
    movl %eax, globalEAX
    movl %ebx, globalEBX
    movl %ecx, globalECX
    movl %edx, globalEDX

    # Get the next instruction and save it in eax
    pop %eax
    # Get the EIP and save it in ebx
    pop %ebx
    # Get the CS and save it in ecx
    pop %ecx
    # Get the EFLAGS and save it in edx
    pop %edx

    # Push the EIP onto the stack
    pushl %ebx
    # Push the EFLAGS onto the stack
    pushl %edx
    # Push the CS onto the stack
    pushl %ecx
    
    
    # Push the call back function onto the stack
    mov globalCBF, %ebx
    pushl %ebx

    # Reset the global call back function to nil
    movl $0, globalCBF
    
    # Push the next instruction
    pushl %eax

    # Reset all the registers back to their original values
    movl globalEAX, %eax
    movl globalEBX, %ebx
    movl globalECX, %ecx
    movl globalEDX, %edx

    ret             # Remove xdetour from stack and return to clkdisp

