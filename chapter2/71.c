#include <stdio.h>

typedef unsigned packet_t;

int xbyte(packet_t word, int bytenum) {
    word = word << ((3 - bytenum) << 3);
    return (int)word >> (3 << 3);
}

void test(packet_t word, int bytenum) {
    printf("For packet_t = %u, bytenum = %d : %d\n", word, bytenum, xbyte(word, bytenum));
}

int main() {
    test(0x12345678, 0);   // byte 0 = 0x78 -> positive -> expect 120
    test(0x12345678, 1);   // byte 1 = 0x56 -> positive -> expect 86
    test(0x12345678, 2);   // byte 2 = 0x34 -> positive -> expect 52
    test(0x12345678, 3);   // byte 3 = 0x12 -> positive -> expect 18

    test(0xFFFFFF80, 0);   // byte 0 = 0x80 -> negative -> expect -128
    test(0x800000FF, 0);   // byte 0 = 0xFF -> negative -> expect -1
    test(0x800000FF, 3);   // byte 3 = 0x80 -> negative -> expect -128

    test(0x00000000, 0);   // all zero -> expect 0
    test(0xFFFFFFFF, 2);   // byte 2 = 0xFF -> negative -> expect -1

    test(0xABCD1234, 0);   // byte 0 = 0x34 -> positive -> expect 52
    test(0xABCD1234, 1);   // byte 1 = 0x12 -> positive -> expect 18
    test(0xABCD1234, 2);   // byte 2 = 0xCD -> negative -> expect -51
    test(0xABCD1234, 3);   // byte 3 = 0xAB -> negative -> expect -85
}
