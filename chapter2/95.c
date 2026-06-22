#include <stdio.h>
#include <assert.h>

typedef unsigned float_bits;

float_bits float_half(float_bits f) {
    float_bits sign = f & 0x80000000;
    float_bits exp = f >> 23 & 0xff;
    float_bits frac = f & 0x7fffff;

    int is_nan = (exp == 0xff);
    int is_normalised = (exp != 0xff) && (exp != 0) && (exp != 1);
    int is_exp1 = (exp == 1);
    int is_denormalised = (exp == 0);

    float_bits normalised_exp = exp - 1;
    float_bits normalised_ret = sign | (normalised_exp << 23) | frac;
    float_bits round_denorm = ((frac & 3) == 3);
    float_bits denormalised_ret = sign | (frac >> 1) + round_denorm;
    float_bits combined = frac | 0x800000;
    float_bits round_exp1 = ((combined & 3) == 3);
    float_bits exp1_ret = sign | ((combined >> 1) + round_exp1);


    float_bits ret;
    is_nan && (ret = f);
    is_normalised && (ret = normalised_ret);
    is_exp1 && (ret = exp1_ret);
    is_denormalised && (ret = denormalised_ret);
    return ret;
}

int main(void) {
    /* Zero */
    assert(float_half(0x00000000) == 0x00000000); // +0
    assert(float_half(0x80000000) == 0x80000000); // -0

    /* Normalized numbers */
    assert(float_half(0x3F800000) == 0x3F000000); // 1.0 -> 0.5
    assert(float_half(0x40000000) == 0x3F800000); // 2.0 -> 1.0
    assert(float_half(0xBF800000) == 0xBF000000); // -1.0 -> -0.5

    /* Infinity */
    assert(float_half(0x7F800000) == 0x7F800000); // +inf
    assert(float_half(0xFF800000) == 0xFF800000); // -inf

    /* NaNs must be unchanged */
    assert(float_half(0x7FC00000) == 0x7FC00000);
    assert(float_half(0x7F800001) == 0x7F800001);
    assert(float_half(0xFFC00000) == 0xFFC00000);

    /* Denormals */
    assert(float_half(0x00000002) == 0x00000001);
    assert(float_half(0x00000004) == 0x00000002);
    assert(float_half(0x80000004) == 0x80000002);

    /* Round-to-even tests */
    assert(float_half(0x00000003) == 0x00000002);
    assert(float_half(0x00000007) == 0x00000004);

    /* Normalized -> Denormalized transition */
    assert(float_half(0x00800000) == 0x00400000);
    assert(float_half(0x00800001) == 0x00400000);
    assert(float_half(0x00FFFFFF) == 0x00800000);

    /* Large finite float */
    assert(float_half(0x7F7FFFFF) == 0x7EFFFFFF);
    
    printf("all test cases passed\n");
    return 0;
}
