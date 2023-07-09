#include<iostream>
#include<vector>
#include "ai.hpp"
using namespace std;

// int ai::AI::evaluate(game_state::GameState &board, char player_mark)
// {
//     char winner=board.check_win();
//     if(winner==player_mark)
//     {
//         return 1;
//     }
//     else if(winner!='-')
//     {
//         return -1;
//     }
//     else return 0;
// }

// int ai::AI::minimax(game_state::GameState &board, char player_mark, bool is_max)
// {
//     int best_score;
//     if(is_max)
//     {
//         best_score=INT_MIN;
//         for(int i=1; i<=3; i++)
//         {
//             for(char j='A'; j<='C'; j++)
//             {
//                 if(board.get_mark(i,j)=='-')
//                 {
//                     game_state::GameState new_board=board;
//                     new_board.mark(i,j,player_mark);
//                     int score=minimax(new_board,player_mark,false);
//                     best_score=std::max(best_score,score);
//                 }
//             }
//         }
//     }
//     else
//     {
//         best_score=INT_MAX;
//         for(int i=1; i<=3; i++)
//         {
//             for(int j='A'; j<='C'; j++)
//             {
//                 if(board.get_mark(i,j)=='-')
//                 {
//                     game_state::GameState new_board=board;
//                     if(player_mark=='X')
//                     {
//                         new_board.mark(i,j,'X');
//                     }
//                     else
//                     {
//                         new_board.mark(i,j,'O');
//                     }
//                     int score=minimax(new_board,player_mark,true);
//                     best_score=std::min(best_score,score);
//                 }
//             }
//         }
//     }
//     return best_score;
// }

ai::AI::AI()
{
    srand(time(NULL));
}

pair<int,char> ai::AI::get_move(game_state::GameState &state)
{
    vector<pair<int,char>> free;
    for(int i=1; i<=3; i++)
    {
        for(char j='A'; j<='C'; j++)
        {
            if(state.get_mark(i,j)=='-')
            {
                free.push_back({i,j});
            }
        }
    }
    int indeks=rand()%free.size();
    return free[indeks];
}

