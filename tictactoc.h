#ifndef BOARD
#define BOARD
#include "boardcell.h"




class Tictactoc{
public:
  Tictactoc();  
  ~Tictactoc();
public:
  void print();
  void play();
  char checkWinner();
  void send_socket(int row, int col);
private:
  int m_size;
  Boardcell** m_cell;  
};





#endif //BOARD