#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

int main()
{
    int k=0;
    double epsilon=pow(10,-6);
    double pi=0;
    while(true)
    {
        double licz;
        if(k%2==0)
        {
            licz=1.0;
        }
        else licz=-1.0;
        double mian=2.0*k+1.0;
        double wyraz=licz/mian;
        pi+=wyraz;
        if(abs(M_PI-4*pi)<epsilon)
        {
            break;
        }
        k++;
    }
    cout<<k<<" "<<setprecision(10)<<4*pi<<endl;
    return 0;
}