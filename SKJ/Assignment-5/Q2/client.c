#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#define MAX_CLIENTS 10
struct ClientInfo
{
    int node_no;
    char ip_address[20];
    int port_no;
};
int main()
{
    int client_socket;
    struct sockaddr_in server_addr;
    struct ClientInfo my_info;
    // Create a socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0)
    {
        perror("Socket creation error");
        exit(1);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345);                  // Use the same port as the server
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Use the server's IP
    // Connect to the server
    if (connect(client_socket, (struct sockaddr *)&server_addr,
                sizeof(server_addr)) < 0)
    {
        perror("Connection error");
        exit(1);
    }
    // Prepare and send client information to the server
    my_info.node_no = 4;                                                     // Change this to your node number
    strncpy(my_info.ip_address, "192.168.0.10", sizeof(my_info.ip_address)); // Change to your IP
    my_info.port_no = 8080;                                                  // Change to your port
    send(client_socket, &my_info.node_no, sizeof(my_info.node_no), 0);
    send(client_socket, my_info.ip_address, sizeof(my_info.ip_address), 0);
    send(client_socket, &my_info.port_no, sizeof(my_info.port_no), 0);
    // Receive and update the client's master table
    struct ClientInfo updated_table[MAX_CLIENTS];
    recv(client_socket, updated_table, sizeof(updated_table), 0);
    printf("Updated Master Table:\n");
    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        if (updated_table[i].node_no != 0)
        {
            printf("Node No: %d, IP Address: %s, Port No: %d\n",
                   updated_table[i].node_no, updated_table[i].ip_address, updated_table[i].port_no);
        }
    }
    close(client_socket);
    return 0;
}
