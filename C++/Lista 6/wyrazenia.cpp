#include<iostream>
#include<vector>
#include<cmath>
#include"wyrazenia.hpp"
using namespace std;

Wyrazenie::Wyrazenie()=default;
Wyrazenie::~Wyrazenie() {} 

Liczba::Liczba(double _val): val(_val){}
double Liczba::oblicz() const
{
    return val;
}
string Liczba::zapis() const
{
    return to_string(val);
}

Stala::Stala(const string& _nazwa, double _val): nazwa(_nazwa), val(_val) {}
double Stala::oblicz() const 
{
    return val;
}
string Stala::zapis() const 
{
    return nazwa;
}

Pi::Pi(): Stala("pi",M_PI){}
double Pi::oblicz() const 
{
    return this->val;
}
string Pi::zapis() const 
{
    return this->nazwa;
}

Fi::Fi(): Stala("fi",1.618033988749895){}
double Fi::oblicz() const 
{
    return this->val;
}
string Fi::zapis() const 
{
    return this->nazwa;
}

E::E(): Stala("e",M_E){}
double E::oblicz() const 
{
    return this->val;
}
string E::zapis() const 
{
    return this->nazwa;
}

Zmienna::Zmienna(const string& nazwa): name(nazwa) {}
void Zmienna::dodaj(const string& nazwa, double val)
{
    zmienne.push_back(make_pair(nazwa,val));
}
void Zmienna::usun(const string& nazwa)
{
    for(auto i=zmienne.begin(); i!=zmienne.end(); i++)
    {
        if(i->first==nazwa)
        {
            zmienne.erase(i);
            break;
        }
    }
}
void Zmienna::zmien(const string& nazwa, double val)
{
    for(auto& para: zmienne)
    {
        if(para.first==nazwa)
        {
            para.second=val;
            break;
        }
    }
}
double Zmienna::oblicz() const 
{
    for(const auto& para: zmienne)
    {
        if(para.first==name)
        {
            return para.second;
        }
    }
    throw invalid_argument("Nie ma takiej zmiennej w wektorze");
}
string Zmienna::zapis() const 
{
    return name;
}

Operator1Arg::Operator1Arg(Wyrazenie *arg): argument(arg) {}

Przeciw::Przeciw(Wyrazenie *arg): Operator1Arg(arg) {}
double Przeciw::oblicz() const 
{
    return -1*argument->oblicz();
}
string Przeciw::zapis() const 
{
    return "-("+argument->zapis()+")";
}

Odwrot::Odwrot(Wyrazenie *arg): Operator1Arg(arg) {}
double Odwrot::oblicz() const 
{
    return 1/argument->oblicz();
}
string Odwrot::zapis() const 
{
    return "1/("+argument->zapis()+")";
}

Sin::Sin(Wyrazenie *arg): Operator1Arg(arg) {}
double Sin::oblicz() const 
{
    return sin(argument->oblicz()*M_PI/180);
}
string Sin::zapis() const
{
    return "sin("+argument->zapis()+")";
}

Cos::Cos(Wyrazenie *arg): Operator1Arg(arg) {}
double Cos::oblicz() const 
{
    return cos(argument->oblicz()*M_PI/180);
}
string Cos::zapis() const 
{
    return "cos("+argument->zapis()+")";
}

Bezwzgl::Bezwzgl(Wyrazenie *arg): Operator1Arg(arg) {}
double Bezwzgl::oblicz() const 
{
    return abs(argument->oblicz());
}
string Bezwzgl::zapis() const 
{
    return "|"+argument->zapis()+"|";
}

Exp::Exp(Wyrazenie *arg): Operator1Arg(arg) {}
double Exp::oblicz() const 
{
    return exp(argument->oblicz());
}
string Exp::zapis() const 
{
    return "e^"+argument->zapis();
}

Ln::Ln(Wyrazenie *arg): Operator1Arg(arg) {}
double Ln::oblicz() const 
{
    return log(argument->oblicz());
}
string Ln::zapis() const 
{
    return "ln"+argument->zapis();
}

Operator2Arg::Operator2Arg(Wyrazenie *a1, Wyrazenie *a2): Operator1Arg(a1), arg2(a2) {}
        
Dodaj::Dodaj(Wyrazenie *a1, Wyrazenie *a2): Operator2Arg(a1,a2) {}
double Dodaj::oblicz() const 
{
    return argument->oblicz()+arg2->oblicz();
}
string Dodaj::zapis() const 
{
    return "("+argument->zapis()+"+"+arg2->zapis()+")";
}

Odejmij::Odejmij(Wyrazenie *a1, Wyrazenie *a2): Operator2Arg(a1,a2) {}
double Odejmij::oblicz() const 
{
    return argument->oblicz()-arg2->oblicz();
}
string Odejmij::zapis() const 
{
    return "("+argument->zapis()+"-"+arg2->zapis()+")";
}

Mnoz::Mnoz(Wyrazenie *a1, Wyrazenie *a2): Operator2Arg(a1,a2) {}
double Mnoz::oblicz() const 
{
    return argument->oblicz()*arg2->oblicz();
}
string Mnoz::zapis() const 
{
    return "("+argument->zapis()+"*"+arg2->zapis()+")";
}

Dziel::Dziel(Wyrazenie *a1, Wyrazenie *a2): Operator2Arg(a1,a2) {}
double Dziel::oblicz() const 
{
    return argument->oblicz()/arg2->oblicz();
}
string Dziel::zapis() const 
{
    return "("+argument->zapis()+"/"+arg2->zapis()+")";
}

Logarytm::Logarytm(Wyrazenie *a1, Wyrazenie *a2): Operator2Arg(a1,a2) {}
double Logarytm::oblicz() const 
{
    if(argument->oblicz()>0 || argument->oblicz()!=1 || arg2->oblicz()>0)
    {
        return log(arg2->oblicz())/log(argument->oblicz());
    }
    else throw invalid_argument("Blad danych dla logarytmu");
}
string Logarytm::zapis() const 
{
    return "log_"+argument->zapis()+"("+arg2->zapis()+")";
}

Potega::Potega(Wyrazenie *a1, Wyrazenie *a2): Operator2Arg(a1,a2) {}
double Potega::oblicz() const 
{
    return pow(argument->oblicz(),arg2->oblicz());
}
string Potega::zapis() const 
{
    return "("+argument->zapis()+"^"+arg2->zapis()+")";
}

Modulo::Modulo(Wyrazenie *a1, Wyrazenie *a2): Operator2Arg(a1,a2) {}
double Modulo::oblicz() const 
{
    return fmod(argument->oblicz(),arg2->oblicz());
}
string Modulo::zapis() const
{
    return "("+argument->zapis()+"%"+arg2->zapis()+")";
}

vector<pair<string,double>>Zmienna::zmienne;



