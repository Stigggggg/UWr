#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

double f(double x, int a)
{
    return 1/pow(x,2)-a;
}

double poch(double x)
{
    return -2.0*1.0/pow(x,3);
}

double F(int n, double x0, int a)
{
    if(n==0)
    {
        return x0;
    }
    else
    {
        double xn=F(n-1,x0,a);
        return (3.0/2.0)*xn-(a/2.0)*pow(xn,3);
    }
}

int main()
{
    //x0 z przedzialu (sqrt(1/3a),sqrt(5/3a))
    cout<<"a=3, x0=1/2"<<endl;  
    for(int i=0; i<=10; i++)
    {
        cout<<"x"<<i<<"="<<F(i,(1.0/2.0),3.0)<<endl;
    }
    cout<<"Wartosc poprawna: "<<1/sqrt(3)<<endl;
    cout<<"a=12, x0=1/3"<< endl;  
    for(int i=0; i<=10; i++)
    {
        cout<<"x"<<i<<"="<<F(i,(1.0/3.0),12.0)<<endl;
    }
    cout<<"Wartosc poprawna: "<<1/sqrt(12)<<endl;
    cout<<"a=27, x0=1/5"<<endl;  
    for(int i = 0; i<=10; i++)
    {
        cout<<"x"<<i<<"="<<F(i,(1.0/5.0),27.0)<<endl;
    }
    cout<<"Wartosc poprawna: "<<1/sqrt(27)<<endl;
    return 0;
}