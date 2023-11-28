#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>
#define SERVER2_PORT 8890
int main()
{
    int serverSocket;
    struct sockaddr_in serverAddr;

    // Create a socket for Server 2
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Initialize the server address structure
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(SERVER2_PORT);

    // Bind the server socket
    bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

    // Listen for incoming connections
    listen(serverSocket, 5);
    while (1)
    {
        int clientSocket;
        char buffer[1024];
        ssize_t bytesRead;

        // Accept an incoming connection from a load balancer
        clientSocket = accept(serverSocket, NULL, NULL);
        printf("Accepted connection from the load balancer.\n");

        // Receive the message from the load balancer
        bytesRead = read(clientSocket, buffer, sizeof(buffer));
        printf("Received from the load balancer: %s\n", buffer);

        // Process the message (e.g., convert to lowercase in this example)
        for (int i = 0; i < bytesRead; i++)
        {
            buffer[i] = tolower(buffer[i]);
        }

        // Send the processed message back to the load balancer
        write(clientSocket, buffer, bytesRead);
        printf("Processed message: %s\n", buffer);
        
        // Close the client socket
        close(clientSocket);
    }
    
    // Close the server socket (not reached in this simplified example)
    close(serverSocket);
    return 0;
}