/*
 * we solve this by calculating the parity (no of 1s) by 
 * divide and conquering. we xor high bits and low bits 
 * until we get 1 bit answer
 */

#include <stdio.h>

int odd_ones(unsigned x) {
    unsigned bit16 = x ^ (x >> 16);
    unsigned bit8 = bit16 ^ (bit16 >> 8);
    unsigned bit4 = bit8 ^ (bit8 >> 4);
    unsigned bit2 = bit4 ^ (bit4 >> 2);
    unsigned bit1 = bit2 ^ (bit2 >> 1);

    return bit1 & 1;
}

void test(unsigned x) {
    if (odd_ones(x)) printf("True\n");
    else printf("False\n");
}

int main() {
    test(0x00000000);
    test(0x00000001);
    test(0x80000000);
    test(0x00000003);
    test(0xFFFFFFFF);
    test(0x7FFFFFFF);
    test(0x55555555);
    test(0xAAAAAAAA);
    test(0x0000000F);
    test(0x0000001F);
    test(0x12345678);
    test(0xDEADBEEF);
    test(0x10000000);
}
