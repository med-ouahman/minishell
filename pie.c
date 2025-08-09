#include "./include/executor.h"
int write_sig = 0;
void child(int *pfds, int id) {
    char buff[101];
    if (id == 0) {
        close(pfds[0]);
        while (write_sig == 0) {
            usleep(100);
        }
        write(pfds[1], "data sent", 10);
    } else {
        buff[read(pfds[0], buff, 10)] = 0;
        printf("%s\n", buff);
    }
    exit(0);
}

void handler(int signum) {

    if (SIGINT == signum) {
        write_sig = !write_sig;
    }
}

int main(void) {

    const int PROCESS_COUNT = 2;
    int pids[PROCESS_COUNT];
    int pfds[2];
    
    pipe(pfds);

    signal(SIGINT, handler);
    for (int i = 0; i < PROCESS_COUNT; i++) {
        pids[i] = fork();
        if (pids[i] == 0)
            child(pfds, i);
        else if (pids[i] < 0) {
            perror("fork");
        }
    }
    for (int i = 0; i < PROCESS_COUNT; ++i) {
        waitpid(pids[i], 0, 0);
    }
    close(pfds[0]);
    close(pfds[1]);
    return 0;
}
