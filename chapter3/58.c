long decode2(long x, long y, long z) {
    y = y - z;
    x = x * y;

    long val = y;
    val = val << 63;
    val = val >> 63;
    val = val ^ x;

    return val;
}
