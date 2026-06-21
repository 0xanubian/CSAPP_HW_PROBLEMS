#include <stdio.h>
#include <limits.h>

int fits_bits(int x, int n) {
    int w = sizeof(int) << 3;

    int truncated = x << (w - n);
    truncated = truncated >> (w - n);

    return x == truncated;
}

void test(int x, int n) {
    if (fits_bits(x, n)) printf("True\n");
    else printf("False\n");
    return;
}

int main() {
    test(5, 3);
    test(-4, 3);
    test(3, 3);
    test(-5, 3);
    test(4, 3);
    test(100, 7);
    test(100, 8);
    test(127, 8);
    test(128, 8);
    test(-128, 8);
    test(-129, 8);
    test(0, 1);
    test(-1, 1);
    test(1, 1);
    test(INT_MAX, 32);
    test(INT_MIN, 32);
    test(INT_MIN, 31);
    test(0, 32);
    return 0;
}
