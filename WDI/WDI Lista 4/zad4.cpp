#include<iostream>
using namespace std;

int potega(int x, int p)
{
    int wynik=1;
    for(int i=1; i<=p; i++)
    {
        wynik*=x;
    }
    return wynik;
}

int main()
{
    int n,k;
    cin>>n>>k;
    int a[k];
    for(int i=0; i<k; i++)
    {
        cin>>a[i];
    }
    int p,pmaks=0,tmp;
    for(int i=0; i<k; i++)
    {
        p=0;
        tmp=n;
        while(tmp%a[i]==0)
        {
            tmp/=a[i];
            p++;
        }
        if(p>pmaks)
        {
            pmaks=p;
        }     
    }
    cout<<pmaks<<" ";
    for(int i=0; i<k; i++)
    {
        if((n%potega(a[i],pmaks))==0)
        {
            cout<<a[i]<<" ";
        }
    }
    return 0;
}

