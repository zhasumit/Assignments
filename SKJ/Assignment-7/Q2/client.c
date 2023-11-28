#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

int main() {
    int client_socket;
    struct sockaddr_in server_addr;

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Socket creation error");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection error");
        exit(1);
    }

    int a = 5, b = 3, result;

    send(client_socket, &a, sizeof(a), 0);
    send(client_socket, &b, sizeof(b), 0);

    recv(client_socket, &result, sizeof(result), 0);

    printf("\nResult: %d\n", result);

    close(client_socket);
    return 0;
}