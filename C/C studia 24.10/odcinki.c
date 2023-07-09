#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>

bool prostopadle(double xa, double ya, double xb, double yb, double xc, double yc, double xd, double yd)
{
    double x1=xb-xa;
    double x2=xd-xc;
    double y1=yb-ya;
    double y2=yd-yc;
    if(x1*y1+x2*y2==0)
        return true;
    else return false;
}

bool rownolegle(double xa, double ya, double xb, double yb, double xc, double yc, double xd, double yd)
{
    double x1=xb-xa;
    double x2=xd-xc;
    double y1=yb-ya;
    double y2=yd-yc;
    if(x1*y2-x2*y1==0)
        return true;
    else return false;
}

int main()
{
    int n=1;
    while(n==1)
    {
        double xa,ya,xb,yb,xc,yc,xd,yd;
        printf("Podaj wspolrzedne koncow odcinkow\n");
        scanf("%lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf",&xa,&ya,&xb,&yb,&xc,&yc,&xd,&yd);
        if(prostopadle(xa,ya,xb,yb,xc,yc,xd,yd)==true)
        {
            printf("prostopadle\n");
        }
        else if(rownolegle(xa,ya,xb,yb,xc,yc,xd,yd==true))
        {
            printf("rownolegle\n");
        }
        else
        {
            printf("-\n");
        }
    }
    return 0;
}
