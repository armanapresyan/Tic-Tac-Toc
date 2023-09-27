#include "tictactoc.h"
#include <iostream>
#include <vector>
#include <fstream> 
#include <cstring>
#include <string>
#include <sstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <fstream> 

#define PORT 8080
#define SERVER_IP "127.0.0.1" 



Tictactoc::Tictactoc(): m_size{3}{
    m_cell = new Boardcell*[m_size];
    for (int i = 0; i < m_size; ++i) {
        m_cell[i] = new Boardcell[m_size];
    }
}

void Tictactoc::print(){
     for (int i = 0; i < m_size; ++i) {
        for (int j = 0; j < m_size; ++j) {
            if (j != 0) {
                std::cout << "|"; 
            }
            std::cout << "|_" << m_cell[i][j].get_step() << "_|"; 
        }
        std::cout << std::endl;
    }
}

char Tictactoc::checkWinner(){
   for (int i = 0; i < m_size; ++i) {
        if (m_cell[i][0].get_step() == m_cell[i][1].get_step() &&
            m_cell[i][1].get_step() == m_cell[i][2].get_step() &&
            m_cell[i][0].get_step() != ' ') {
            return m_cell[i][0].get_step();
        }
    }

    
    for (int j = 0; j < m_size; ++j) {
        if (m_cell[0][j].get_step() == m_cell[1][j].get_step() &&
            m_cell[1][j].get_step() == m_cell[2][j].get_step() &&
            m_cell[0][j].get_step() != ' ') {
            return m_cell[0][j].get_step();
        }
    }

    
    if (m_cell[0][0].get_step() == m_cell[1][1].get_step() &&
        m_cell[1][1].get_step() == m_cell[2][2].get_step() &&
        m_cell[0][0].get_step() != ' ') {
        return m_cell[0][0].get_step();
    }
    if (m_cell[0][2].get_step() == m_cell[1][1].get_step() &&
        m_cell[1][1].get_step() == m_cell[2][0].get_step() &&
        m_cell[0][2].get_step() != ' ') {
        return m_cell[0][2].get_step();
    }

    return ' '; 
}



void Tictactoc::send_socket(int row, int col) {


    std::ofstream save_file("save.txt"); 
    
    if (!save_file) {
        std::cerr << "Error opening the file." << std::endl;
        return;
    }
    
    save_file << row << col;

    save_file.close();

    if (!save_file.good()) {
        std::cerr << "Error closing the file." << std::endl;
    } else {
        std::cout << "File 'save.txt' has been saved." << std::endl;
    }

    
    int client_socket;
    struct sockaddr_in server_address;
    char buffer[1024] = {0};

    
    

    // Create socket
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    
    if (inet_pton(AF_INET, SERVER_IP, &server_address.sin_addr) <= 0) {
        perror("Invalid address/Address not supported");
        exit(EXIT_FAILURE);
    }

   
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

   
  std::ifstream read_file("save.txt");
if (!read_file) {
    std::cerr << "Error opening the file" << std::endl;
    exit(EXIT_FAILURE);
}

std::string line;
while (std::getline(read_file, line)) {
    const char* cstr = line.c_str();
    send(client_socket, cstr, strlen(cstr), 0);
    printf("Sent: %s\n", cstr);
}

read_file.close();

    // Receive a response from the server
       read(client_socket, buffer, sizeof(buffer));
    int i = buffer[0] - '0';
    int j = buffer[1] - '0';
    i--;
    j--;
    m_cell[i][j].set_step('O');
    printf("Received: %s\n", buffer);

    close(client_socket);

}



void Tictactoc::play(){
    int step = 0;
    char currentPlayer = 'X';
    std::vector<char> coordinates;
    while (true) {
        int row, col;
        std::cout << "Player " << currentPlayer << ", enter your move (row and column): ";
        std::cin >> row >> col;

       if (row < 1 || row > m_size || col < 1 || col > m_size) {
          std::cout << "Invalid move. Try again." << std::endl;
           continue; 
       }

       if(m_cell[row - 1][col - 1].get_step() == 'X' || m_cell[row - 1][col - 1].get_step() == 'O'){
          std::cout << "the place with the number you want is collided, try to enter another coordinate: " << std::endl;
           continue; 
       }


        m_cell[row - 1][col - 1].set_step(currentPlayer);
        if(currentPlayer != 'O'){
            send_socket(row, col);
        }
       
        step++;
        print(); 

        char winner = checkWinner();
        if (winner != ' ') {
            if (winner == 'X' || winner == 'O') {
                std::cout << "Player " << winner << " wins!" << std::endl;
                break;            } 
           
        }
     
         if (step == m_size * m_size) {
            std::cout << "It's a tie" << std::endl;
            break;
        }
       
    }

   
}


Tictactoc::~Tictactoc(){
   for(int i = 0; i < m_size; ++i){
    delete m_cell[i];
   }
   delete m_cell;
}
