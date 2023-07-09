#include<iostream>
#include<stdexcept>
#include "game_state.hpp"
using namespace std;

game_state::GameState::GameState()
{
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            board[i][j]='-';
        }
    }
}

void game_state::GameState::mark(int n, char m, char znak)
{
    if(n>3 || n<1 || m<'A' || m>'C')
    {
        throw std::out_of_range("Nie ma takiego indeksu");
    }
    if(znak!='X' && znak!='O')
    {
        throw std::invalid_argument("Nieprawidlowy znak");
    }
    if(board[n-1][m-'A']!='-')
    {
        throw std::invalid_argument("Pole zajete");
    }
    board[n-1][m-'A']=znak;
}

bool game_state::GameState::is_full()
{
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            if(board[i][j]=='-')
            {
                return false;
            }
        }
    }
    return true;
}

char game_state::GameState::check_win()
{
    for(int i=0; i<3; i++)
    {
        if(board[i][0]!='-' && board[i][0]==board[i][1] && board[i][1]==board[i][2])
        {
            return board[i][0];
        }
    }
    for(int j=0; j<3; j++)
    {
        if(board[0][j]!='-' && board[0][j]==board[1][j] && board[1][j]==board[2][j])
        {
            return board[0][j];
        }
    }
    if(board[0][0]!='-' && board[0][0]==board[1][1] && board[1][1]==board[2][2])
    {
        return board[0][0];
    }
    if(board[2][0]!='-' && board[0][2]==board[1][1] && board[1][1]==board[2][0])
    {
        return board[0][2];
    }
    if(is_full())
    {
        return 'D';
    }
    return '-';
}

char game_state::GameState::get_mark(int n, char m)
{
    return board[n-1][m-'A'];
}





