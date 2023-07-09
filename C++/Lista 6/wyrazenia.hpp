#include<iostream>
#include<cmath>
#include<vector>
using namespace std;

class Wyrazenie
{
    private:
        Wyrazenie& operator=(const Wyrazenie&)=delete;
        Wyrazenie(const Wyrazenie&)=delete;
    public:
        Wyrazenie();
        virtual double oblicz() const=0;
        virtual string zapis() const=0;
        virtual ~Wyrazenie();
};

class Liczba: public Wyrazenie
{
    private:
        double val;
    public:
        Liczba(double _val);
        double oblicz() const override;
        string zapis() const override;
};

class Stala: public Wyrazenie
{
    protected:
        string nazwa;
        double val;
    public:
        Stala(const string& _nazwa, double _val);
        double oblicz() const override;
        string zapis() const override;
};

class Pi: public Stala
{
    public:
        Pi();
        double oblicz() const override;
        string zapis() const override;
};

class Fi: public Stala
{
    public:
        Fi();
        double oblicz() const override;
        string zapis() const override;
};

class E: public Stala
{
    public:
        E();
        double oblicz() const override;
        string zapis() const override;
};

class Zmienna: public Wyrazenie
{
    private:
        string name;
        static vector<pair<string,double>> zmienne;
    public:
        Zmienna(const string& nazwa);
        static void dodaj(const string& nazwa, double val);
        static void usun(const string& nazwa);
        static void zmien(const string& nazwa, double val);
        double oblicz() const override;
        string zapis() const override;
};

class Operator1Arg: public Wyrazenie
{
    protected:
        Wyrazenie *argument;
    public:
        Operator1Arg(Wyrazenie *arg);
        double oblicz() const override=0;
        string zapis() const override=0;
};

class Przeciw: public Operator1Arg
{
    public:
        Przeciw(Wyrazenie *arg);
        double oblicz() const override;
        string zapis() const override;
};

class Odwrot: public Operator1Arg
{
    public:
        Odwrot(Wyrazenie *arg);
        double oblicz() const override;
        string zapis() const override;
};

class Sin: public Operator1Arg
{
    public:
        Sin(Wyrazenie *arg);
        double oblicz() const override;
        string zapis() const override;
};

class Cos: public Operator1Arg
{
    public:
        Cos(Wyrazenie *arg);
        double oblicz() const override;
        string zapis() const override;
};

class Bezwzgl: public Operator1Arg
{
    public:
        Bezwzgl(Wyrazenie *arg);
        double oblicz() const override;
        string zapis() const override;
};

class Exp: public Operator1Arg
{
    public:
        Exp(Wyrazenie *arg);
        double oblicz() const override;
        string zapis() const override;
};

class Ln: public Operator1Arg
{
    public:
        Ln(Wyrazenie *arg);
        double oblicz() const override;
        string zapis() const override;
};

class Operator2Arg: public Operator1Arg
{
    protected:
        Wyrazenie *arg2;
    public:
        Operator2Arg(Wyrazenie *a1, Wyrazenie *a2);
        double oblicz() const override=0;
        string zapis() const override=0;
};

class Dodaj: public Operator2Arg
{
    public:
        Dodaj(Wyrazenie *a1, Wyrazenie *a2);
        double oblicz() const override;
        string zapis() const override;
};

class Odejmij: public Operator2Arg
{
    public:
        Odejmij(Wyrazenie *a1, Wyrazenie *a2);
        double oblicz() const override;
        string zapis() const override;
};

class Mnoz: public Operator2Arg
{
    public:
        Mnoz(Wyrazenie *a1, Wyrazenie *a2);
        double oblicz() const override;
        string zapis() const override;
};

class Dziel: public Operator2Arg
{
    public:
        Dziel(Wyrazenie *a1, Wyrazenie *a2);
        double oblicz() const override;
        string zapis() const override;
};

class Logarytm: public Operator2Arg
{
    public:
        Logarytm(Wyrazenie *a1, Wyrazenie *a2);
        double oblicz() const override;
        string zapis() const override;
};

class Potega: public Operator2Arg
{
    public:
        Potega(Wyrazenie *a1, Wyrazenie *a2);
        double oblicz() const override;
        string zapis() const override;
};

class Modulo: public Operator2Arg
{
    public:
        Modulo(Wyrazenie *a1, Wyrazenie *a2);
        double oblicz() const override;
        string zapis() const override;
};