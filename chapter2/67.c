#include <stdio.h>

int int_size_is_32() {
    /* Set most significant bit of 32-bit machine */
    int set_msb = 1 << 31;

    /* Shift past msb of 32-bit word */
    int beyond_msb = 1 << 31;
    beyond_msb = beyond_msb << 1;

    /* set_msb is nonzero when word size >= 32
     * beyond_msb is zero when word size <= 32 */
    return set_msb && !beyond_msb;
}

int main() {
    if (int_size_is_32()) printf("True\n");
    else printf("False\n");
    return 0;
}
