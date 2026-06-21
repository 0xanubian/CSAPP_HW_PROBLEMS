#include <stdio.h>
#include <limits.h>

int saturating_add(int x, int y) {
    int sum = x + y;
    int sign_x = (unsigned)x >> 31;
    int sign_y = (unsigned)y >> 31;
    int sign_s = (unsigned)sum >> 31;

    int is_neg_overflow = !(sign_x ^ sign_y) && (sign_x && sign_y) && (!sign_s);
    int is_pos_overflow = !(sign_x ^ sign_y) && (!sign_x && !sign_y) && (sign_s);

    int result = sum;
    int min = 0x80000000;
    int max = 0x7FFFFFFF;
    is_neg_overflow && (result = min);
    is_pos_overflow && (result = max);
    return result;
}

void test(int x, int y) {
    printf("For x = %d, y = %d : sum = %d\n", x, y, saturating_add(x, y));
}

int main() {
    test(INT_MAX, 1);            // expect INT_MAX  (2147483647)  -- positive overflow, clamps to TMax
    test(1, INT_MAX);             // expect INT_MAX  (2147483647)  -- same but operands swapped
    test(INT_MAX, INT_MAX);       // expect INT_MAX  (2147483647)  -- both at max, large positive overflow
    test(INT_MIN, -1);            // expect INT_MIN  (-2147483648) -- negative overflow, clamps to TMin
    test(-1, INT_MIN);             // expect INT_MIN  (-2147483648) -- same but operands swapped
    test(INT_MIN, INT_MIN);        // expect INT_MIN  (-2147483648) -- both at min, large negative overflow
    test(INT_MAX, 0);               // expect 2147483647             -- boundary, no overflow
    test(INT_MIN, 0);                // expect -2147483648            -- boundary, no overflow
    test(INT_MAX, -1);                // expect 2147483646             -- mixed signs, never overflows
    test(INT_MIN, 1);                  // expect -2147483647            -- mixed signs, never overflows
    test(0, 0);                         // expect 0                       -- trivial
    test(100, 200);                      // expect 300                     -- ordinary positive, no overflow
    test(-100, -200);                     // expect -300                    -- ordinary negative, no overflow
    test(INT_MAX - 1, 1);                  // expect 2147483647 (INT_MAX)    -- exactly at the edge, should NOT overflow
    test(INT_MAX, -INT_MAX);                // expect 0                       -- cancels out to 0, mixed signs
    test(INT_MIN + 1, -1);                   // expect -2147483648 (INT_MIN)   -- exactly at the edge, should NOT overflow
    return 0;
}
