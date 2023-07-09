#include<iostream>
#include<algorithm>
using namespace std;

string konwersja(int n, int system)
{
    string wynik;
    while(n>0)
    {
        if(n%system<10)
        {
            wynik+=(n%system)+'0';
        }
        else
        {
            wynik+=(n%system)+'A'-10;
        }
        n/=system;
    }
    reverse(wynik.begin(),wynik.end());
    return wynik;
}

int main()
{
    int n,system;
    cin>>n>>system;
    cout<<konwersja(n,system);
    return 0;
}