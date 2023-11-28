#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define PORT 8080
int main()
{
    int server_fd, new_socket;
    struct sockaddr_in server_addr, new_addr;
    socklen_t addr_size;
    char buffer[1024];
    time_t rawtime;
    struct tm *info;
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0)
    {
        perror("Error in socket");
        exit(1);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = PORT;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Error in bind");
        exit(1);
    }
    if (listen(server_fd, 10) == 0)
    {
        printf("Listening...\n");
    }
    else
    {
        perror("Error in listen");
        exit(1);
    }
    addr_size = sizeof(new_addr);
    new_socket = accept(server_fd, (struct sockaddr *)&new_addr, &addr_size);
    time(&rawtime);
    info = localtime(&rawtime);
    snprintf(buffer, sizeof(buffer), "Date and Time: %sCPU Load: 0.75\n",
             asctime(info));
    send(new_socket, buffer, strlen(buffer), 0);
    close(new_socket);
    close(server_fd);
    return 0;
}