#include <stdio.h>

int divide_power2(int x, int k) {
    int sign = x >> 31;
    sign && (x = x + (1 << k) - 1);
    x = x >> k;
    return x;
}

int main() {
    printf("%d\n", divide_power2(12, 2));
    printf("%d\n", divide_power2(13, 2));
    printf("%d\n", divide_power2(-12, 2));
    printf("%d\n", divide_power2(-13, 2));
    printf("%d\n", divide_power2(-15, 2));
    printf("%d\n", divide_power2(15, 2));
    printf("%d\n", divide_power2(0, 5));
    printf("%d\n", divide_power2(7, 0));
    printf("%d\n", divide_power2(-7, 0));
    printf("%d\n", divide_power2(1, 31));
    printf("%d\n", divide_power2(-1, 31));
    printf("%d\n", divide_power2(-2147483648, 1));
    printf("%d\n", divide_power2(-2147483648, 31));
    printf("%d\n", divide_power2(2147483647, 1));

    return 0;
}
