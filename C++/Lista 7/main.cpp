#include<iostream>
#include "game.hpp"
using namespace std;

int main()
{
    char user,ai;
    cout<<"Wybierz swoj symbol: "<<endl;
    cin>>user;
    if(user=='X')
    {
        ai='O';
        game::Game g(user,ai);
        g.play();
    }
    else if(user=='O')
    {
        ai='X';
        game::Game g(user,ai);
        g.play();
    }
    else
    {
        while(user!='X' && user !='O')
        {
            clog<<"Wybierz poprawny symbol "<<endl;
            cin>>user;
        }
        game::Game g(user,ai);
        g.play();
    }
    return 0;
}
