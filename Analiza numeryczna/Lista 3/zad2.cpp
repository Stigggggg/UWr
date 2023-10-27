#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

double zad2v1(double a, double b, double c)
{
    return(-b+sqrt(b*b-4.0*a*c))/(2.0*a);
}
double zad2v2(double a, double b, double c)
{
    if(b>0)
        return 2.0*c/(-b-sqrt(b*b-4.0*a*c));
    return 2.0*c/(-b+sqrt(b*b-4.0*a*c));
}

int main() 
{
    cout<<setprecision(16)<<zad2v1(0.25,1000000.0,0.25)<<" "<<zad2v2(0.25,10000.0,0.25);
}