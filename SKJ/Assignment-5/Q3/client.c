#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
int main()
{
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[1024];
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0)
    {
        perror("Error in socket");
        exit(1);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = PORT;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    if (connect(client_socket, (struct sockaddr *)&server_addr,
                sizeof(server_addr)) < 0)
    {
        perror("Error in connection");
        exit(1);
    }
    recv(client_socket, buffer, sizeof(buffer), 0);
    printf("Server Response: %s\n", buffer);
    close(client_socket);
    return 0;
}
