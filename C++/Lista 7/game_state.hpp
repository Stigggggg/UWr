#include<iostream>

namespace game_state
{
    class GameState
    {
        private:
            char board[3][3];
        public:
            GameState();
            void mark(int n, char m, char znak);
            bool is_full();
            char check_win();
            char get_mark(int n, char m);
    };
}
