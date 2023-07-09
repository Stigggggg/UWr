#include<stdio.h>
#include<stdlib.h>

long long tab[46];

void fib(long long tab[46])
{
    long long f1=1,f2=2,f3;
    tab[0]=1;
    tab[1]=2;
    for(int i=2; i<=45; i++)
    {
        f3=f1+f2;
        tab[i]=f3;
        f1=f2;
        f2=f3;
    }
}

int main()
{
    fib(tab);
    unsigned int n;
    int s=0;
    scanf("%u", &n);
    int l=0;
    while(tab[l]<=n)
    {
        l++;
    }
    l--;
    for(int i=l; i>=0; i--)
    {
        if(tab[i]+s<=n)
        {
            printf("%d",1);
            s+=tab[i];
        }
        else
        {
            printf("%d",0);
        }
    }
    return 0;
}
