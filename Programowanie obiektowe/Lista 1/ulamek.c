//Mikolaj Drozd 339139
//Zadanie 2 z listy 1
//gcc ulamek.c

#include<stdio.h>
#include<stdlib.h>

typedef struct{
    int licz;
    int mian;
}ulamek;

int nwd(int a, int b)
{
    if(a<0)
    {
        a=-a;
    }
    if(b<0)
    {
        b=-b;
    }
    while(b!=0)
    {
        int pom=b;
        b=a%b;
        a=pom;
    }
    return a;
}

int nww(int a, int b)
{
    return (a*b)/nwd(a,b);
}

ulamek *nowy_ulamek(int num, int denom)
{
    ulamek *nowy=(ulamek *)malloc(sizeof(ulamek));
    int wsp_mian=nwd(num,denom);
    nowy->licz=num/wsp_mian;
    nowy->mian=denom/wsp_mian;
    return nowy;
}

void show(ulamek *u)
{
    printf("%d/%d\n",u->licz,u->mian);
}

ulamek *mnozenie_1(ulamek *a, ulamek *b)
{
    ulamek *c=nowy_ulamek((a->licz)*(b->licz),(a->mian)*(b->mian));
    return c;
}

void mnozenie_2(ulamek *a, ulamek *b)
{
    a->licz*=b->licz;
    a->mian*=b->mian;
    int wsp_mian=nwd(a->licz,a->mian);
    a->licz/=wsp_mian;
    a->mian/=wsp_mian;
}

ulamek *dzielenie_1(ulamek *a, ulamek *b)
{
    ulamek *c=nowy_ulamek((a->licz)*(b->mian),(a->mian)*(b->licz));
    return c;
}

void dzielenie_2(ulamek *a, ulamek *b)
{
    a->licz*=b->mian;
    a->mian*=b->licz;
    int wsp_mian=nwd(a->licz,a->mian);
    a->licz/=wsp_mian;
    a->mian/=wsp_mian;
}

ulamek *dodawanie_1(ulamek *a, ulamek *b)
{
    ulamek *c=nowy_ulamek((a->licz)*(b->mian)+(b->licz)*(a->mian),(a->mian)*(b->mian));
    return c;
}

void dodawanie_2(ulamek *a, ulamek *b)
{
    int wsp_wiel=nww(a->licz,b->mian);
    a->licz*=wsp_wiel/a->mian;
    a->mian=wsp_wiel;
    a->licz+=b->licz*wsp_wiel/b->mian;
}

ulamek *odejmowanie_1(ulamek *a, ulamek *b)
{
    ulamek *c=nowy_ulamek((a->licz)*(b->mian)-(b->licz)*(a->mian),(a->mian)*(b->mian));
    return c;
}

void odejmowanie_2(ulamek *a, ulamek *b)
{
    int wsp_wiel=nww(a->licz,b->mian);
    a->licz*=wsp_wiel/a->mian;
    a->mian=wsp_wiel;
    a->licz-=b->licz*wsp_wiel/b->mian;
}

//w mainie są pozostawione testy, żeby sprawdzić działanie programu, wystarczy odkomentować

int main()
{
    ulamek *a=nowy_ulamek(1,0);
    ulamek *b=nowy_ulamek(10,6);
    if(a->mian==0 || b->mian==0)
    {
        printf("Dzielenie przez 0!!!");
        return 0;
    }
    ulamek *c=mnozenie_1(a,b);
    /*ulamek *d=dzielenie_1(a,b);
    ulamek *e=dodawanie_1(a,b);
    ulamek *f=odejmowanie_1(a,b);
    show(c);
    show(d);
    show(e);
    show(f);
    odejmowanie_2(a,b);
    show(a);
    dzielenie_2(a,b);*/
    return 0;
}