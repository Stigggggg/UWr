_JB_RBX = 0
_JB_RBP = 1
_JB_R12 = 2
_JB_R13 = 3
_JB_R14 = 4
_JB_R15 = 5
_JB_RSP = 6
_JB_RIP = 7

        .text

        .globl Setjmp
        .type Setjmp,@function
Setjmp:
	movq    (%rsp),%r11 //przechowujemy szczyt stosu
	movq    %rbx,(_JB_RBX * 8)(%rdi) //przenosimy kolejne rejestry do jumpbuf
	movq    %rbp,(_JB_RBP * 8)(%rdi)
	movq    %r12,(_JB_R12 * 8)(%rdi)
	movq    %r13,(_JB_R13 * 8)(%rdi)
	movq    %r14,(_JB_R14 * 8)(%rdi)
	movq    %r15,(_JB_R15 * 8)(%rdi)
	movq    %rsp,(_JB_RSP * 8)(%rdi)
	movq    %r11,(_JB_RIP * 8)(%rdi) //przenosimy r11 do rip, zebysmy wiedzieli od jakiej instrukcji zaczac po powrocie
	xorl	%eax,%eax
	ret
        .size Setjmp, . - Setjmp
        
        .globl Longjmp
        .type Longjmp,@function
Longjmp:
	movq    (_JB_RBX * 8)(%rdi),%rbx //znowu przenosimy rejestry
	movq    (_JB_RBP * 8)(%rdi),%rbp
	movq    (_JB_R12 * 8)(%rdi),%r12
	movq    (_JB_R13 * 8)(%rdi),%r13
	movq    (_JB_R14 * 8)(%rdi),%r14
	movq    (_JB_R15 * 8)(%rdi),%r15
	movq    (_JB_RSP * 8)(%rdi),%rsp
	movq    (_JB_RIP * 8)(%rdi),%r11 
	movl	%esi,%eax //drugi argument do rax, jesli jest rowny 0, to zmieniamy go na 1
	testl	%eax,%eax //jesli 0, ustaw na 1
	jnz	1f
	incl	%eax
1:	movq	%r11,(%rsp) //stary rip na stos jak wyzej
	ret
        .size Longjmp, . - Longjmp
