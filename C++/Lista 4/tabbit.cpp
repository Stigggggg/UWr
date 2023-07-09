#include<iostream>
#include<cstdint>
#include<stdexcept>
#include<string>
using namespace std;
#include"tabbit.hpp"

tab_bit::tab_bit(int rozm): dl(rozm)
{
    int n=rozm/rozmiarslowa;
    if(rozm%rozmiarslowa!=0)
    {
        n++;
    }
    tab=new slowo[n]();
}

tab_bit::tab_bit(slowo wzorzec): dl(rozmiarslowa)
{
    tab=new slowo[1];
    tab[0]=wzorzec;
}

tab_bit::tab_bit(initializer_list<bool> l) : tab_bit((int) l.size())
{
    int i=0; 
    for(bool b : l)
    {
        pisz(i++,b);
    }
}

tab_bit::tab_bit(const tab_bit &tb): dl(tb.dl)
{
    int n=dl/rozmiarslowa;
    if(dl%rozmiarslowa!=0)
    {
        n++;
    }
    tab=new slowo[n];
    for(int i=0; i<n; i++)
    {
        tab[i]=tb.tab[i];
    }
}

tab_bit::tab_bit(tab_bit&& tb): dl(tb.dl), tab(tb.tab)
{
    tb.dl=0;
    tb.tab=nullptr;
}

tab_bit& tab_bit::operator=(const tab_bit& tb)
{
    if(this==&tb)
    {
        return *this;
    }
    delete[] tab;
    dl=tb.dl;
    int n=dl/rozmiarslowa;
    if(dl%rozmiarslowa!=0)
    {
        n++;
    }
    tab=new slowo[n];
    for(int i=0; i<n; i++)
    {
        tab[i]=tb.tab[i];
    }
    return *this;
}

tab_bit& tab_bit::operator=(tab_bit&& tb)
{
    if(this==&tb)
    {
        return *this;
    }
    delete[] tab;
    dl=tb.dl;
    tab=tb.tab;
    tb.dl=0;
    tb.tab=nullptr;
    return *this;
}

tab_bit::~tab_bit()
{
    delete[] tab;
}

bool tab_bit::czytaj(int i) const
{
    if(i<0 || i>=dl)
    {
        throw out_of_range("Indeks poza zakresem");
    }
    int slowonr=i/rozmiarslowa;
    int bitnr=i%rozmiarslowa;
    return (tab[slowonr]&(1ull<<bitnr))!=0;
}

bool tab_bit::pisz(int i, bool b)
{
    if(i<0 || i>=dl)
    {
        throw out_of_range("Indeks poza zakresem");
    }
    int slowonr=i/rozmiarslowa;
    int bitnr=i%rozmiarslowa;
    slowo maska=1ull<<bitnr;
    if(b==1)
    {
        tab[slowonr]|=maska;
    }
    else
    {
        tab[slowonr]&=~maska;
    }
    return b;
}

bool tab_bit::operator[](int i) const
{
    return czytaj(i);
}

tab_bit::ref tab_bit::operator[](int i)
{
    return ref(*this, i);
}

inline int tab_bit::rozmiar() const
{
    return dl;
}

tab_bit tab_bit::operator|(const tab_bit& tb) const
{
    if(rozmiar()!=tb.rozmiar())
    {
        throw invalid_argument("Niezgodnosc rozmiarow");
    }
    tab_bit wynik(rozmiar());
    for(int i=0; i<dl; i++)
    {
        wynik.pisz(i, czytaj(i)|tb.czytaj(i));
    }
    return wynik;
}

tab_bit tab_bit::operator&(const tab_bit& tb) const
{
    if(rozmiar()!=tb.rozmiar())
    {
        throw invalid_argument("Niezgodnosc rozmiarow");
    }
    tab_bit wynik(rozmiar());
    for(int i=0; i<dl; i++)
    {
        wynik.pisz(i, czytaj(i)&tb.czytaj(i));
    }
    return wynik;
}

tab_bit tab_bit::operator^(const tab_bit& tb) const
{
    if(rozmiar()!=tb.rozmiar())
    {
        throw invalid_argument("Niezgodnosc rozmiarow");
    }
    tab_bit wynik(rozmiar());
    for(int i=0; i<dl; i++)
    {
        wynik.pisz(i, czytaj(i)^tb.czytaj(i));
    }
    return wynik;
}

tab_bit& tab_bit::operator|=(const tab_bit& tb)
{
    if(rozmiar()!=tb.rozmiar())
    {
        throw invalid_argument("Niezgodnosc rozmiarow");
    }
    for(int i=0; i<dl; i++)
    {
        pisz(i, czytaj(i)|tb.czytaj(i));
    }
    return *this;
}

tab_bit& tab_bit::operator&=(const tab_bit& tb)
{
    if(rozmiar()!=tb.rozmiar())
    {
        throw invalid_argument("Niezgodnosc rozmiarow");
    }
    for(int i=0; i<dl; i++)
    {
        pisz(i, czytaj(i)&tb.czytaj(i));
    }
    return *this;
}

tab_bit& tab_bit::operator^=(const tab_bit& tb)
{
    if(rozmiar()!=tb.rozmiar())
    {
        throw invalid_argument("Niezgodnosc rozmiarow");
    }
    for(int i=0; i<dl; i++)
    {
        pisz(i, czytaj(i)^tb.czytaj(i));
    }
    return *this;
}

tab_bit tab_bit::operator!() const
{
    tab_bit wynik(dl);
    for(int i=0; i<dl; i++)
    {
        wynik.pisz(i, !czytaj(i));
    }
    return wynik;
}

istream& operator>>(istream& we, tab_bit& tb)
{
    string s;
    we>>s;
    int dl=s.length();
    tb=tab_bit(dl);
    for(int i=0; i<dl; i++)
    {
        if(s[i]=='1')
        {
            tb.pisz(i,true);
        }
        else if(s[i]=='0')
        {
            tb.pisz(i,false);
        }
        else throw invalid_argument("Niepoprawna tablica bitow");
    }
    return we;
}

ostream& operator<<(ostream& wy, const tab_bit& tb)
{
    for(int i=0; i<tb.dl; i++)
    {
        wy<<(tb.czytaj(i)==1? '1' : '0');
    }
    return wy;
}

tab_bit::ref::operator bool() const
{
    return tablica.czytaj(indeks);
}

tab_bit::ref& tab_bit::ref::operator=(bool b)
{
    tablica.pisz(indeks,b);
    return *this;
}

tab_bit::ref& tab_bit::ref::operator=(const ref& r)
{
    if(this!=&r) 
    {
        bool b=r.operator bool(); 
        tablica.pisz(indeks,b); 
    }
    return *this;
}