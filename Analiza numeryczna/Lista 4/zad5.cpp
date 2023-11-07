#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

double f(double x, int R)
{
    return 1.0/x-R;
}

double poch(double x)
{
    return -1/pow(x,2);
}

double F(int n, double x0, int R)
{
    if(n==0)
    {
        return x0;
    }
    else
    {
        double xn=F(n-1,x0,R);
        return xn-f(xn,R)/poch(xn);
    }
}

int main()
{
    cout<<"R=5, x=1/10"<<endl;
    for(int i=0; i<=10; i++)
    {
        cout<<"x"<<i<<"="<<F(i,1.0/10.0,5)<<endl;
    }
    cout<<"R=5, x=1/4"<<endl;
    for(int i=0; i<=10; i++)
    {
        cout<<"x"<<i<<"="<<F(i,1.0/4.0,5)<<endl;
    }
    cout<<"R=10, x=3/50"<<endl;
    for(int i=0; i<=10; i++)
    {
        cout<<"x"<<i<<"="<<F(i,3.0/50.0,10)<<endl;
    }
    cout<<"R=4, x=1/3"<<endl;
    for(int i=0; i<=10; i++)
    {
        cout<<"x"<<i<<"="<<F(i,1.0/3.0,4)<<endl;
    }
    cout<<"R=2, x=1"<<endl;
    for(int i=0; i<=10; i++)
    {
        cout<<"x"<<i<<"="<<F(i,1.0,2)<<endl;
    }
    cout<<"R=5, x=-1/20"<<endl;
    for(int i=0; i<=15; i++)
    {
        cout<<"x"<<i<<"="<<F(i,-1.0/20.0,5)<<endl;
    }
}
