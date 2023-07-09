#include<iostream>
using namespace std;

int a(int n)
{
    if(n%2==0)
    {
        return n;
    }
    else
    {
        return (-1)*n;
    }
}

int b(int n)
{
    int suma=0;
    for(int i=1; i<=n; i++)
    {
        if(i%2==0)
        {
            suma+=(-1)/i;
        }
        else
        {
            suma+=1/i;
        }
    }
    return suma;
}

int potega(int x, int p)
{
    int wynik=1;
    for(int i=1; i<=p; i++)
    {
        wynik*=x;
    }
    return wynik;
}

int c(int n,int x)
{
    int suma=0;
    for(int i=1; i<=n; i++)
    {
        suma+=i*potega(x,i);
    }
    return suma;
}

int main()
{
    int n,x;
    cin>>n>>x;
    cout<<a(n)<<" "<<b(n)<<" "<<c(n,x);
    return 0;
}