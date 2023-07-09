#include<stdio.h>
#include<stdlib.h>

int czy_jest_bezkwadratowa(int x)
{
    for(int i=2; i*i<=x; i++)
    {
        if(x%(i*i)==0)
        {
            return 0;
        }
    }
    return 1;
}

int szukanie(int x)
{
    for(int i=x; i<=x+1000; i++)
    {
        if(czy_jest_bezkwadratowa(i)==1)
        {
            return i;
        }
    }
    return 0;
}

int main(void)
{
    int n, czy_jest=0;
    scanf("%d", &n);
    czy_jest=szukanie(n);
    if(czy_jest==0)
    {
        printf("BRAK");
    }
    else
    {
        printf("%d", czy_jest);
    }
}
