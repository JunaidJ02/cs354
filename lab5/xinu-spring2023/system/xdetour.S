/* xdetour.s - xdetour (x86) */

/*------------------------------------------------------------------------
 * xdetour  - 
 *------------------------------------------------------------------------
 */
#include <icu.s>
    .text
    .globl	xdetour		# Clock interrupt dispatcher
    
xdetour:
    cli 

    call test1
    
    cmpl $0, globalCPUCBF
    jne cpuDetour

    cmpl $0, globalWALLCBF 
    jne wallDetour

    sti
    ret

cpuDetour:
    # Push the call back function onto the stack
    call globalCPUCBF

    # Reset the global call back function to nil
    movl $0, globalCPUCBF

    # Add WALLX callback function if both are present
    cmpl $0, globalWALLCBF
    jne addWallDetour
    
    sti
    ret

addWallDetour:
    # trigger the call back function onto the stack
    call globalWALLCBF

    # Reset the global call back function to nil
    movl $0, globalWALLCBF

    sti
    ret

wallDetour:
    # Push the call back function onto the stack
    call globalWALLCBF

    # Reset the global call back function to nil
    movl $0, globalWALLCBF

    sti
    ret

