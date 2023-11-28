#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#define ROWS 3
#define COLS 3
void sendMatrix(int pipe_fd[2], int matrix[ROWS][COLS])
{
    close(pipe_fd[0]);
    write(pipe_fd[1], matrix, sizeof(int) * ROWS * COLS);
    close(pipe_fd[1]);
}
void receiveMatrix(int pipe_fd[2], int result[ROWS][COLS])
{
    close(pipe_fd[1]);
    read(pipe_fd[0], result, sizeof(int) * ROWS * COLS);
    close(pipe_fd[0]);
}
int main()
{
    int matrix1[ROWS][COLS] = {{3, 2, 3}, {4, 1, 6}, {2, 8, 3}};
    int matrix2[ROWS][COLS] = {{4, 4, 7}, {6, 5, 4}, {3, 2, 1}};
    int result[ROWS][COLS] = {0};
    int pipe_parent_to_child[2];
    int pipe_child_to_parent[2];
    if (pipe(pipe_parent_to_child) == -1 | pipe(pipe_child_to_parent) == -1)
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
        int child_result[ROWS][COLS] = {0};
        receiveMatrix(pipe_parent_to_child, matrix1);
        receiveMatrix(pipe_parent_to_child, matrix2);
        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                child_result[i][j] = matrix1[i][j] + matrix2[i][j];
            }
        }
        sendMatrix(pipe_child_to_parent, child_result);
        exit(EXIT_SUCCESS);
    }
    else
    {
        sendMatrix(pipe_parent_to_child, matrix1);
        sendMatrix(pipe_parent_to_child, matrix2);
        receiveMatrix(pipe_child_to_parent, result);
        printf("Sum of Matrices:\n");
        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                printf("%d\t", result[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}
