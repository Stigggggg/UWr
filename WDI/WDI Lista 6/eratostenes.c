#include<stdio.h>
#include<stdlib.h>

void sito(int n, int s[])
{
    for(int i=2; i*i<=n; i++) //zaczynamy od 2, idziemy do pierwiastka
    {
        if(s[i]==1)
        {
            for(int j=i*i; j<=n; j+=i) //zaczynamy od kwadratu, bo poprzednie wielokrotności są wykreślone
            {
                s[j]=0;
            }
        }
    }
    for(int i=2; i<=n; i++)
    {
        if(s[i]==1)
        {
            printf("%d ",i);
        }
    }
}

int main()
{
    int n;
    scanf("%d",&n);
    int s[n];
    for(int i=0; i<n; i++)
    {
        s[i]=1;
    }
    sito(n,s);
    return 0;
}