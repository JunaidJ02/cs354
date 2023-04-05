/* clkdisp.s - clkdisp (x86) */

/*------------------------------------------------------------------------
 * clkdisp  -  Interrupt dispatcher for clock interrupts (x86 version)
 *------------------------------------------------------------------------
 */
#include <icu.s>

		.data
		.extern globalCBF
		.extern globalEAX
		.extern globalEBX
		.extern globalECX

		.text
		.globl	clkdisp		# Clock interrupt dispatcher
clkdisp:
		pushal			# Save registers
		cli			# Disable further interrupts
		movb	$EOI,%al	# Reset interrupt
		outb	%al,$OCW1_2

		call	clkhandler	# Call high level handler

		sti			# Restore interrupt status
		popal			# Restore registers

		cmpl $0, globalCBF 
		je no_cfb

		# Save the current eax
		mov globalEAX, %eax
		mov globalEBX, %ebx
		mov globalECX, %ecx
		
		# Get the EIP and save it in eax
		pop %eax
		# Get the CS and save it in ebx
		pop %ebx
		# Get the EFLAGS and save it in ecx
		pop %ecx

		# Push the EIP onto the stack
		pushl %eax
		# Push the EFLAGS onto the stack
		pushl %ecx
		# Push the CS onto the stack
		pushl %ebx
		
		# Push the call back function onto the stack
		mov globalCBF, %eax
		pushl %eax

		movl $0, globalCBF

		# Reset all the registers back to their original values
		movl globalEAX, %eax
		movl globalEBX, %ebx
		movl globalECX, %ecx
		
		iret			# Return from interrupt

no_cfb:
	iret
