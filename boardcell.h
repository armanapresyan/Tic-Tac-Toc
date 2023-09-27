#ifndef BOARDCELL
#define BOARDCELL
#include <iostream>

class Boardcell{
  public:
    Boardcell();
    Boardcell(const char str);


  public:
    void set_step(const char str);

    char get_step() const;

  private:
   char m_step;
};


std::ostream& operator<<(std::ostream& os, const Boardcell& s);

#endif //BOARDCELL