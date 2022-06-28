#ifndef _H_TICTACTOE_
#define _H_TICTACTOE_

typedef unsigned short  uint16_t;
typedef unsigned char   uint8_t;


class CTictactoe
{
    public:
        static CTictactoe& get_instance();
        
    public:
        void initialize();
        void finalize();
        void run();

    public:
        uint16_t get_winner();
        void     print_board();
        bool     get_current_player();


    private:
        static CTictactoe* p_instance;
        static uint16_t    reference_counter;

    private:
        CTictactoe();
       ~CTictactoe();

        static void release_instance();
    
    private:
        uint16_t winner;
        uint16_t player[2];
        bool     current_player;
        
    private:
        bool     game_over();
        bool     move( uint16_t index );
        
        inline uint16_t  get_input();

};

#endif // _H_TICTACTOE_