#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void signal_handler(int sig) {
    return;
}

unsigned int wakeup(unsigned int secs) {
    if (signal(SIGINT, signal_handler) == SIG_ERR) {
        fprintf(stderr, "Signal error\n");
    }

    int ret = sleep(secs);

    printf("Slept for %d of %d secs.\n", secs-ret, secs);
    return ret;
}

int main(int argc, char **argv, char **envp) {
    int secs = atoi(argv[1]);

    wakeup(secs);
    return 0;
}
