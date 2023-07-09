#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

typedef struct 
{
    char* imie;
    char* nazwisko;
    short wiek,waga;
    double wzrost;
    double BMI;
}osoba;

bool mniejsze(osoba* a, osoba* b)
{
    if(strcmp(a->nazwisko,b->nazwisko)<0)
    {
        return 0;
    }
    if(strcmp(a->nazwisko,b->nazwisko)>0)
    {
        return 1;
    }
    if(strcmp(a->imie,b->imie)<0)
    {
        return 0;
    }
    if(strcmp(a->imie,b->imie)>0)
    {
        return 1;
    }
    if(a->wiek<b->wiek)
    {
        return 0;
    }
    if(a->wiek>b->wiek)
    {
        return 1;
    }
    if(a->BMI<b->BMI)
    {
        return 0;
    }
    if(a->BMI>b->BMI)
    {
        return 1;
    }
    return 0;
}

void insert(osoba tab[], int n, bool (*mniejsza)(osoba*,osoba*))
{
    int j;
    for(int i=1; i<n; i++)
    {
        osoba x=tab[i];
        j=i-1;
        while(j>=0 && mniejsza(&tab[j],&x))
        {
            tab[j+1]=tab[j];
            j--;
        }
        tab[j+1]=x;
    }
}

void wypisz(osoba o)
{
    printf("%s %s %d %d %lf %lf",o.nazwisko,o.imie,o.wiek,o.waga,o.wzrost,o.BMI);
}

int main()
{
    osoba tab[11]={
        {"Kasewq","Sdsad",32,60,1.75},
        {"Kasewq","Fdsweqr",45,65,1.79},
        {"Kasewq","Ddsadqw",42,59,1.76},
        {"Tweasewq","Kwrqwr",43,61,1.77},
        {"Aqwrwq","Ssatsaty",44,62,1.78},
        {"Wqwrwq","Dyuutrewe",40,63,1.76},
        {"Hrgfd","Pewrtwe",39,64,1.82},
        {"Tqwreq","Pewrtwe",38,70,1.80},
        {"Gsadf","Rewwqe",35,72,1.79},
        {"Gsadf","Rerwqrwq",34,71,1.85},
        {"Eertwtew","Etwrtew",42,59,1.76},
    };
    for(int i=0; i<11; i++)
    {
        tab[i].BMI=tab[i].waga/(tab[i].wzrost*tab[i].wzrost);
    }
    insert(tab,11,(bool (*)(osoba *, osoba *))mniejsze);
    for(int i=0; i<11; i++)
    {
        wypisz(tab[i]);
    }
    return 0;
}