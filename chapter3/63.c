/* Asm for the code
 switch_prob(long, long):
        subq    $65, %rsi
        cmpq    $5, %rsi
        ja      .L2
        jmp     *.L4(,%rsi,8)
.L4:
        .quad   .L8
        .quad   .L2
        .quad   .L7
        .quad   .L6
        .quad   .L5
        .quad   .L3
.L8:
        leaq    0(,%rdi,8), %rax
        ret
.L7:
        leaq    0(,%rdi,8), %rax
        ret
.L6:
        movq    %rdi, %rax
        sarq    $3, %rax
        ret
.L5:
        movq    %rdi, %rax
        salq    $4, %rax
        subq    %rdi, %rax
        movq    %rax, %rdi
.L3:
        imulq   %rdi, %rdi
.L2:
        leaq    75(%rdi), %rax
        ret
*/

long switch_prob(long x, long n) {
    long result = x;

    switch(n) {
        case 65:
        case 67:
            result = 8 * x;
            break;
        case 68:
            result >>= 3;
            break;
        case 69:
            result <<= 4;
            result -= x;
            x = result;
        case 70:
            x = x * x;
        default:
            result = x + 75;
            break;

    }
    return result;
}
