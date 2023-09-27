#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 8080
#define MAX_BUFFER_SIZE 1024

char m_cell[3][3];

void initialize_board() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            m_cell[i][j] = '_';
        }
    }
}

void print_board(char * buffer) {
    int row = buffer[0] - '0'; 
    int col = buffer[1] - '0';
    row--;
    col--; 
    m_cell[row][col] = 'X';
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (j != 0) {
                printf("|");
            }
            printf("|_%c_|", m_cell[i][j]);
        }
        printf("\n");
    }
}



int main() {
    int server_socket, new_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_len = sizeof(client_address);
    char buffer[MAX_BUFFER_SIZE] = {0};
    
    initialize_board();

    // Create socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up server address structure
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    // Bind socket to address
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) == -1) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        
        if ((new_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_len)) == -1) {
            perror("Accept failed");
            continue; 
        }

        // Read data from client
        ssize_t bytes_received = read(new_socket, buffer, MAX_BUFFER_SIZE);
        if (bytes_received <= 0) {
            close(new_socket);
            continue;
        }

        buffer[bytes_received] = '\0'; 
        print_board(buffer);
        printf("Received: %s\n", buffer);

        // Send a message back to the client
        char row;
        char col;
        printf("player 2: specify the appropriate coordinate to place O: ");
        scanf(" %c", &row);
        scanf(" %c", &col);
        char str[3];
        str[0] = row;
        str[1] = col;
        str[2] = '\0';
        send(new_socket, str, strlen(str), 0);
        int i = row - '0';
        int j = col - '0';
        --i;
        --j;
        m_cell[i][j] = 'O';

        close(new_socket);
    }

   
    return 0;
}
