#include <stdio.h>

int lower_one_mask(int n) {
    int mask = 0xffffffff;
    mask = mask << (n-1);
    mask = mask << 1;
    return ~mask;
}

int main() {
    printf("for %d : 0x%X\n", 6, lower_one_mask(6));
    printf("for %d : 0x%X\n", 17, lower_one_mask(17));
    printf("for %d : 0x%X\n", 32, lower_one_mask(32));
}
