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

		sti			# Restore interrupt status
		popal			# Restore registers

		# Check if there is a call back functiona associated with the process
		cmpl $0, globalCBF 
		jne cfb

		iret			# Return from interrupt

# If there was no call back function, just call iret
cfb:
		# Save the current eax
		movl %eax, globalEAX
		movl %ebx, globalEBX
		movl %ecx, globalECX
		
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

		# Reset the global call back function to nil
		movl $0, globalCBF

		# Reset all the registers back to their original values
		movl globalEAX, %eax
		movl globalEBX, %ebx
		movl globalECX, %ecx
		
		iret			# Return from interrupt
