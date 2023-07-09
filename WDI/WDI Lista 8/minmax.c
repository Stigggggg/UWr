#include<stdio.h>
#include<stdlib.h>

int mini;

void minimum(int tab[], int l, int p)
{
    if(p-l==0)
    {
        mini=tab[l];
    }
    else 
    {
        if(p-l==1)
        {
            if(tab[l]<tab[p])
            {
               mini=tab[l];
            }
            else
            {
                mini=tab[p];
            }
        }
        else
        {
            int min1,min2;
            minimum(tab,l,(l+p)/2);
            min1=mini;
            minimum(tab,((l+p)/2)+1,p);
            min2=mini;
            if(min1<min2)
            {
                mini=min1;
            }
            else
            {
                mini=min2;
            }
        }
    }
}

int main()
{
    int n;
    scanf("%d",&n);
    int tab[n];
    for(int i=0; i<n; i++)
    {
        scanf("%d",&tab[i]);
    }
    minimum(tab,0,n-1);
    printf("%d",mini);
    return 0;
}