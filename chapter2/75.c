#include <stdio.h>
#include <stdint.h>

int signed_high_prod(int x, int y) {
    int64_t high_prod = (int64_t)x * (int64_t)y;
    return (int)(high_prod >> 32);
}

unsigned unsigned_high_prod(unsigned x, unsigned y) {
    int sign_x = x >> 31;
    int sign_y = y >> 31;
    int high_prod = signed_high_prod((int)x, (int)y);
    return high_prod + sign_x * y + sign_y * x;
}

void test(unsigned x, unsigned y) {
    printf("For x = %x, for y = %x, high_bits are = %x\n", x, y, unsigned_high_prod(x, y));
}

int main() {
    test(0x12345678, 0xFFFFFFFF);   // expect 0x12345677
    test(0x00000000, 0x00000000);   // expect 0x00000000
    test(0xFFFFFFFF, 0xFFFFFFFF);   // expect 0xFFFFFFFE
    test(0x00000001, 0xFFFFFFFF);   // expect 0x00000000
    test(0x80000000, 0x00000002);   // expect 0x00000001
    test(0x80000000, 0x80000000);   // expect 0x40000000
    test(0x7FFFFFFF, 0x7FFFFFFF);   // expect 0x3FFFFFFF
    test(0xFFFFFFFF, 0x00000001);   // expect 0x00000000
    test(0x10000000, 0x10000000);   // expect 0x01000000
    test(0xABCDEF01, 0x12345678);   // expect 0x0c379aaa
    return 0;
}
