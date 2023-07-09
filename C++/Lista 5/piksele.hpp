#include<iostream>
#include<stdexcept>
using namespace std;

class kolor
{
    protected:
        int r,g,b;
    public:
        kolor();
        kolor(int _r, int _g, int _b);
        int get_r() const;
        int get_g() const;
        int get_b() const;
        void set_r(int _r);
        void set_g(int _g);
        void set_b(int _b);
        void jasniej(int x);
        void ciemniej(int x);
        static kolor srednia(const kolor& k1, const kolor& k2);
};

class kolortransparentny: public virtual kolor
{
    protected:
        int alfa;
    public:
        kolortransparentny();
        kolortransparentny(int _r, int _g, int _b, int _alfa);
        int get_alfa();
        void set_alfa(int _alfa);
};

class kolornazwany: public virtual kolor
{
    protected:
        string nazwa;
    public:
        kolornazwany();
        kolornazwany(int _r, int _g, int _b, const string& _nazwa);
        const string& get_nazwa() const;
        void set_nazwa(const string& _nazwa);
};

class kolornt: public kolortransparentny, public kolornazwany
{
    public:
        kolornt();
        kolornt(int _r, int _g, int _b, int _alfa, const string& _nazwa);
};

class piksel
{
    protected: 
        int x,y;
    public:
        static const int ekran_x=800;
        static const int ekran_y=600;
        piksel(int _x, int _y);
        int get_x() const;
        int get_y() const;
        void set_x(int _x);
        void set_y(int _y);
        int odleglosc_l() const;
        int odleglosc_r() const;
        int odleglosc_g() const;
        int odleglosc_d() const;
        void przesun(int dx, int dy);
};

class pikselkolorowy: public piksel
{
    protected:
        kolortransparentny k;
    public:
        pikselkolorowy(int _x, int _y, int _r, int _g, int _b, int alfa);
        kolortransparentny get_kolor();
        void set_kolor(kolortransparentny _k);
        int get_alfa();
        void set_alfa(int _alfa);
        void przesun(int _x, int _y);
};

int odleglosc(const piksel& p, const piksel &q);

ostream& operator<<(ostream& os, const kolor& k);