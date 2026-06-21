#include <stdio.h>

unsigned srl(unsigned x, int k) {
    // perform shift arithmetically
    unsigned xsra = (int) x >> k;
    unsigned mask = 0xffffffff << ((sizeof(int) << 3) - k);

    return xsra & ~mask;
}

int sra(int x, int k) {
    // perform shift logically
    int xsrl = (unsigned) x >> k;
    int w = sizeof(int) << 3;
    int sign_mask = 1 << (w - 1);
    int sign = !!(x & sign_mask);
    int mask = (~sign + 1) << (w - k);

    return xsrl | mask;
}

int main() {
    printf("for 32: %u, %d\n", srl(32, 3), sra(32, 3));
    printf("for -32: %u, %d\n", srl(-32, 3), sra(-32, 3));
}
