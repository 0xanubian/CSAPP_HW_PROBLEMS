#include <stdio.h>

int main() {
    char buf[16];

    fgets(buf, 16, stdin);
    printf("\n%s\n", buf);
}
