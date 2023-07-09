#include<iostream>
#include"wymierna.hpp"
#include<algorithm>
#include<cmath>
#include<map>

obliczenia::wymierna::wymierna(int l, int m): licz(l), mian(m)
{
    if(m==0)
    {
        throw dzielenie_przez_0("Dzielenie przez zero");
    }
    if(m<0)
    {
        licz=-licz;
        mian=-mian;
    }
    int gcd=__gcd(abs(licz),abs(mian));
    licz/=gcd;
    mian/=gcd;
}

obliczenia::wymierna::wymierna(int l): wymierna(l,1) {}

obliczenia::wymierna::wymierna(): wymierna(0,1) {}

int obliczenia::wymierna::get_licz() const
{
    return licz;
}

int obliczenia::wymierna::get_mian() const
{
    return mian;
}

obliczenia::wymierna obliczenia::wymierna::operator-() const
{
    wymierna wynik(-licz,mian);
    return wynik;
}

obliczenia::wymierna obliczenia::wymierna::operator!() const
{
    wymierna wynik(mian,licz);
    return wynik;
}

obliczenia::wymierna obliczenia::wymierna::operator+(const wymierna &w)
{
    int l=licz*w.mian+w.licz*mian;
    int m=mian*w.mian;
    if((l>0 && l>INT_MAX/m) || (l<0 && l<INT_MIN/m))
    {
        throw przekroczenie_zakresu("Przekroczenie zakresu");
    }
    return wymierna(l,m);
}

obliczenia::wymierna obliczenia::wymierna::operator-(const wymierna &w)
{
    return *this+(-w);
}

obliczenia::wymierna obliczenia::wymierna::operator*(const wymierna &w)
{
    if((licz>0 && w.licz>0 && licz>INT_MAX/w.licz) || (licz>0 && w.licz<0 && w.licz<INT_MIN/licz) || (licz<0 && w.licz>0 && licz<INT_MIN/w.licz) || (licz<0 && w.licz<0 && licz<INT_MAX/w.licz))
    {
        throw przekroczenie_zakresu("Przekroczenie zakresu");
    }
    return wymierna(licz*w.licz,mian*w.mian);
}

obliczenia::wymierna obliczenia::wymierna::operator/(const wymierna &w)
{
    return *this*(!w);
}

obliczenia::wymierna::operator double()
{
    return ((double)licz)/mian;
}

obliczenia::wymierna::operator int()
{
    return round(((double)licz)/mian);
}

ostream& obliczenia::operator<<(ostream &wy, const wymierna &w)
{
    wy<<w.get_licz();
    if(w.get_mian()!=1)
    {
        wy<<"/"<<w.get_mian();
    }
    return wy;
}

// ostream& obliczenia::operator<<(ostream &wyj, const wymierna &w)
// {
//     if(w.mian==1)
//     {
//         wyj<<w.licz;
//     }
//     else if(w.licz==0)
//     {
//         wyj<<0;
//     }
//     else
//     {
//         int calosc=w.licz/w.mian;
//         int reszta=abs(w.licz%w.mian);
//         string okres="";
//         map<int,int> mapa; //przechowuje pozycje cyfr rozwiniecia
//         if(reszta!=0) //jesli reszta niezerowa, to sprawdzamy rozwiniecie
//         {
//             wyj<<calosc<<".";
//             int pozycja=0;
//             while(reszta!=0 && mapa.find(reszta)==mapa.end()) //dopoki reszta niezerowa i sie nie powtarza
//             {
//                 mapa[reszta]=pozycja;
//                 reszta*=10;
//                 okres+=to_string(reszta/w.mian);
//                 reszta%=w.mian;
//                 pozycja++;
//             }
//             if(reszta==0) //jesli rowna zero, to wypisujemy rozwiniecie
//             {
//                 wyj<<okres;
//             }
//             else //jesli nie, to wypisujemy rozwiniecie
//             {
//                 int czesc_dziesietna=mapa[reszta]; //pozycja poczatku okresu
//                 wyj<<okres.substr(0,czesc_dziesietna)<<"("<<okres.substr(czesc_dziesietna)<<")";
//             }
//         }
//         else
//         {
//             wyj<<calosc;
//         }
//     }
//     return wyj;
// }

