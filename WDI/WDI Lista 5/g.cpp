#include<iostream>
using namespace std;

int gn(int n)
{
    if(n==0 || n==1 || n==2)
    {
        return 1;
    }
    else
    {
        int akt=1,poprz=1,jpoprz=1,bpoprz;
        for(int i=3; i<=n; i++)
        {
            bpoprz=jpoprz;
            jpoprz=poprz;
            poprz=akt;
            akt=poprz+jpoprz+bpoprz;
        }
        return akt;
    }
}

int main()
{
    cout<<gn(5);
    return 0;
}