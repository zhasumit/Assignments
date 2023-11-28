#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define LOAD_BALANCER_PORT 8888
#define SERVER_COUNT 2
#define SERVER1_IP "127.0.0.1"
#define SERVER1_PORT 8889
#define SERVER2_IP "127.0.0.1"
#define SERVER2_PORT 8890

int main()
{
    int loadBalancerSocket, serverSockets[SERVER_COUNT];
    struct sockaddr_in loadBalancerAddr, serverAddrs[SERVER_COUNT];
 
    // Create a socket for the load balancer
    loadBalancerSocket = socket(AF_INET, SOCK_STREAM, 0);
 
    // Initialize the load balancer address structure
    memset(&loadBalancerAddr, 0, sizeof(loadBalancerAddr));
    loadBalancerAddr.sin_family = AF_INET;
    loadBalancerAddr.sin_addr.s_addr = INADDR_ANY;
    loadBalancerAddr.sin_port = htons(LOAD_BALANCER_PORT);
 
    // Bind the load balancer socket
    bind(loadBalancerSocket, (struct sockaddr *)&loadBalancerAddr, sizeof(loadBalancerAddr));
 
    // Listen for incoming connections
    listen(loadBalancerSocket, SERVER_COUNT);

    // Create sockets for Server 1 and Server 2
    serverSockets[0] = socket(AF_INET, SOCK_STREAM, 0);
    serverSockets[1] = socket(AF_INET, SOCK_STREAM, 0);

    // Initialize server addresses
    memset(&serverAddrs[0], 0, sizeof(serverAddrs[0]));
    serverAddrs[0].sin_family = AF_INET;
    serverAddrs[0].sin_addr.s_addr = inet_addr(SERVER1_IP);
    serverAddrs[0].sin_port = htons(SERVER1_PORT);
    memset(&serverAddrs[1], 0, sizeof(serverAddrs[1]));
    serverAddrs[1].sin_family = AF_INET;
    serverAddrs[1].sin_addr.s_addr = inet_addr(SERVER2_IP);
    serverAddrs[1].sin_port = htons(SERVER2_PORT);

    // Connect to Server 1 and Server 2
    connect(serverSockets[0], (struct sockaddr *)&serverAddrs[0], sizeof(serverAddrs[0]));
    connect(serverSockets[1], (struct sockaddr *)&serverAddrs[1], sizeof(serverAddrs[1]));
    int currentServer = 0; // Variable to keep track of the selected server
    while (1)
    {
        int clientSocket;

        // Accept an incoming connection from a client
        clientSocket = accept(loadBalancerSocket, NULL, NULL);
        printf("Accepted connection from a client.\n");
        char buffer[1024];
        ssize_t bytesRead;
        
        // Read the message from the client
        bytesRead = read(clientSocket, buffer, sizeof(buffer));
        printf("Received from client: %s\n", buffer);
        
        // Forward the message to the selected server
        write(serverSockets[currentServer], buffer, bytesRead);
        printf("Forwarded to server %d: %s\n", currentServer + 1, buffer);
        char serverResponse[1024]; // Response buffer for server response
        ssize_t serverResponseBytes;
        
        // Receive the response from the server
        serverResponseBytes = read(serverSockets[currentServer], serverResponse,sizeof(serverResponse));
        printf("Received from server %d: %s\n", currentServer + 1, serverResponse);
        
        // Send the response back to the client
        write(clientSocket, serverResponse, serverResponseBytes);
        printf("Sent response to client: %s\n", serverResponse);
        
        // Close the client socket
        close(clientSocket);
        
        // Switch to the other server in a round-robin fashion
        currentServer = (currentServer + 1) % SERVER_COUNT;
    }
   
    // Close sockets and clean up (not reached in this simplified example)
    close(loadBalancerSocket);
    close(serverSockets[0]);
    close(serverSockets[1]);
    return 0;
}