#include<inttypes.h>
typedef unsigned __int128 uint128_t;
void store(uint128_t *dest,uint64_t x,u_int64_t y)
{
    *dest=x*(uint128_t) y;
}

//////////////////////////////////////////

store:
    movq %rsi,%rax
    mulq %rdx
    movq %rax (%rdi)
    movq %rdx,8(%rdi)
    ret

