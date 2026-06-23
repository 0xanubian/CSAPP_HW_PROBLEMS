#include <stdio.h>
#include <assert.h>

typedef unsigned float_bits;

int set_bit_pos(int x) {
    if ((x & 0x80000000) != 0)
        return 32;

    unsigned ux = (unsigned)x;
    int length = 0;

    while (ux >= (1u << length))
        length++;

    return length;
}

float_bits float_i2f(int i) {
    //for if i = 0
    if (i == 0)
        return 0;

    //for if i = INT_MIN as its negate will overflow the 32 bit representation
    if (i == 0x80000000)
        return 0xCF000000;

    // get the sign bit
    int sign = i & 0x80000000;

    // get absoulute value of i
    unsigned abs = sign ? -i : i;
    
    // get the E
    int E = set_bit_pos((int) abs) - 1;

    // get exponent part of float representation
    int exp = E + 127;
    
    float_bits frac;
    /* if E <= 23; for a small E, multiplying by 2^E will give us our float
     * so we need to shift it left by (23-E) to get the frac part of float
     * representation. then we need to remove the implicit leading 1
     */

    if (E <= 23) {
        frac = abs << (23 - E);
        frac = frac & 0x7fffff;
    }

    /*
     * if E > 23; for a large E, the int cannot be contained in 23 bit frac 
     * part. so we shift right by (E-23) there are some bits that are lost
     * called discarded bits. we compare those discarded bits to the halfway 
     * between two representable values (1 << (shift -1)) and make our rounding
     * decision accordingly
     */
    else {
        int shift = E - 23;
        int discarded = abs & ((1 << shift) - 1);
        int half = 1 << (shift - 1);
        frac = abs >> shift;
        frac = frac & 0x7fffff;

        //if discarded < half do nothing
        //if discarded > half round up
        //if discarded == half round such way that lsb is 0
        int lsb = frac & 1;
        if (discarded > half || (discarded == half && lsb == 1))
            frac++;
    }

    return sign | ((exp << 23) + frac);
}

int main(void)
{
    /* Zero */
    assert(float_i2f(0) == 0x00000000);

    /* Small positive integers */
    assert(float_i2f(1) == 0x3F800000);
    assert(float_i2f(2) == 0x40000000);
    assert(float_i2f(3) == 0x40400000);
    assert(float_i2f(4) == 0x40800000);
    assert(float_i2f(5) == 0x40A00000);
    assert(float_i2f(6) == 0x40C00000);
    assert(float_i2f(7) == 0x40E00000);
    assert(float_i2f(8) == 0x41000000);

    /* Small negative integers */
    assert(float_i2f(-1) == 0xBF800000);
    assert(float_i2f(-2) == 0xC0000000);
    assert(float_i2f(-3) == 0xC0400000);
    assert(float_i2f(-4) == 0xC0800000);
    assert(float_i2f(-5) == 0xC0A00000);

    /* Powers of two */
    assert(float_i2f(16) == 0x41800000);
    assert(float_i2f(32) == 0x42000000);
    assert(float_i2f(64) == 0x42800000);
    assert(float_i2f(128) == 0x43000000);
    assert(float_i2f(1024) == 0x44800000);

    /* Largest exactly representable integers */
    assert(float_i2f(16777215) == 0x4B7FFFFF);  /* 2^24 - 1 */
    assert(float_i2f(16777216) == 0x4B800000);  /* 2^24 */

    /* Round-to-even tests */
    assert(float_i2f(16777217) == 0x4B800000);

    /* More rounding cases */
    assert(float_i2f(33554431) == 0x4C000000);
    assert(float_i2f(33554432) == 0x4C000000);

    /* Large values */
    assert(float_i2f(1000000) == 0x49742400);
    assert(float_i2f(-1000000) == 0xC9742400);

    assert(float_i2f(12345) == 0x4640E400);
    assert(float_i2f(-12345) == 0xC640E400);

    /* Edge of int range */
    assert(float_i2f(0x7FFFFFFF) == 0x4F000000);
    assert(float_i2f(0x80000000) == 0xCF000000);

    printf("All test cases passed\n");

    return 0;
}
