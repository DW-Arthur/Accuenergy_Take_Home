#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define PORT 8080

int main(int argc, char const *argv[]) {
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};
    // Message interval in seconds
    int interval = 1; 
    // Message count
    int count = 0; 
    
    // Reading command line arguments for server IP and port
    if (argc != 3) {
        printf("Usage: %s <server_ip> <server_port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    char* server_ip = argv[1];
    int server_port = atoi(argv[2]);
    
    // Creating socket file descriptor
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
    
    memset(&serv_addr, '0', sizeof(serv_addr));
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(server_port);
       
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, server_ip, &serv_addr.sin_addr)<=0) {
    printf("\nInvalid address/ Address not supported \n");
    return -1;
}

// Connecting to server
if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    printf("\nConnection Failed \n");
    return -1;
}

// Sending and receiving messages from the server
while(1) {
    // Sending message to the server
    count++;
    send(sock, hello, strlen(hello), 0);
    printf("Message %d sent\n", count);
    
    // Receiving message from the server
    valread = read(sock, buffer, 1024);
    printf("Server message: %s\n", buffer);
    memset(buffer, 0, sizeof(buffer));
    
    // Sleeping for the specified interval
    sleep(interval);
}
return 0;
