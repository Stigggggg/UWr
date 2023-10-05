#include<iostream>
#include<cmath>
using namespace std;

float f_single(float x)
{
    float f=14*(1-cos(17*x))/x*x;
    return f;
}

double f_double(double x)
{
    double f=14*(1-cos(17*x))/x*x;
    return f;
}


int main()
{
    for(int i=11; i<=20; i++)
    {
        cout<<i<<" "<<f_single(pow(10,-i))<<" "<<f_double(pow(10,-i))<<endl;
    }
    return 0;
}