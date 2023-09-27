void Tictactoc::set_step(const char str){
     if(str == 'X' || str == 'O'){
         m_step = str;
       }else{
        throw("You entered an error, please enter X or O");
       }
}
