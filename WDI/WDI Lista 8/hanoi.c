#include<stdio.h>
#include<stdlib.h>

void hanoi(int n, char z, char na, char pom)
{
    if(n==1)
    {
        printf("\nDysk 1 z %c na %c",z,na);
        return;
    }
    hanoi(n-1,z,pom,na);
    printf("\nDysk %d z %c na %c",n,z,na);
    hanoi(n-1,pom,na,z);
}

int main()
{
    int n=4;
    hanoi(n,'A','C','B');
    return 0;
}