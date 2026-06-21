/*
 * solved it using OR-smear technique
 */

#include <stdio.h>

int leftmost_one(unsigned x) {
    unsigned s = x | (x >> 1);
    s = s | (s >> 2);
    s = s | (s >> 4);
    s = s | (s >> 8);
    s = s | (s >> 16);

    unsigned ret = s ^ (s >> 1);
    printf("for x = %X : %X\n", x, ret);
    return ret;
}

int main() {
    leftmost_one(0x00000000);
    leftmost_one(0x0000FF00);
    leftmost_one(0x00006600);
    leftmost_one(0x00000001);
    leftmost_one(0x80000000);
    leftmost_one(0xFFFFFFFF);
    leftmost_one(0x7FFFFFFF);
    leftmost_one(0x00000003);
    leftmost_one(0x12345678);
    leftmost_one(0x00000010);
    leftmost_one(0x40000001);
    leftmost_one(0x00010001);

}
