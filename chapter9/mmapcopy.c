#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

long get_file_size(FILE *fp) {
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    return size;
}

void mmapcopy(int fd, int size) {
    void *buf = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
    write(1, buf, size);
}

int main() {
    int fd = open("file.txt", O_RDONLY);

    struct stat st;
    fstat(fd, &st);

    int file_size = st.st_size;

    mmapcopy(fd, file_size);
}
