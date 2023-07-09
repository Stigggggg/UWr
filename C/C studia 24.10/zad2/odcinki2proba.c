#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main()
{
    int n=1;
    double xa,ya,xb,yb,xc,yc,xd,yd;
    while(n==1)
    {
        printf("Podaj wspolrzedne odcinkow:\n");
        scanf("%lf %lf %lf %lf %lf %lf %lf %lf",&xa,&ya,&xb,&yb,&xc,&yc,&xd,&yd);
        double aP=(yb-ya)/(xb-xa);
        double aQ=(yd-yc)/(xd-xc);
        double dlP=sqrt((xb-xa)*(xb-xa)+(yb-ya)*(yb-ya));
        double dlQ=sqrt((xd-xc)*(xd-xc)+(yd-yc)*(yd-yc));
        if((xa==xb && xc==xd) || (ya==yb && yc==yd))
        {
            printf("rownolegle\n");
        }
        else if((xa==xb && yc==yd) || (xc==xd && ya==yb))
        {
            printf("rownolegle\n");
        }
        else
        {
            if(dlP==0 || dlQ==0)
            {
                printf("Dlugosc 0!\n");
            }
            else
            {
                if(aP==aQ)
                {
                    printf("rownolegle\n");
                }
                else if(aP*aQ==-1)
                {
                    printf("prostopadle\n");
                }
                else
                {
                    printf("-\n");
                }
            }
        }
    }
    return 0;
}
