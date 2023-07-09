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

int main()
{
    int n;
    cin>>n;
    int a[n];
    for(int i=0; i<n; i++)
    {
        cin>>a[i];
    }
    int dzielnik=nwd(a[0],a[1]);
    for(int i=2; i<n; i++)
    {
        dzielnik=nwd(dzielnik,a[i]);
    }
    cout<<dzielnik;
    return 0;
}