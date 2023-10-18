#include<iostream>
#include<cmath>
using namespace std;

double f_double(double x)
{
    double f=14.0*289.0*(0.5-289.0*pow(x,2.0)/24.0);
    return f;
}

int main()
{
    for(int i=11; i<=20; i++)
    {
        cout<<i<<" "<<f_double(pow(10,-i))<<endl;
    }
    return 0;
}