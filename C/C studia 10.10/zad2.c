#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main()
{
    int n;
    double fi=(sqrt(5)+1)/2;
    printf("Podaj liczbe: ");
    scanf("%d",&n);
    printf("%-3s   %29s","n","fi^n\n");
    double w=1;
    for(int i=0; i<=n; i++)
    {
        printf("%-3d   %28.6lf\n",i,w);
        w*=fi;
    }
    return 0;
}
