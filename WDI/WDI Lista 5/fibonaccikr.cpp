#include<iostream>
using namespace std;

int fib(int k, int r)
{
    int a=0,b=1%r,c=0;
    for(int i=3; i<=k; i++)
    {
        c+=a;
        c%=r;
        a=b;
        b=c;
    }
    return c;
}

int main()
{
    int k,r;
    cin>>k>>r;
    cout<<fib(k,r);
    return 0;
}