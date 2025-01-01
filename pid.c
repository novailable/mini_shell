#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main() {
    pid_t pid = fork();

    if (pid == -1) {
        // Error occurred during fork
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        // In the child process, exit immediately
        exit(0);
    } else {
        // In the parent process, print the process ID
        printf("%d\n", pid); // Parent's PID (which is the child process ID in this case)
        wait(NULL); // Wait for the child to terminate
    }

    return 0;
}
