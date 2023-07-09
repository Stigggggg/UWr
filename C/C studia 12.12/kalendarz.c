#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

typedef struct{
    short int r,m,d;
}kalendarz;

bool mniejszy(kalendarz *k1, kalendarz *k2)
{
    if(k1->r<k2->r)
    {
        return 1;
    }
    if(k1->r>k2->r)
    {
        return 0;
    }
    if(k1->m<k2->m)
    {
        return 1;
    }
    if(k1->m>k2->m)
    {
        return 0;
    }
    if(k1->d<k2->d)
    {
        return 1;
    }
    if(k1->d>k2->d)
    {
        return 0;
    }
    return 0;
}

void podmiana(kalendarz** k1, kalendarz** k2)
{
    kalendarz* tmp=*k1;
    *k1=*k2;
    *k2=tmp;
}

void bubble(kalendarz* tab[], int n)
{
    for(int i=0; i<n-1; i++)
    {
        for(int j=0; j<n-i-1; j++)
        {
            if(mniejszy(tab[j+1],tab[j]))
            {
                podmiana(&tab[j+1],&tab[j]);
            }
        }
    }
}

void wypisz(kalendarz* k)
{
    printf("%d %d %d\n",k->r,k->m,k->d);
}

int main()
{
    int n;
    scanf("%d",&n);
    kalendarz* tab[n];
    for(int i=0; i<n; i++)
    {
        kalendarz* d=(kalendarz*)malloc(sizeof(kalendarz));
        scanf("%hd %hd %hd",&d->r,&d->m,&d->d);
        tab[i]=d;
    }
    bubble(tab,n);
    for(int i=0; i<n; i++)
    {
        wypisz(tab[i]);
    }
    return 0;
}
