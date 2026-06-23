#include <stdio.h>
#include <assert.h>

typedef unsigned float_bits;

int float_f2i(float_bits f) {
    float_bits sign = f >> 31;
    float_bits exp = f >> 23 & 0xff;
    float_bits frac = f & 0x7fffff;
    float_bits bias = 127;
    int e = exp - bias;

    int ret;
    float_bits m;
    //for 0
    if (exp == 0 && frac == 0) ret = 0;

    // for NaN
    else if (exp == 0xff) ret = 0x80000000;

    // can't be represented in 32 bit signed int
    else if (e > 30) ret = 0x80000000;

    // close to zero so round it to zero
    else if (e < 0) ret = 0;

    else {
        // add the leading 1
        m = frac | 0x800000;

        //shift the binary point correctly
        if (e > 23) ret = m << (e - 23);
        else ret = m >> (23 - e);
    }

    if (sign) ret = -ret;

    return ret;
}

int main() {
    assert(float_f2i(0x00000000) == 0);
    assert(float_f2i(0x80000000) == 0);

    /* Integers */
    assert(float_f2i(0x3F800000) == 1);      // 1.0
    assert(float_f2i(0x40000000) == 2);      // 2.0
    assert(float_f2i(0x40400000) == 3);      // 3.0
    assert(float_f2i(0x40800000) == 4);      // 4.0
    assert(float_f2i(0x40A00000) == 5);      // 5.0

    /* Negative integers */
    assert(float_f2i(0xBF800000) == -1);     // -1.0
    assert(float_f2i(0xC0000000) == -2);     // -2.0
    assert(float_f2i(0xC0400000) == -3);     // -3.0

    /* Fractional values: round toward zero */
    assert(float_f2i(0x3FC00000) == 1);      // 1.5
    assert(float_f2i(0x40200000) == 2);      // 2.5
    assert(float_f2i(0x40B00000) == 5);      // 5.5

    assert(float_f2i(0xBFC00000) == -1);     // -1.5
    assert(float_f2i(0xC0200000) == -2);     // -2.5
    assert(float_f2i(0xC0B00000) == -5);     // -5.5

    /* Magnitude less than 1 */
    assert(float_f2i(0x3F000000) == 0);      // 0.5
    assert(float_f2i(0x3F400000) == 0);      // 0.75
    assert(float_f2i(0xBF000000) == 0);      // -0.5
    assert(float_f2i(0xBF400000) == 0);      // -0.75

    /* Exact powers of two */
    assert(float_f2i(0x44800000) == 1024);   // 1024.0
    assert(float_f2i(0x4B000000) == 8388608);// 2^23

    /* Largest signed int exactly representable */
    assert(float_f2i(0x4EFFFFFF) == 2147483520);

    /* Overflow */
    assert(float_f2i(0x4F000000) == 0x80000000u); // 2^31
    assert(float_f2i(0xCF000000) == 0x80000000u); // -2^31 (Data Lab spec)
    assert(float_f2i(0x7F7FFFFF) == 0x80000000u); // largest finite float

    /* Infinity */
    assert(float_f2i(0x7F800000) == 0x80000000u);
    assert(float_f2i(0xFF800000) == 0x80000000u);

    /* NaN */
    assert(float_f2i(0x7FC00000) == 0x80000000u);
    assert(float_f2i(0x7F800001) == 0x80000000u);
    assert(float_f2i(0xFFC00000) == 0x80000000u);

    printf("All test cases passed\n");
    return 0;
}
