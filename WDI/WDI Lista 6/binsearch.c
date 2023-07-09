#include<stdio.h>
#include<stdlib.h>

int binsearch(int tab[],int l, int p, int x)
{
    int k;
    while(l<p)
    {
        k=(l+p)/2;
        if(tab[k]<x)
        {
            l=k+1;
        }
        else
        {
            p=k;
        }
    }
    return l;
}

int main()
{
    int x=3;
    int tab[6]={1,2,4,6,7,x};
    printf("%d",binsearch(tab,0,4,x));
    return 0;
}