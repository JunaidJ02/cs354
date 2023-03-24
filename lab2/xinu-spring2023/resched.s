	.file	"resched.c"
	.text
	.comm	Defer,8,8
	.globl	resched
	.type	resched, @function
resched:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	Defer(%rip), %eax
	testl	%eax, %eax
	jle	.L2
	movb	$1, 4+Defer(%rip)
	jmp	.L1
.L2:
	movl	currpid(%rip), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	leaq	proctab(%rip), %rdx
	addq	%rdx, %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movzwl	(%rax), %eax
	cmpw	$1, %ax
	jne	.L4
	movq	-16(%rbp), %rax
	movzwl	2(%rax), %eax
	movswl	%ax, %edx
	movzwl	readylist(%rip), %eax
	cwtl
	cltq
	leaq	0(,%rax,8), %rcx
	leaq	4+queuetab(%rip), %rax
	movzwl	(%rcx,%rax), %eax
	cwtl
	cltq
	leaq	0(,%rax,8), %rcx
	leaq	queuetab(%rip), %rax
	movl	(%rcx,%rax), %eax
	cmpl	%eax, %edx
	jg	.L6
	movq	-16(%rbp), %rax
	movw	$2, (%rax)
	movq	-16(%rbp), %rax
	movzwl	2(%rax), %eax
	movswl	%ax, %edx
	movzwl	readylist(%rip), %eax
	movswl	%ax, %ecx
	movl	currpid(%rip), %eax
	movl	%ecx, %esi
	movl	%eax, %edi
	call	insert@PLT
.L4:
	movzwl	readylist(%rip), %eax
	cwtl
	movl	%eax, %edi
	call	dequeue@PLT
	movl	%eax, currpid(%rip)
	movl	currpid(%rip), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	leaq	proctab(%rip), %rdx
	addq	%rdx, %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movw	$1, (%rax)
	movl	$150, preempt(%rip)
	movq	-8(%rbp), %rax
	leaq	8(%rax), %rdx
	movq	-16(%rbp), %rax
	addq	$8, %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ctxsw@PLT
	jmp	.L1
.L6:
	nop
.L1:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	resched, .-resched
	.globl	resched_cntl
	.type	resched_cntl, @function
resched_cntl:
.LFB1:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	cmpl	$1, -4(%rbp)
	je	.L8
	cmpl	$2, -4(%rbp)
	je	.L9
	jmp	.L15
.L8:
	movl	Defer(%rip), %eax
	leal	1(%rax), %edx
	movl	%edx, Defer(%rip)
	testl	%eax, %eax
	jne	.L11
	movb	$0, 4+Defer(%rip)
.L11:
	movl	$1, %eax
	jmp	.L12
.L9:
	movl	Defer(%rip), %eax
	testl	%eax, %eax
	jg	.L13
	movl	$-1, %eax
	jmp	.L12
.L13:
	movl	Defer(%rip), %eax
	subl	$1, %eax
	movl	%eax, Defer(%rip)
	movl	Defer(%rip), %eax
	testl	%eax, %eax
	jne	.L14
	movzbl	4+Defer(%rip), %eax
	testb	%al, %al
	je	.L14
	call	resched
.L14:
	movl	$1, %eax
	jmp	.L12
.L15:
	movl	$-1, %eax
.L12:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	resched_cntl, .-resched_cntl
	.ident	"GCC: (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
