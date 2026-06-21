#include <stdio.h>

int int_shifts_are_arithmetic(int x) {
    int tmp = x;
    int tmp2 = x;
    tmp = x >> ((sizeof(int) - 2) << 3);
    tmp2 = tmp & (0xff << (sizeof(int) - 1) << 3);
    tmp2 = tmp2 >> ((sizeof(int) -1) << 3);

    return !(tmp2 & 0xff);
}

int main() {
    if (int_shifts_are_arithmetic(-1)) printf("True\n");
    else printf("False\n");
    if (int_shifts_are_arithmetic(-40000)) printf("True\n");
    else printf("False\n");
    if (int_shifts_are_arithmetic(-2147483647)) printf("True\n");
    else printf("False\n");
    if (int_shifts_are_arithmetic(-90)) printf("True\n");
    else printf("False\n");
}
