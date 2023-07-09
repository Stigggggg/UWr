#include<iostream>
#include<stdexcept>
#include<cmath>
#include "piksele.hpp"
using namespace std;


kolor::kolor(): r(0), g(0), b(0){}
kolor::kolor(int _r, int _g, int _b)
{
    if(_r<0 || _r>255 || _g<0 || _g>255 || _b<0 || _b>255)
    {
        throw out_of_range("Nieodpowiednia wartosc RGB");
    }
    r=_r;
    g=_g;
    b=_b;
}
int kolor::get_r() const
{
    return r;
}
int kolor::get_g() const
{
    return g;
}
int kolor::get_b() const
{
    return b;
}
void kolor::set_r(int _r)
{  
    if(_r<0 || _r>255)
    {
        throw out_of_range("Nieodpowiednia wartosc RGB");
    }
    r=_r;
}
void kolor::set_g(int _g)
{   
    if(_g<0 || _g>255)
    {
        throw out_of_range("Nieodpowiednia wartosc RGB");
    }
    g=_g;
}
void kolor::set_b(int _b)
{   
    if(_b<0 || _b>255)
    {
        throw out_of_range("Nieodpowiednia wartosc RGB");
    }
    b=_b;
}
void kolor::jasniej(int x)
{
    r+=x;
    g+=x;
    b+=x;
}
void kolor::ciemniej(int x)
{
    r-=x;
    g-=x;
    b-=x;
}
kolor kolor::srednia(const kolor& k1, const kolor& k2)
{
    return kolor((k1.r + k2.r)/2,(k1.g + k2.g)/2,(k1.b + k2.b)/2);
}

kolortransparentny::kolortransparentny(): alfa(255){}
kolortransparentny::kolortransparentny(int _r, int _g, int _b, int _alfa): kolor(_r, _g, _b)
{
    if(_alfa>255 || _alfa<0)
    {
        throw out_of_range("Nieodpowiednia wartosc przezroczystosci");
    }
    alfa=_alfa;
}
int kolortransparentny::get_alfa()
{
    return alfa;
}
void kolortransparentny::set_alfa(int _alfa)
{
    alfa=_alfa;
}

kolornazwany::kolornazwany(): nazwa(""){}
kolornazwany::kolornazwany(int _r, int _g, int _b, const string& _nazwa): kolor(_r, _g, _b)
{
    for(auto c: nazwa)
    {
        if(!islower(c))
        {
            throw invalid_argument("Nazwa ma zawierac tylko male litery");
        }
    }
    nazwa=_nazwa;
}
const string& kolornazwany::get_nazwa() const
{
    return nazwa;
}
void kolornazwany::set_nazwa(const string& _nazwa)
{
    for(auto c: _nazwa)
    {
        if(!islower(c))
        {
            throw invalid_argument("Nazwa ma zawierac tylko male litery");
        }
    }
    nazwa=_nazwa;
}

kolornt::kolornt(){}
kolornt::kolornt(int _r, int _g, int _b, int _alfa, const string& _nazwa): kolor(_r, _g, _b), kolortransparentny(_r, _g, _b, _alfa), kolornazwany(_r, _g, _b, _nazwa){}



piksel::piksel(int _x, int _y)
{
    if(_x<0 || _x>=ekran_x || _y<0 || _y>=ekran_y) 
    {
        throw out_of_range("Piksel poza ekranem");
    }
    x=_x;
    y=_y;
}
int piksel::get_x() const 
{
    return x;
}
int piksel::get_y() const 
{
    return y;
}
void piksel::set_x(int _x) 
{
    if(x<0 || x>ekran_x) 
    {
        throw std::out_of_range("Wspolrzedna x poza ekranem");
    }
    x=_x;
}
void piksel::set_y(int _y) 
{
    if(y<0 || y >ekran_y) 
    {
        throw std::out_of_range("Wspolrzedna y poza ekranem");
    }
    y=_y;
}
int piksel::odleglosc_l() const
{
    return x;
}
int piksel::odleglosc_r() const
{
    return ekran_x-x;
}
int piksel::odleglosc_g() const
{
    return y;
}
int piksel::odleglosc_d() const
{
    return ekran_y-y;
}
void piksel::przesun(int dx, int dy)
{
    if(x+dx<0 || x+dx>=ekran_x || y+dy<0 || y+dy>=ekran_y)
    {
        throw out_of_range("Piksel poza ekranem");
    }
    x+=dx;
    y+=dy;
}

pikselkolorowy::pikselkolorowy(int _x, int _y, int _r, int _g, int _b, int alfa): piksel(_x,_y), k(_r,_g,_b,alfa){}
kolortransparentny pikselkolorowy::get_kolor()
{
    return k;
}
void pikselkolorowy::set_kolor(kolortransparentny _k)
{
    k=_k;
}
int pikselkolorowy::get_alfa()
{
    return k.get_alfa();
}
void pikselkolorowy::set_alfa(int _alfa)
{
    k.set_alfa(_alfa);
}
void pikselkolorowy::przesun(int _x, int _y)
{
    if(x+_x<0 || x+_x>ekran_x or y+_y<0 or y+_y>ekran_y)
    {
        throw out_of_range("Piksel poza ekranem");
    }
    x=x+_x;
    y=y+_y;
}

int odleglosc(const piksel& p, const piksel &q)
{
    int dx=p.get_x()-q.get_x();
    int dy=p.get_y()-q.get_y();
    return round((sqrt(dx*dx+dy*dy)));
}

ostream& operator<<(ostream& os, const kolor& k) 
{
    os<<"r="<<k.get_r()<<" g="<< k.get_g()<<" b="<<k.get_b();
    return os;
}




