#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

int main()
{
    double x1=2.0;
    double x1_p=2.0;
    for(int i=1; i<=40; i++)
    {
        double x=pow(2,i)*sqrt(2*(1-sqrt(1-pow(x1/pow(2,i),2))));
        double x_p=sqrt(2*pow(x1_p,2)/(1+sqrt(1-pow(x1_p/pow(2,i),2))));
        x1=x;
        x1_p=x_p;
        cout<<setprecision(10)<<i+1<<": "<<x1<<" "<<x1_p<<endl;
    }
    cout<<setprecision(10)<<M_PI<<endl;
    return 0;
}