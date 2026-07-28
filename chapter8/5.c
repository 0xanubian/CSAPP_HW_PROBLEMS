#include <stdio.h>
#include <unistd.h>

unsigned int wakeup(unsigned int secs) {
    int ret = sleep(secs);

    printf("Woke up at %d secs.\n", secs-ret);
    return ret;
}
