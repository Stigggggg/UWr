#include<iostream>
#include "ai.hpp"

namespace game
{
    class Game
    {
        private:
            game_state::GameState board;
            ai::AI ai;
            bool user_turn;
            char user_mark;
            char ai_mark;
            void display();
            std::pair<int,char> get_user_move();
            void make_move(std::pair<int,char> move, char mark);
        public:
            Game(char user_mark, char ai_mark);
            void play();
    };
}
