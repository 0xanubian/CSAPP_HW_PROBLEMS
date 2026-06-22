#include <stdio.h>

int threeforth(int x) {
    /*
     * we first x / 4 and get the quotient(q) then remainder(r) = x - 4q
     * result = 3q + (3r)/4 but for roundinng to 0, as >> 2 rounds toward -inf
     * we need to add bias The bias for dividing by 2^k with round-toward-zero
     * is (2^k - 1) for -ve r and nothing for +ve r
    */

    int sign_x = x >> 31;
    int bias = 0;
    bias = sign_x & ((1 << 2) - 1);
    int q = (x + bias) >> 2;
    int r = x - (q << 2);
    q = q + q + q;
    
    r = r + r + r;
    int sign_r = r >> 31;
    bias = 0;
    sign_r && (bias = (1 << 2) - 1);
    r = r + bias;
    r = r >> 2;

    return q + r;
}

int main() {
    printf("for %d : %d\n", 0, threeforth(0));
    printf("for %d : %d\n", 8, threeforth(8));
    printf("for %d : %d\n", 7, threeforth(7));
    printf("for %d : %d\n", -8, threeforth(-8));
    printf("for %d : %d\n", -7, threeforth(-7));
    printf("for %d : %d\n", 1, threeforth(1));
    printf("for %d : %d\n", -1, threeforth(-1));
    printf("for %d : %d\n", 2147483647, threeforth(2147483647));
    printf("for %d : %d\n", -2147483648, threeforth(-2147483648));
}
