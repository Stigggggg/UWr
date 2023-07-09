#include<iostream>
#include<stdexcept>
#include"historia.hpp"
using namespace std;

Liczba::Liczba(double x=0) : val(x), hist(new double[max_size]), size(1), ind(0) //konstruktor domyslny
{
    hist[ind]=x;
}
Liczba::Liczba() : Liczba(0) {} //konstruktor delegatowy
Liczba::Liczba(const Liczba& l) : val(l.val), hist(new double[max_size]), size(l.size), ind(l.ind) //konstruktor kopiujacy
{
    hist=new double[max_size];
    hist[ind]=val;
} 
Liczba::Liczba(Liczba&& l) : val(l.val), hist(l.hist), size(l.size), ind(l.ind) //konstruktor przenoszacy
{
    l.hist=nullptr;
}
const Liczba& Liczba::operator=(const Liczba& l) //przypisanie kopiujace
{
    if(this!=&l)
    {
        val=l.val;
        int kopia_size=min(size,l.size);
        for(int i=0; i<kopia_size; i++)
        {
            hist[i]=l.hist[i];
        }
        for(int i=kopia_size; i<size; i++)
        {
            hist[i]=0;
        }
        ind=l.ind;
    }
    return *this;
}
const Liczba& Liczba::operator=(Liczba&& l) //przypisanie przenoszace
{
    if(this!=&l)
    {
        val=l.val;
        size=l.size;
        ind=l.ind;
        delete[] hist;
        hist=l.hist;
        l.hist=nullptr;
        l.val=0;
        l.size=0;
        l.ind=0;
    }
    return *this;
}
Liczba::~Liczba() //destruktor
{
    delete[] hist;
}
double Liczba::get_val()
{
    return val;
}
void Liczba::set_val(double x)
{
    this->val=x;
    if(ind+1<max_size)
    {
        ind++;
        size++;
        hist[ind]=val;
    }
    else
    {
        for(int i=1; i<max_size; i++)
        {
            hist[i-1]=hist[i];
        }
        hist[max_size-1]=val;
    }
    val=x;
}
double Liczba::undo_val()
{
    if(ind>=1)
    {
        ind--;
        return hist[ind];
    }
    else
    {
        throw out_of_range("Nie ma wiecej elementow do przywrocenia");
    }
}
