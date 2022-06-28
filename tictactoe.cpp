#include "tictactoe.h"
#include <iostream>

CTictactoe* CTictactoe::p_instance = nullptr;
uint16_t    CTictactoe::reference_counter;


CTictactoe& CTictactoe::get_instance()
{
    if ( CTictactoe::p_instance == nullptr )    CTictactoe::p_instance = new  CTictactoe;
    CTictactoe::reference_counter++;
    return *p_instance;
}


void CTictactoe::release_instance()
{
    delete CTictactoe::p_instance;
    CTictactoe::p_instance = nullptr;
    return;
}



CTictactoe::CTictactoe()
{
    CTictactoe::reference_counter = 0;
    initialize();
}


CTictactoe::~CTictactoe()
{
    if ( CTictactoe::p_instance != nullptr ) delete CTictactoe::p_instance;
    CTictactoe::p_instance = nullptr;
}



void CTictactoe::initialize()
{
    player[0] = 0;
    player[1] = 0;
    winner    = 0;
    current_player = true;
    return;
}

void CTictactoe::finalize()
{
    CTictactoe::reference_counter--;
    if ( CTictactoe::reference_counter == 0 &&  !(CTictactoe::p_instance == nullptr) )
    {
        CTictactoe::release_instance();
    }
    return;    
}


void CTictactoe::run()
{
    do {
        std::cout << "it's " << ( ! get_current_player() ? 'o' : 'x' );   // who is next
        std::cout << "'s move:\n";

        while (! move( get_input() ) ) {};

        print_board();
        std::cout << '\n';

    } while ( ! game_over() );

    std::cout << "congratulations! " << (get_current_player() ? 'o' : 'x' ) << " has won" << std::endl;

    return;
}




inline uint16_t CTictactoe::get_input()
{
    uint16_t field;
    std::cout << "\tplease enter the number of a valid field: ";
    std::cin >> field;
    return field;
}



bool CTictactoe::move( uint16_t index ){

    // is move valid?  i.e. test if index is already occupied
    if ( ( player[0] | player[1] ) & ( 1 << index )  || index > 8) return false;

    current_player = !current_player;
    player[ current_player ] = player[ current_player ] | (1 << index);

    return true;
}



bool CTictactoe::game_over(){
    
    if ( ( player[0] | player[1] ) == 0b111111111 ) return true;

    short winning_patterns[8] = {
        0b000000111,
        0b000111000,
        0b111000000,
        0b100100100,
        0b010010010,
        0b001001001,
        0b100010001,
        0b001010100
    };
    for (int i = 0; i < 8; i++){
        if ( ( winning_patterns[i] & player[ current_player ] ) == winning_patterns[i] ){
            winner = winning_patterns[i];
            return true;
        }
    };
    return false;
}



bool CTictactoe::get_current_player(){
    return current_player;
}



uint16_t CTictactoe::get_winner(){
    return winner;
}



void CTictactoe::print_board(){
    for ( char i = 0; i < 9; i++ ){
        if ( i % 3 == 0)
            std::cout << std::endl;
        if      ( player[0] & (1 << i) )
            std::cout << 'x';
        else if ( player[1] & (1 << i) )
            std::cout << 'o';
        else
            std::cout << '.';
    }
    std::cout << std::endl;
    return;
}