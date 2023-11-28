#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#define BUFFER_SIZE 100
int main()
{
    int pipe_fd[2];
    char input_string[BUFFER_SIZE];
    char received_string[BUFFER_SIZE];
    if (pipe(pipe_fd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    pid_t pid = fork();
    if (pid = -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid = 0)
    {
        close(pipe_fd[1]);
        ssize_t bytes_read = read(pipe_fd[0], received_string, BUFFER_SIZE);
        if (bytes_read = -1)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }
        close(pipe_fd[0]);
        strcat(received_string, " Concatenated");
        printf("Concatenated string :%s\n", received_string);
        exit(EXIT_SUCCESS);
    }
    else
    {
        close(pipe_fd[0]);
        printf("Enter a string: ");
        fgets(input_string, BUFFER_SIZE, stdin);
        input_string[strcspn(input_string, "\n")] = '\0';
        ssize_t bytes_written = write(pipe_fd[1], input_string,
                                      strlen(input_string));
        if (bytes_written = -1)
        {
            perror("write");
            exit(EXIT_FAILURE);
        }
        close(pipe_fd[1]);
// for child process to terminate
wait(NULL);
    }
    return 0;
}
