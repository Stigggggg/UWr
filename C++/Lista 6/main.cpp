#include<iostream>
#include"wyrazenia.hpp"
using namespace std;

int main()
{
    Wyrazenie *w = new Odejmij(new Pi(),new Dodaj(new Liczba(2),new Mnoz(new Zmienna("x"),new Liczba(7))));
    Wyrazenie *w1=new Dziel(new Mnoz(new Odejmij(new Zmienna("x"),new Liczba(1)),new Zmienna("x")),new Liczba(2));
    Wyrazenie *w2=new Dziel(new Dodaj(new Liczba(3),new Liczba(5)),new Dodaj(new Liczba(2),new Mnoz(new Zmienna("x"),new Liczba(7))));
    Wyrazenie *w3=new Odejmij(new Dodaj(new Mnoz(new Zmienna("x"), new Liczba(7)),new Liczba(2)),new Dodaj(new Mnoz(new Zmienna("y"),new Liczba(3)),new Liczba(5)));
    Zmienna::dodaj("x",0);
    Zmienna::dodaj("y",0);
    for(double i=0; i<=1; i+=0.01)
    {
        Zmienna::zmien("x",i);
        Zmienna::zmien("y",i);
        cout<<w->oblicz()<<endl;
        // cout<<w1->oblicz()<<endl;
        // cout<<w2->oblicz()<<endl;
        // cout<<w3->oblicz()<<endl;
    }
    cout<<w->zapis();
    return 0;
}