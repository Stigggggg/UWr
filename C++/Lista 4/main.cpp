#include<iostream>
#include<cstdint>
using namespace std;
#include"tabbit.hpp"

int main()
{
    tab_bit t(46); // tablica 46-bitowa (zainicjalizowana zerami)
    cout<<t<<endl;
    tab_bit u(45ull); // tablica 64-bitowa (sizeof(uint64_t)*8)
    cout<<u<<endl;
    tab_bit v(t); // tablica 46-bitowa (skopiowana z t)
    cout<<v<<endl;
    tab_bit w(4);
    w[0]=1;
    w[1]=0;
    w[2]=1;
    w[3]=1;
    tab_bit x(4);
    x[0]=1;
    x[1]=1;
    x[2]=1;
    x[3]=0;
    v[0]=1; // ustawienie bitu 0-go bitu na 1
    v[1]=v[0];
    cout<<v<<endl;
    t[45] = true; // ustawienie bitu 45-go bitu na 1
    cout<<t<<endl;
    bool b = v[1]; // odczytanie bitu 1-go
    cout<<b<<endl;
    u[45] = u[46] = u[63]; // przepisanie bitu 63-go do bitow 45-go i 46-go
    u[23]=u[35]=u[0];
    cout<<u<<endl;
    cout<<t<<endl; // wysietlenie zawartości tablicy bitów na ekranie
    cout<<(w|x)<<endl;
    cout<<(w&x)<<endl;
    cout<<(w^x)<<endl;
    cout<<(!x)<<endl;
    tab_bit d{1,0,0,1,1,1,0};
    cout<<d<<endl;
    return 0;
}