#include <stdio.h>

int any_odd_one(unsigned x) {
    unsigned mask = 0xAAAAAAAA;
    unsigned cleared_x = x & mask;

    return !!cleared_x;
}

void test(unsigned x) {
    if (any_odd_one(x)) printf("True\n");
    else printf("False\n");
}

int main() {
    test(0x00000000);
    test(0xFFFFFFFF);
    test(0x00000001);
    test(0x00000002);
    test(0x55555555);
    test(0xAAAAAAAA);
    test(0x80000000);
    test(0x40000000);
    test(0x00000004);
    test(0x00000008);
    test(0x12345678);
    test(0x01010101);
    test(0x02020202);
}
