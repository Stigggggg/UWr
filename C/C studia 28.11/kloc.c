#include<stdio.h>
#include<stdlib.h>

void sortuj(int a, int b, int c)
{
    int min=0;
    int max=0;
    int sred=0;
    if(a<b && a<c)
    {
        min=a;
        if(b<c)
        {
            sred=b;
            max=c;
        }
        else
        {
            sred=c;
            max=b;
        }
    }
    else if(b<c && b<a)
    {
        min=b;
        if(a<c)
        {
            sred=a;
            max=c;
        }
        else
        {
            sred=c;
            max=a;
        }
    }
    else if(c<a && c<b)
    {
        min=c;
        if(a<b)
        {
            sred=a;
            max=b;
        }
        else
        {
            sred=a;
            max=b;
        }
    }
    printf("%d %d %d\n",max,sred,min);
}

int abs(int n)
{
    if(n<0)
    {
        return n*(-1);
    }
    else return n;
}

int najw_odl(int a, int b, int c)
{
    int odl=-1;
    if(abs(a-b)>odl)
    {
        odl=abs(a-b);
    }
    if(abs(b-c)>odl)
    {
        odl=abs(b-c);
    }
    if(abs(a-c)>odl)
    {
        odl=abs(a-c);
    }
    return odl;
}

int main()
{
    
    int d,a,b,c,ile=0,odl=100000;
    int sc=scanf("%d",&d);
    sc--;
    for(int i=1; i<=1000; i++)
    {
        for(int j=1; j<=1000; j++)
        {
            for(int k=1; k<=1000; k++)
            {
                if(i*i+j*j+k*k==d*d)
                {
                    if(najw_odl(i,j,k)<odl)
                    {
                        odl=najw_odl(i,j,k);
                        a=i,b=j,c=k;
                        ile++;
                    }
                }
            }
        }
    }
    if(ile==0)
    {
        printf("BRAK");
    }
    else
    {
        sortuj(a,b,c);
    }
    return 0;
}