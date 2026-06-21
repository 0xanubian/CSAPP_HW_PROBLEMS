#include <stdio.h>
#include <limits.h>

int tsub_ok(int x, int y) {
    //y = -y;
    int sub = x - y;
    int sign_x = (unsigned)x >> 31;
    int sign_y = !((unsigned)y >> 31);
    int sign_s = (unsigned)sub >> 31;

    int is_neg_overflow = !(sign_x ^ sign_y) && (sign_x && sign_y) && (!sign_s);
    int is_pos_overflow = !(sign_x ^ sign_y) && (!sign_x && !sign_y) && (sign_s);

    return !(is_pos_overflow || is_neg_overflow);
}

void test(int x, int y) {
    if (tsub_ok(x, y))
        printf("For x = %d, y = %d subtraction is True\n", x, y);
    else 
        printf("For x = %d, y = %d subtraction is False\n", x, y);
}

int main() {
    test(10, 8);              // expect 1 — ordinary, no overflow
    test(0, 0);                // expect 1 — trivial
    test(INT_MIN, 1);           // expect 0 — negative overflow
    test(INT_MAX, -1);           // expect 0 — positive overflow
    test(INT_MIN, INT_MAX);       // expect 0 — large negative overflow
    test(INT_MAX, INT_MIN);        // expect 0 — large positive overflow
    test(INT_MIN, INT_MIN);         // expect 1 — same value, true result is 0, fits fine
    test(INT_MAX, INT_MAX);          // expect 1 — same value, true result is 0, fits fine
    test(INT_MAX - 1, -1);            // expect 1 — exactly reaches TMax, no overflow
    test(INT_MIN + 1, 1);              // expect 1 — exactly reaches TMin, no overflow
    test(0, INT_MIN);                   // expect 0 — the errata's flagged edge case (y = TMin), x nonnegative
    test(-1, INT_MIN);                    // expect 1 — the errata's flagged edge case (y = TMin), x negative
    test(-5, INT_MIN);                      // expect 1 — same idea, another negative x
    test(5, INT_MIN);                        // expect 0 — same idea, another nonnegative x
    return 0;
}
