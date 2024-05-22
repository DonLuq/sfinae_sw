	.file	"test_file_2020.cc"
	.text
	.def	__main;	.scl	2;	.type	32;	.endef
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
.LFB12:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	call	__main
	movl	$2, %edx
	movl	$4, %ecx
	call	_Z1AIjET_S0_S0_
	movl	$0, %eax
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section	.text$_Z1AIjET_S0_S0_,"x"
	.linkonce discard
	.globl	_Z1AIjET_S0_S0_
	.def	_Z1AIjET_S0_S0_;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z1AIjET_S0_S0_
_Z1AIjET_S0_S0_:
.LFB13:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	movl	%edx, 24(%rbp)
	movl	16(%rbp), %eax
	cmpl	24(%rbp), %eax
	jbe	.L4
	movl	16(%rbp), %eax
	jmp	.L6
.L4:
	movl	24(%rbp), %eax
.L6:
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (GNU) 11.2.0"
