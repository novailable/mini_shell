#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipe_fd[2];
    pid_t pid1, pid2;

    // Create the pipe
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        return 1;
    }

    // Fork the first child for `cat`
    pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        return 1;
    }

    if (pid1 == 0) {  // Child process for `cat`
        // Close the unused write end of the pipe
        close(pipe_fd[0]);

        // Redirect stdout to the pipe
        dup2(pipe_fd[1], STDOUT_FILENO);

        // Close the write end of the pipe
        close(pipe_fd[1]);

        // Prepare arguments for `cat`
        char *cat_args[] = {"/bin/cat", NULL};

        // Execute `cat` using execve
        execve("/bin/cat", cat_args, NULL);
        perror("execve cat");
        return 1;
    }

    // Fork the second child for `ls`
    pid2 = fork();
    if (pid2 == -1) {
        perror("fork");
        return 1;
    }

    if (pid2 == 0) {  // Child process for `ls`
        // Close the unused read end of the pipe
        close(pipe_fd[1]);

        // Redirect stdin to read from the pipe
        dup2(pipe_fd[0], STDIN_FILENO);

        // Close the read end of the pipe
        close(pipe_fd[0]);

        // Prepare arguments for `ls`
        char *ls_args[] = {"/bin/ls", NULL};

        // Execute `ls` using execve
        execve("/bin/ls", ls_args, NULL);
        perror("execve ls");
        return 1;
    }

    // Parent process
    // Close both ends of the pipe
    close(pipe_fd[0]);
    close(pipe_fd[1]);

    // Wait for both child processes to finish
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}
