#include<iostream>
using namespace std;

int nwd(int a,int b)
{
    int pom;
    while(b!=0)
    {
        pom=b;
        b=a%b;
        a=pom;
    }
    return a;
}

int nww(int a,int b)
{
    return (a*b)/nwd(a,b);
}

int main()
{
    int a,b;
    cin>>a>>b;
    cout<<nww(a,b)<<" ";
    int dzielnik=nwd(a,b);
    a/=dzielnik;
    b/=dzielnik;
    cout<<a<<"/"<<b;
    return 0;
}