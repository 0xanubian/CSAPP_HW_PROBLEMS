#include <stdio.h>

void replace_byte(unsigned x, int i, unsigned char b) {
    printf("For x = 0x%X, i = %d, and b = 0x%X: ", x, i, b);

    unsigned xright = x;
    
    //for the left part
    x = x >> ((i + 1) << 3);
    x = x << (1 << 3);
    x = x + (unsigned)b;

    //for the right part
    unsigned tmp = xright;
    tmp = tmp >> (i << 3);
    tmp = tmp << (i << 3);
    xright = xright ^ tmp;

    //combining
    x = x << (i << 3);
    x = x + xright;

    printf("0x%X\n", x);
}

int main() {
    replace_byte(0x12345678, 2, 0xAB);
    replace_byte(0x12345678, 0, 0xAB);
    replace_byte(0x12345678, 1, 0xAB);
    replace_byte(0x12345678, 3, 0xAB);
}
