#include "tictactoe.h"
#include <iostream>


int main( void ){
    CTictactoe& r_tictactoe = CTictactoe::get_instance();
    r_tictactoe.initialize();
    r_tictactoe.run();
    r_tictactoe.finalize();
    CTictactoe::release_instance();
    return 0;
}