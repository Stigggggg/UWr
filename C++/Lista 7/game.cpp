#include<iostream>
#include"game.hpp"
using namespace std;

game::Game::Game(char user_mark, char ai_mark): board(), ai(), user_mark(user_mark), ai_mark(ai_mark), user_turn(true) {}

void game::Game::display()
{
    cout<<"Plansza:"<<endl;
    cout<<"  A B C"<<endl;
    for(int i=0; i<3; i++)
    {
        cout<<i+1<<" ";
        for(int j=0; j<3; j++)
        {
            cout<<board.get_mark(i+1,'A'+j)<<" ";
        }
        cout<<endl;
    }
}

pair<int,char> game::Game::get_user_move()
{
    while(true)
    {
        cout<<"Twoj ruch: ";
        string ruch;
        cin>>ruch;
        if(ruch.length()!=2)
        {
            clog<<"Nie ma takiego ruchu. Sprobuj jeszcze raz. "<<endl;
            continue;
        }
        int wiersz=ruch[0]-'0';
        char kolumna=ruch[1];
        if(wiersz<1 || wiersz>3 || kolumna<'A' || kolumna>'C')
        {
            clog<<"Nie ma takiego pola. Sprobuj jeszcze raz"<<endl;
            continue;
        }
        if(board.get_mark(wiersz,kolumna)!='-')
        {
            clog<<"To pole jest juz zajete. Sprobuj jeszcze raz. "<<endl;
            continue;
        }
        return make_pair(wiersz,kolumna);
    }
}

void game::Game::make_move(pair<int,char> move, char mark)
{
    board.mark(move.first,move.second,mark);
    display();
}

void game::Game::play()
{
    cout<<"Witamy w grze! "<<endl;
    display();
    while(true)
    {
        if(user_turn)
        {
            pair<int,char> move=get_user_move();
            make_move(move,user_mark);
            if(board.check_win()!='-')
            {
                break;
            }
            user_turn=false;
        }
        else
        {
            cout<<"Ruch komputera: "<<endl;
            pair<int,char> move=ai.get_move(board);
            cout<<move.first<<move.second<<endl;
            make_move(move,ai_mark);
            if(board.check_win()!='-')
            {
                break;
            }
            user_turn=true;
        }
    }
    char winner=board.check_win();
    cout<<"Koniec gry. ";
    if(winner==user_mark)
    {
        cout<<"Wygrales! "<<endl;
    }
    else if(winner==ai_mark)
    {
        cout<<"Przegrales! "<<endl;
    }
    else cout<<"Remis! "<<endl;
}
