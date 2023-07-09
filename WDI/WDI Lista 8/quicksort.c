#include<stdio.h>
#include<stdlib.h>

int podzial(int l, int p, int tab[])
{
    int i=l,j=p,x=tab[l],y;
    while(i<j)
    {
        while(tab[j]>x)
        {
            j--;
        }
        while(tab[i]<x)
        {
            i++;
        }
        if(i<j)
        {
            y=tab[j];
            tab[j]=tab[i];
            tab[i]=y;
            i++;
            j--;
        }
    }
    return j;
}

void quicksort(int tab[], int l, int r)
{
    int s;
    if(l<r)
    {
        s=podzial(l,r,tab);
        quicksort(tab,l,s);
        for(int i=l; i<=s; i++)
        {
            printf("%d ",tab[i]);
        }
        printf("\n");
        quicksort(tab,s+1,r);
        for(int i=s+1; i<=r; i++)
        {
            printf("%d ",tab[i]);
        }
        printf("\n");
    }
}

int main()
{
    int n=4;
    int tab[4]={4,3,2,1};
    quicksort(tab,0,n-1);
    for(int i=0; i<n; i++)
    {
        printf("%d ",tab[i]);
    }
    return 0;
}