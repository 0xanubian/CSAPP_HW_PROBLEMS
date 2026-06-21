#include <stdio.h>
#include <stdlib.h>

void copy_int(int val, void *buf, int maxbytes) {
    if (maxbytes - (int)sizeof(val) >= 0) printf("copy successful\n");
    else printf("copy failed\n");
    return;
}

int main() {
    void *buf = malloc(5);
    copy_int(1, buf, 4);
    copy_int(1, buf, 3);
}
