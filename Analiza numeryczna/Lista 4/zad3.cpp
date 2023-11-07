#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

double f(double x)
{
    return x-0.49;
}

int main()
{
    double a0=0;
    double b0=1;
    double an=a0;
    double bn=b0;
    for(int i=0; i<=5; i++)
    {
        double mn=(an+bn)/2;
        double fun=f(mn);
        double en=abs(0.49-mn);
        double osz=pow(2,-i-1)*(b0-a0);
        cout<<setprecision(10)<<"i: "<<i<<" an = "<<an<<" bn = "<<bn<<" mn = "<<mn<<" f(mn) = "<<fun<<" |en| = "<<en<<" osz: "<<osz<<endl; 
        if(fun>0)
        {
            bn=mn;
        }
        else
        {
            an=mn;
        }
    }
}