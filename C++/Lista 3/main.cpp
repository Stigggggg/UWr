#include<iostream>
#include"historia.hpp"
using namespace std;

int main()
{
    Liczba l1;
    //Testy konstruktora domyslnego
    cout<<l1.get_val()<<endl; // powinno wypisac 0
    l1.set_val(5.0);
    cout<<l1.get_val()<<endl; // powinno wypisac 5
    //Testy konstruktora i przypisania kopiujacego
    Liczba l2(3.0);
    l2.set_val(5.0);
    Liczba l3(l2);
    cout<<l2.get_val()<<endl; // powinno wypisac 5
    Liczba l4;
    l4=l3;
    cout<<l4.get_val()<<endl; // powinno wypisac 5
    //Testy undo_val() na 3 wartosciach
    Liczba l(2.0);
    l.set_val(3.0);
    l.set_val(4.0);
    cout<<l.get_val()<<endl;// powinno wypisac 4
    cout<<l.undo_val()<<endl; // powinno wypisac 3
    cout<<l.undo_val()<<endl;// powinno wypisac 2
    // //Testy undo na wiecej niz 3 wartosciach (test errora)
    // Liczba l1(2.0);
    // l1.set_val(3.0);
    // l1.set_val(4.0);
    // l1.set_val(5.0);
    // cout<<l1.get_val()<<endl; //powinno byc 5
    // cout<<l1.undo_val()<<endl; //powinno byc 4
    // cout<<l1.undo_val()<<endl; //powinno byc 3
    // cout<<l1.undo_val()<<endl; //powinien byc error
    return 0;
}