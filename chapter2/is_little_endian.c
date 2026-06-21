/* this will return 1 if its a little endian machine and 0 if its a big endian machine */

#include <stdio.h>

int is_little_endian() {
    int a = 1;

    unsigned char *byte = (unsigned char *)&a;
    return *byte;
}

int main() {
    if (is_little_endian()) printf("This is a little endian machine\n");
    else printf("This is a big endian machine\n");
    return 0;
}
