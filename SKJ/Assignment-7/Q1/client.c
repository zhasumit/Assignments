#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"  // Change this to the server's IP address
#define PORT 12345

void receive_file(int server_socket) {
    FILE *file = fopen("received_file.txt", "wb");
    if (file == NULL) {
        perror("File create error");
        exit(1);
    }

    char buffer[1024];
    int bytesRead;

    while ((bytesRead = recv(server_socket, buffer, sizeof(buffer), 0)) > 0) {
        fwrite(buffer, 1, bytesRead, file);
    }

    fclose(file);
}

int main() {
    int client_socket;
    struct sockaddr_in server_addr;

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Socket creation error");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection error");
        exit(1);
    }

    receive_file(client_socket);
    printf("File received successfully.\n");

    close(client_socket);
    return 0;
}