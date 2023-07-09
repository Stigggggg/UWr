#include<stdio.h>
#include<stdlib.h>

int euklides(int a, int b)
{
    int temp;
    while(b!=0)
    {
        temp=b;
        b=a%b;
        a=temp;
    }
    return a;
}

int main()
{
    int a,b;
    scanf("%d %d",&a,&b);
    printf("%d",euklides(a,b));
    return 0;
}