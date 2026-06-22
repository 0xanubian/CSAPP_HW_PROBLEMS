#include <assert.h>
#include <stdio.h>

typedef unsigned float_bits;

float_bits float_negate(float_bits f) {
    float_bits de_signed = f << 1;
    de_signed = de_signed >> 1;
    float_bits exp = de_signed >> 23;
    float_bits frac = de_signed << 9;
    frac = frac >> 9;

    int is_nan = (exp == 0xff) && frac;

    float_bits ret;
    is_nan && (ret = f);
    !is_nan && (ret = f ^ 0x80000000);
    return ret;
}

int main() {
    assert(float_negate(0x00000000) == 0x80000000);
    assert(float_negate(0x80000000) == 0x00000000);
    assert(float_negate(0x3F800000) == 0xBF800000);
    assert(float_negate(0xBF800000) == 0x3F800000);
    assert(float_negate(0x40200000) == 0xC0200000);
    assert(float_negate(0x00000001) == 0x80000001);
    assert(float_negate(0x007FFFFF) == 0x807FFFFF);
    assert(float_negate(0x00800000) == 0x80800000);
    assert(float_negate(0x7F800000) == 0xFF800000);
    assert(float_negate(0xFF800000) == 0x7F800000);

    /* NaNs must be unchanged */
    assert(float_negate(0x7FC00000) == 0x7FC00000);
    assert(float_negate(0x7F800001) == 0x7F800001);
    assert(float_negate(0xFFC00000) == 0xFFC00000);
    printf("all tests passed\n");
}
