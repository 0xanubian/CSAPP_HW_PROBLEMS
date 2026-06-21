#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *calloc(size_t nmemb, size_t size) {
    int params_not_zero = nmemb && size;
    
    int msize;
    void *ret = NULL;

    params_not_zero && (msize = nmemb * size);
    params_not_zero && (nmemb == msize / size) && (ret = malloc(msize));
    params_not_zero && (nmemb == msize / size) && (memset(ret, 0, msize));

    return ret;
}

int main() {
    if (calloc(0, 1)) printf("True\n");
    else printf("False\n");
    if (calloc(1, 0)) printf("True\n");
    else printf("False\n");
    if (calloc(6, 8)) printf("True\n");
    else printf("False\n");
    if (calloc(1000000, 5000)) printf("True\n");
    else printf("False\n");
}
