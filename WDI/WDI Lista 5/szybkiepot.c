#include<stdio.h>
#include<stdlib.h>

int szybkie_potegowanie(int a, int x)
{
    if(x==0)
    {
        return 1;
    }
    if(x%2==1)
    {
        return a*(szybkie_potegowanie(a,(x-1)/2)*szybkie_potegowanie(a,(x-1)/2));
    }
    else
    {
        return szybkie_potegowanie(a,x/2)*szybkie_potegowanie(a,x/2);
    }
}

int main()
{
    int n,x;
    scanf("%d %d",&n,&x);
    printf("%d",szybkie_potegowanie(n,x));
    return 0;
}