#include <assert.h>
#include <stdio.h>

typedef unsigned float_bits;

float_bits float_absval(float_bits f) {
    float_bits exp = f >> 23 & 0xff;
    float_bits frac = f & 0x7fffff;

    int is_nan = (exp == 0xff) && frac;

    float_bits ret;
    ret = f << 1;
    ret = ret >> 1;
    is_nan && (ret = f);
    return ret;
}

int main() {
    assert(float_absval(0x00000000) == 0x00000000);
    assert(float_absval(0x80000000) == 0x00000000);

    assert(float_absval(0x3F800000) == 0x3F800000);
    assert(float_absval(0xBF800000) == 0x3F800000);

    assert(float_absval(0x40200000) == 0x40200000);
    assert(float_absval(0xC0200000) == 0x40200000);

    assert(float_absval(0x00000001) == 0x00000001);
    assert(float_absval(0x80000001) == 0x00000001);

    assert(float_absval(0x007FFFFF) == 0x007FFFFF);
    assert(float_absval(0x807FFFFF) == 0x007FFFFF);

    assert(float_absval(0x00800000) == 0x00800000);
    assert(float_absval(0x80800000) == 0x00800000);

    assert(float_absval(0x7F800000) == 0x7F800000);
    assert(float_absval(0xFF800000) == 0x7F800000);

    /* NaNs must be unchanged */
    assert(float_absval(0x7FC00000) == 0x7FC00000);
    assert(float_absval(0x7F800001) == 0x7F800001);
    assert(float_absval(0xFFC00000) == 0xFFC00000);
    printf("all tests passed\n");
}
