#include <stdio.h>

unsigned rotate_left(unsigned x, int n) {
    int w = sizeof(unsigned) << 3;
    unsigned rotate = x >> (w - n);

    x = x << n;
    return x | rotate;
}

int main() {
    printf("%X\n", rotate_left(0x12345678, 4));
    printf("%X\n", rotate_left(0x12345678, 8));
    printf("%X\n", rotate_left(0x12345678, 16));
    printf("%X\n", rotate_left(0x12345678, 20));
    printf("%X\n", rotate_left(0x12345678, 0));
}
