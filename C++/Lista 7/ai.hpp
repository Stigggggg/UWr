#include<iostream>
#include"game_state.hpp"

namespace ai
{
    class AI
    {
        public:
            AI();
            // int evaluate(game_state::GameState &board, char user_mark);
            std::pair<int,char> get_move(game_state::GameState &state);
            // int minimax(game_state::GameState &board, char player_mark, bool is_max);
    };
}

