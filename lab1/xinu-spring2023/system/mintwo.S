# Username: javedj

/* Simple code to find min of two integers passed to mintwo() coded
	in AT&T assembly. Assumes caller follows CDECL. */

        .text
        .globl mintwo

mintwo:
        # Save register values on the stack
        pushl   %ebp
        movl    %esp, %ebp
        pushfl
        pushl   %ebx   

        # Load the two arguments into registers
        movl    8(%ebp), %eax
        movl    12(%ebp), %ebx

        # Compare the values
        cmpl    %eax, %ebx

        # Jump to L2 if %ebx is the min number
        jge     .L2
        # Otherwise swap so %ebx is the min number
        movl    %ebx, %eax
    .L2:
        # Reset the stack pointers 
        popl    %ebx
        popfl
        movl    (%esp),%ebp
        add     $4,%esp
        ret