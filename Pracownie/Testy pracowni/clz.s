.text
.globl clz
.type clz, @function

clz:
        xor %eax,%eax
        movq %rdi,%rax
        shrq %rdi
        orq %rax,%rdi
        movq %rdi,%rax
        shrq $2,%rax
        orq %rdi,%rax
        movq %rax,%rdi
        shrq $4,%rdi
        orq %rax,%rdi
        movq %rdi,%rdx
        shrq $8,%rdx
        orq %rdi,%rdx
        movq %rdx,%rax
        shrq $16,%rax
        orq %rdx,%rax
        notq %rax
        movq %rax,%rdx
        andq mask1(%rip),%rdx
        shrq %rax
        andq mask1(%rip),%rax
        addq %rax,%rdx
        movq %rdx,%rax
        andq mask2(%rip),%rax
        shrq $2,%rdx
        andq mask2(%rip),%rdx
        addq %rdx,%rax
        movq %rax,%rdx
        andq mask3(%rip),%rdx
        shrq $4,%rax
        andq mask3(%rip),%rax
        addq %rax,%rdx
        movq %rdx,%rax
        andq mask4(%rip),%rax
        shrq $8,%rdx
        andq mask4(%rip),%rdx
        addq %rdx,%rax
        movq %rax,%rdx
        andq mask5(%rip),%rdx
        shrq $16,%rax
        andq mask5(%rip),%rax
        addq %rax,%rdx
        movl %edx,%eax
        shrq $32,%rdx
        addq %rdx,%rax
        ret

    .data
mask1: .quad 0x5555555555555555
mask2: .quad 0x3333333333333333
mask3: .quad 0x0F0F0F0F0F0F0F0F
mask4: .quad 0x00FF00FF00FF00FF
mask5: .quad 0x0000FFFF0000FFFF
