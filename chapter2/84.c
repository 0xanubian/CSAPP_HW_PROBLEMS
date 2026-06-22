#include <stdio.h>

unsigned f2u(float x) {
    return *(unsigned *)&x;
}

int float_le(float x, float y) {
    unsigned ux = f2u(x);
    unsigned uy = f2u(y);

    unsigned sx = ux >> 31;
    unsigned sy = uy >> 31;

    return (!sx && !sy) && (ux <= uy) ||
           (ux << 1) == 0 && (uy << 1) == 0 ||
           (sx && sy) && (ux >= uy) ||
           (sx && !sy);
}

void test(float x, float y) {
    if (float_le(x, y)) printf("True\n");
    else printf("False\n");
}

int main() {
    test(4.3, 8.4);
    test(0, 0);
    test(0, -0);
    test(-4.7, -3.1);
    test(-8.4, 3.8);

    test(8.4, 4.3);
    test(-3.1, -4.7);
    test(3.8, -8.4);
}
