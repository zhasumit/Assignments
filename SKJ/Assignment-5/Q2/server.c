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
struct ClientInfo master_table[MAX_CLIENTS];
int num_clients = 0;
void updateMasterTable(int node_no, char *ip_address, int port_no)
{
    if (num_clients < MAX_CLIENTS)
    {
        master_table[num_clients].node_no = node_no;
        strncpy(master_table[num_clients].ip_address, ip_address,
                sizeof(master_table[num_clients].ip_address));
        master_table[num_clients].port_no = port_no;
        num_clients++;
    }
    else
    {
        printf("Master table is full.\n");
    }
}
int main()
{
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    int node_no;
    char client_ip[20];
    int client_port;
    // Initialize master table (you can pre-fill this with initial data)
    // Create a socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0)
    {
        perror("Socket creation error");
        exit(1);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345); // Use your desired port
    server_addr.sin_addr.s_addr = INADDR_ANY;
    // Bind the socket
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) <
        0)
    {
        perror("Binding error");
        exit(1);
    }
    // Listen for clients
    if (listen(server_socket, 10) == 0)
    {
        printf("Listening...\n");
    }
    else
    {
        perror("Listening error");
        exit(1);
    }
    // Accept client connections and update the master table
    addr_size = sizeof(client_addr);
    while (1)
    {
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr,
                               &addr_size);
        // Receive client information
        recv(client_socket, &node_no, sizeof(node_no), 0);
        recv(client_socket, client_ip, sizeof(client_ip), 0);
        recv(client_socket, &client_port, sizeof(client_port), 0);
        // Update master table with client information
        updateMasterTable(node_no, client_ip, client_port);
        // Send the updated table back to the client
        send(client_socket, master_table, sizeof(master_table), 0);
        close(client_socket);
    }
    close(server_socket);
    return 0;
}
