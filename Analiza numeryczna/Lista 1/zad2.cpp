#include<iostream>
#include<cmath>
using namespace std;

int main()
{
    double x=0.001;
    double wynik=4046*((sqrt(pow(x,14))+1)-1)/pow(x,14);
    cout<<wynik;
    return 0;
}