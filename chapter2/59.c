/* 
 * yield a word consisting of least significant byte of x and remaining of y 
 * x = 0x89ABCDEF y = 0x76543210 result = 0x765432EF
 */

#include <stdio.h>
void int_shift(int x, int y) {
    unsigned char *xp = (unsigned char *)&x;
    unsigned char *yp = (unsigned char *)&y;

    *yp = *xp;
    printf("%X\n", *(int*)yp);
}

void long_shift(long x, long y) {
    unsigned char *xp = (unsigned char *)&x;
    unsigned char *yp = (unsigned char *)&y;

    *yp = *xp;
    printf("%lX\n", *(long*)yp);
}

int main() {
    int_shift(0x89ABCDEF, 0x76543210);
    long_shift(0x1234567890ABCDEF, 0x7D92B14EF83AC605);
    return 0;
}
