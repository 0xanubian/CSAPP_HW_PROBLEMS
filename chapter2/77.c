#include <stdio.h>

int mul_17(int x) {
    int orig_x = x;
    x = x << 4;
    x += orig_x;
    return x;
}

int mul_m7(int x) {
    int orig_x = x;
    x = x << 3;
    x -= orig_x;
    return -x;
}

int mul_60(int x) {
    int orig_x = x;
    x = x << 6;
    x -= (orig_x << 2);
    return x;
}

int mul_m112(int x) {
    int orig_x = x;
    x = x << 7;
    x -= (orig_x << 4);
    return -x;
}

int main() {
    printf("%d\n", mul_17(9));
    printf("%d\n", mul_m7(9));
    printf("%d\n", mul_60(9));
    printf("%d\n", mul_m112(9));
}
