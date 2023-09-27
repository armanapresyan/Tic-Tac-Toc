// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>
// #include <unistd.h>

// #define PORT 8080
// #define SERVER_IP "192.168.0.12" // Replace with the server's local IP

// int main() {
//     int client_socket;
//     struct sockaddr_in server_address;
//     char buffer[1024] = {0};
//     const char* hello_message = "Hello from client";

//     // Create socket
//     if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
//         perror("Socket creation failed");
//         exit(EXIT_FAILURE);
//     }

//     // Set up server address structure
//     server_address.sin_family = AF_INET;
//     server_address.sin_port = htons(PORT);

//     // Convert IPv4 address from text to binary
//     if (inet_pton(AF_INET, SERVER_IP, &server_address.sin_addr) <= 0) {
//         perror("Invalid address/Address not supported");
//         exit(EXIT_FAILURE);
//     }

//     // Connect to the server
//     if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
//         perror("Connection failed");
//         exit(EXIT_FAILURE);
//     }

//     // Send a message to the server
//     send(client_socket, hello_message, strlen(hello_message), 0);
//     printf("Hello message sent\n");

//     // Receive a response from the server
//     read(client_socket, buffer, sizeof(buffer));
//     printf("Received: %s\n", buffer);

//     close(client_socket);

//     return 0;
// }
