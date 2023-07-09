#include<stdio.h>

unsigned jakiBit(unsigned liczba, unsigned nrBitu)
{
    liczba=liczba>>nrBitu;
    return liczba%2;
}

void zmienBit(unsigned *liczba, unsigned nrBitu)
{
    unsigned l=1<<nrBitu;
    *liczba=(*liczba)^l;
}

void wypisz(unsigned n)
{
    if(n==1)
    {
        printf("%d",1);
    }
    else if(n==0)
    {
        printf("%d",0);
    }
    else
    {
        wypisz(n/2);
        printf("%d",n%2);
    }
}

int main()
{
    unsigned n,nr;
    scanf("%u %u",&n,&nr);
    int ile=0;
    for(int i=31; i>=0; i--)
    {
        if(jakiBit(n,i)==1)
        {
            ile++;
        }
        if(i==nr)
        {
            if(jakiBit(n,nr)==0)
            {
                ile++;
            }
            zmienBit(&n,i);
            printf("%u",jakiBit(n,i));
        }
        else
        {
            printf("%u",jakiBit(n,i));
        }
    }
    printf("\n");
    wypisz(n);
    printf("\n%d",ile);
    if(n!=0)
    {
        int i=31;
        while(jakiBit(n,i)==0)
        {
            i--;
        }
        printf("\n");
        printf("%d",i);
        i=0;
        while(jakiBit(n,i)==0)
        {
            i++;
        }
        printf("\n");
        printf("%d",i);
    }
    return 0;
}