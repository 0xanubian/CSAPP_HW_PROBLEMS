#include <stdio.h>

int func_a(int x) {
    return !!x;
}

int func_b(int x) {
    x = ~x;
    return !!x;
}

int func_c(int x) {
    x = x & 0xff;
    return !!x;
}

int func_d(int x) {
    x = x & (0xff << ((sizeof(int) - 1) << 3));
    x = ~x;
    return ~~x;
}

int test(int x) {
    return func_a(x) && func_b(x) && func_c(x) && func_d(x);
}

int main() {
    printf("0x00000000: %d\n", test(0x00000000));
    printf("0xFFFFFFFF: %d\n", test(0xFFFFFFFF));
    printf("0x00000001: %d\n", test(0x00000001));
    printf("0x80000000: %d\n", test(0x80000000));
    printf("0x000000FF: %d\n", test(0x000000FF));
    printf("0xFF000000: %d\n", test(0xFF000000));
    printf("0x00FFFFFF: %d\n", test(0x00FFFFFF));
    printf("0xFFFFFF00: %d\n", test(0xFFFFFF00));
    printf("0x12345678: %d\n", test(0x12345678));
    printf("0x7FFFFFFF: %d\n", test(0x7FFFFFFF));
}
