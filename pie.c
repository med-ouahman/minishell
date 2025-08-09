#include "./include/executor.h"

void child(int *pfds, char *str, int id) {
    // usleep(id * 1000);
    close(pfds[1]);
    char buf[101];
    buf[read(pfds[0], buf, 1)] = 0;
    close(pfds[0]);
    printf("Process: %d - %s\n",getpid(), buf);
    exit(0);
}

int main(void) {

    char *str = "0123456789";
    const int PROCESS_COUNT = 11;
    int pids[PROCESS_COUNT];
    int pfds[2];
    char buf[101];
    pipe(pfds);
    write(pfds[1], str, 10);
    // close(pfds[1]);
    for (int i = 0; i < PROCESS_COUNT; i++) {
        pids[i] = fork();
        if (pids[i] < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pids[i] == 0) {

            child(pfds, str, i);
        }
    }

     for (int i = 0; i < PROCESS_COUNT; i++) {
        waitpid(pids[i], 0, 0);
    }
    close(pfds[0]);
}
