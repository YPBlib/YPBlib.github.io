arith:
    xorq %rsi,%rdi
    leaq (%rdx,%rrx,2),%rax
    salq $4,%rax
    andl $252645135,%edi
    subq %rdi,%rax
    ret