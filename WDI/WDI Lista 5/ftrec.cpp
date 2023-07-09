#include<iostream>
using namespace std;

int fTrec(int n, int m)
{
    if(m==0)
    {
        return n;
    }
    else if(n==0)
    {
        return m;
    }
    else
    {
        return fTrec(n-1,m)+2*fTrec(n,m-1);
    }
}

int fTiter(int n, int m)
{
    int akt[n+1],poprz[n+1];
    if(m==0)
    {
        return n;
    }
    if(n==0)
    {
        return m;
    }
    for(int i=0; i<=n; i++)
    {
        poprz[i]=i;
    }
    for(int i=1; i<=m; i++)
    {
        akt[0]=i;
        for(int j=1; j<=n; j++)
        {
            akt[j]=poprz[j]+2*poprz[j-1];
        }
        for(int j=0; j<=n; j++)
        {
            poprz[j]=akt[j];
        }
    }
    return akt[n];
}

int main()
{
    cout<<fTiter(3,4);
    return 0;
}