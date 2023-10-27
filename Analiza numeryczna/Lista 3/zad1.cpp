#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

double zad1a(double x)
{
    return 1.0/(pow(x,3.0)+sqrt(pow(x,6.0)+2023.0*2023.0));
}

double zad1a_popr(double x)
{
    return (pow(x,3.0)-sqrt(pow(x,6.0)+2023.0*2023.0))/(-1.0*2023.0*2023.0);
}

double zad1b(double x)
{
    return log2(x)-2.0;
}

double zad1b_popr(double x)
{
    return log2(x/4.0);
}

double zad1c(double x)
{
    return M_PI/2.0-x-atan(1.0/x);
}

double zad1c_popr(double x)
{
    return -1.0/3.0+x*x/5.0;
}

int main()
{
    cout<<setprecision(10)<<zad1a(-1000000000)<<" "<<zad1a_popr(-1000000000)<<endl;
    cout<<setprecision(10)<<zad1b(4-pow(10.0,-15))<<" "<<zad1b_popr(4-pow(10.0,-15))<<endl;
    cout<<setprecision(10)<<zad1c(pow(10.0,-10))<<" "<<zad1c_popr(pow(10.0,-10));
    return 0;
}