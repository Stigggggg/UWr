#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct
{
    short int g,m,s;
}zegar;

static const zegar pocz={0,0,0};

bool sprawdz(zegar z)
{
    if(z.g<0 || z.g>=24)
    {
        return 0;
    }
    if(z.m<0 || z.m>=60)
    {
        return 0;
    }
    if(z.s<0 || z.s>=60)
    {
        return 0;
    }
    return 1;
}

zegar normuj(zegar z)
{
    z.m+=z.s/60;
    z.s%=60;
    if(z.s<0)
    {
        z.s+=60;
        z.m--;
    }
    z.g+=z.m/60;
    z.m%=60;
    if(z.m<0)
    {
        z.m+=60;
        z.g--;
    }
    z.g%=24;
    if(z.g<0)
    {
        z.g+=24;
    }
    return z;
}

zegar ustaw(short g, short m, short s)
{
    zegar z;
    z.g=g;
    z.m=m;
    z.s=s;
    if(sprawdz(z)==0)
    {
        z=normuj(z);
        return z;
    }
    else return z;
}

void dodajgodziny(zegar *z, short g)
{
    z->g+=g;
    *z=normuj(*z);
}

void dodajminuty(zegar *z, short m)
{
    z->m+=m;
    *z=normuj(*z);
}

void dodajsekundy(zegar *z, short s)
{
    z->s+=s;
    *z=normuj(*z);
}

void drukuj(FILE *f, zegar z)
{
    fprintf(f,"%02d:%02d:%02d",z.g,z.m,z.s);
}

int main()
{
    zegar z=ustaw(7,30,50);
    dodajsekundy(&z,-60);
    drukuj(stdout,z);
    return 0;
}
