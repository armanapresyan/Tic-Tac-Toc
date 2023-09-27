#include "boardcell.h"

std::ostream& operator<<(std::ostream& os, const Boardcell& s){
    os << s.get_step();
    return os;
}

Boardcell::Boardcell() = default;

Boardcell::Boardcell(const char str) : m_step{str} {}


void Boardcell::set_step(const char str){
     if(str == 'X' || str == 'O'){
         m_step = str;
       }else{
        throw("You entered an error, please enter X or O");
       }
}

char Boardcell::get_step() const {
    return m_step; 
}


