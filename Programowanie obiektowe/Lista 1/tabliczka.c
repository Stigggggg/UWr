//Mikolaj Drozd 339139
//Zadanie 4 z listy 1
//gcc tabliczka.c

#include<stdio.h>
#include<stdlib.h>

void tabliczka(float x1, float x2, float y1, float y2, float skok)
{
    printf("\t  ");
    for(float i=y1; i<y2; i+=skok)
    {
        printf("%6.2f   ",i);
    }
    printf("\n");
    for(float i=x1; i<x2; i+=skok)
    {
        printf("%6.2f:   ",i);
        for(float j=y1; j<y2; j+=skok)
        {
            printf("%6.2f   ",i*j);
        }
        printf("\n");
    }
}

int main()
{
    float x1,x2,y1,y2,skok;
    scanf("%f %f %f %f %f",&x1,&x2,&y1,&y2,&skok);
    tabliczka(x1,x2,y1,y2,skok);
    return 0;
}
