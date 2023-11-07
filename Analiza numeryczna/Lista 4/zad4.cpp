#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

double f(double x)
{   
    return pow(x,4)-log(x+4);
}   

double miejsce_zerowe(double a, double b, double eps)
{
    int n=floor(log2((b-a)/(2*eps)))+1;
    for(int i=0; i<n; i++)
    {
        double mn=(a+b)/2;
        double fun=f(mn);
        if(fun==0 || (b-a)/2<eps)
        {
            return mn;
        }
        if(fun*f(a)<0)
        {
            b=mn;
        }
        else
        {
            a=mn;
        }
    }
    return (a+b)/2;
}

int main()
{
    double a1=-2;
    double b1=0;
    double a2=0;
    double b2=2;
    double eps=pow(10,-8);
    double x1=miejsce_zerowe(a1,b1,eps);
    double x2=miejsce_zerowe(a2,b2,eps);
    cout<<setprecision(10)<<x1<<" "<<x2<<endl;
}