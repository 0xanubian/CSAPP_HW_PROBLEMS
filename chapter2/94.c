#include <stdio.h>
#include <assert.h>

typedef unsigned float_bits;

float_bits float_twice(float_bits f) {
    float_bits sign = f >> 31;
    sign = sign << 31;
    float_bits exp = f >> 23 & 0xff;
    float_bits frac = f & 0x7fffff;
    int is_nan = (exp == 0xff);

    int is_normalised = (exp != 0xff) && (exp != 0);
    int is_denormalised = (exp == 0);

    unsigned normalised_exp = exp + 1;
    unsigned is_overflow = (normalised_exp == 0xff);
    unsigned normalised_ret;
    is_overflow && (normalised_ret = sign | 0x7f800000);
    !is_overflow && (normalised_ret = sign | normalised_exp << 23 | frac);
    unsigned denormalised_ret = sign | ((f & 0x7FFFFFFF) << 1);

    float_bits ret;
    is_nan && (ret = f);
    is_normalised && (ret = normalised_ret);
    is_denormalised && (ret = denormalised_ret);
    return ret;
}

int main() {
    assert(float_twice(0x00000000) == 0x00000000);
    assert(float_twice(0x80000000) == 0x80000000);

    assert(float_twice(0x00000001) == 0x00000002);
    assert(float_twice(0x00000002) == 0x00000004);
    assert(float_twice(0x00400000) == 0x00800000);
    assert(float_twice(0x007FFFFF) == 0x00FFFFFE);
    assert(float_twice(0x80000001) == 0x80000002);

    assert(float_twice(0x3F800000) == 0x40000000);
    assert(float_twice(0x40000000) == 0x40800000);
    assert(float_twice(0x40400000) == 0x40C00000);
    assert(float_twice(0xBF800000) == 0xC0000000);
    assert(float_twice(0xC0200000) == 0xC0A00000);

    assert(float_twice(0x7F000000) == 0x7F800000);
    assert(float_twice(0x7F7FFFFF) == 0x7F800000);
    assert(float_twice(0xFF7FFFFF) == 0xFF800000);

    assert(float_twice(0x7F800000) == 0x7F800000);
    assert(float_twice(0xFF800000) == 0xFF800000);

    assert(float_twice(0x7FC00000) == 0x7FC00000);
    assert(float_twice(0x7F800001) == 0x7F800001);
    assert(float_twice(0xFFC00000) == 0xFFC00000);
    printf("All test cases passed\n");
}
