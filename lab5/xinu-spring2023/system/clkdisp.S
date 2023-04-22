/* clkdisp.s - clkdisp (x86) */

/*------------------------------------------------------------------------
 * clkdisp  -  Interrupt dispatcher for clock interrupts (x86 version)
 *------------------------------------------------------------------------
 */
#include <icu.s>
		.text
		.globl	clkdisp		# Clock interrupt dispatcher
		
clkdisp:
		pushal			# Save registers
		cli			# Disable further interrupts
		movb	$EOI,%al	# Reset interrupt
		outb	%al,$OCW1_2

		call	clkhandler	# Call high level handler

		sti				# Restore interrupt status
		popal			# Restore registers

		# Add xdetour function if cpux requests it
        cmpl $0, globalCPUCBF
        jne detour

		cmpl $0, globalWALLCBF
        jne detour
		
		iret			# Return from interrupt

detour:
		cli

		# Save the current eax
		movl %eax, globalEAX
		movl %ebx, globalEBX
		movl %ecx, globalECX
		
		# Get the EIP and save it in eax
		popl %eax
		# Get the CS and save it in ebx
		popl %ebx
		# Get the EFLAGS and save it in ecx
		popl %ecx

		# Push the EIP onto the stack
		pushl %eax
		# Push the EFLAGS onto the stack
		pushl %ecx
		# Push the CS onto the stack
		pushl %ebx
		
		# Push the call back function onto the stack
		movl (xdetour), %eax # TODO: traps when trying to move to this location
		pushl %eax

		# Reset all the registers back to their original values
		movl globalEAX, %eax
		movl globalEBX, %ebx
		movl globalECX, %ecx
		
		sti
		iret			# Return from interrupt