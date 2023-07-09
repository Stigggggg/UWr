#include<stdio.h>
#include<stdlib.h>

int mini(int a, int b)
{
    if(a>=b)
        return b;
    else return a;
}

int main()
{
    int n;
    scanf("%d",&n);
    int tab[n][n];
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            scanf("%d",&tab[i][j]);
        }
    }
    for(int i=1; i<n; i++)
    {
        tab[i][0]+=tab[i-1][0];
    }
    for(int j=1; j<n; j++)
    {
        tab[0][j]+=tab[0][j-1];
    }
    for(int i=1; i<n; i++)
    {
        for(int j=1; j<n; j++)
        {
            tab[i][j]+=mini(tab[i-1][j],tab[i][j-1]);
        }
    }
    printf("%d",tab[n-1][n-1]);
    return 0;
}