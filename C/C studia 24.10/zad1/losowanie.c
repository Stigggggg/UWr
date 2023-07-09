#include<stdio.h>
#include<stdlib.h>

int main()
{
    srand(time(NULL));
    int n;
    scanf("%d", &n);
    double min=2, max=-1;
    for(int i=0; i<n; i++)
    {
        double c=rand() / (double)RAND_MAX;
        printf("%.3lf\n",c);
        if(c<min)
        {
            min=c;
        }
        if(c>max)
        {
            max=c;
        }
    }
    printf("Minimum: %.3lf Maksimum: %.3lf\n",min,max);
    return 0;
}
