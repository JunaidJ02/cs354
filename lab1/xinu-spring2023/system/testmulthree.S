# Username: javedj

/* Simple code to find min of two integers passed to mintwo() coded
	    in AT&T assembly. Assumes caller follows CDECL. */

        .text
        .globl testmulthree

testmulthree:
        # Save register values on the stack
        pushl   %ebp   
        movl    %esp, %ebp
        pushfl
        pushl   %ebx

        # Load arguments into registers
        movl    8(%ebp), %eax
        movl    12(%ebp), %ebx
        movl    16(%ebp), %ecx

        # Push the register values onto the stack for the multhree function
        pushl   %ecx
        pushl   %ebx
        pushl   %eax

        call multhree # Call the function and save result to %eax

        # Reset the stack pointers 
        popl    %ebx
        popl    %ebx
        popl    %ebx
        popl    %ebx
        popfl
        movl    (%esp),%ebp
        add     $4,%esp
        ret