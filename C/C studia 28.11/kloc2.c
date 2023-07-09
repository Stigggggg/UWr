#include<stdio.h>
#include<math.h>

int main()
{
    int d;
    int sc=scanf("%d",&d);
    sc--;
    for(int i=d-2; i>=1; i--)
    {
        for(int j=d-1; j>=i; j--)
        {
            int p=d*d-i*i-j*j;
            if(p>0)
            {
                if((int)sqrt(p)==sqrt(p) && p>=j*j)
                {
                    printf("%d %d %d",(int)sqrt(p),j,i);
                    return 0;
                }
            }
        }
    }
    printf("BRAK");
    return 0;
}