#include <stdio.h>

unsigned a(int k) {
    unsigned x = 0xffffffff;
    return x << k;
}

unsigned b(int j, int k) {
    unsigned x = 0xffffffff;
    x = x >> k;
    x = x << k;
    x = ~x;
    x = x << j;
    return x;
}
