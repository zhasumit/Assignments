#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int clientSocket;
    struct sockaddr_in serverAddr;

    // Create a socket for the client
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Initialize the server address structure
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Change to the load balancer'sIP
    serverAddr.sin_port = htons(8888);                   // Use the load balancer's port

    // Connect to the load balancer
    connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    char message[1024];
    printf("Enter a message to send to the load balancer: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0'; // Remove the newline character

    // Send the message to the load balancer
    write(clientSocket, message, strlen(message));
    char buffer[1024];
    ssize_t bytesRead;

    // Receive the response from the load balancer
    bytesRead = read(clientSocket, buffer, sizeof(buffer));
    printf("Response from Load Balancer: %s\n", buffer);

    // Close the client socket
    close(clientSocket);
    return 0;
}