#include <stdio.h>

int mul3div4(int x) {
    //sign && (x = x + (1 << 
    x = x + x + x;
    int sign = x >> 31;
    sign && (x = x + (1 << 2) - 1);
    x = x >> 2;
    return x;
}

int main() {
    printf("for %d : %d\n", 8, mul3div4(8));
    printf("for %d : %d\n", -8, mul3div4(-8));
    printf("for %d : %d\n", 100, mul3div4(100));
    printf("for %d : %d\n", -100, mul3div4(-100));
    printf("for %d : %d\n", 7, mul3div4(7));
    printf("for %d : %d\n", -7, mul3div4(-7));
    printf("for %d : %d\n", 0, mul3div4(0));
    printf("for %d : %d\n", 1, mul3div4(1));
    printf("for %d : %d\n", -1, mul3div4(-1));
    printf("for %d : %d\n", 0x7FFFFFFF, mul3div4(0x7FFFFFFF));
    printf("for %d : %d\n", 0x60000000, mul3div4(0x60000000));
    printf("for %d : %d\n", 0x40000000, mul3div4(0x40000000));
    printf("for %d : %d\n", 0x3FFFFFFF, mul3div4(0x3FFFFFFF));
    printf("for %d : %d\n", 0x80000000, mul3div4(0x80000000));
    printf("for %d : %d\n", 0xAAAAAAAA, mul3div4(0xAAAAAAAA));
}
