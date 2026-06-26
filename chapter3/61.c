/* even this code produce the correct ouptut asm with -Og flag
 * and x86-64 gcc 16.1 compiler
 * ASM:
 * cread(long*):
 *       testq   %rdi, %rdi
 *       je      .L3
 *       movq    (%rdi), %rax
 *       ret
 * .L3:
 *       movl    $0, %eax
 *       ret
 */

long cread(long *xp) {
    return (xp ? *xp : 0);
}
