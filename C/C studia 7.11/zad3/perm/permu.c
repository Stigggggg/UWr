#include<stdio.h>
#include<stdlib.h>

int byl[1000000];

int main()
{
    int n;
    scanf("%d",&n);
    int perm[n];
    for(int i=1; i<=n; i++)
    {
        scanf("%d",&perm[i]);
    }
    int max_dl=-1;
    for(int i=1; i<=n; i++)
    {
        int dl=1,akt=i;
        if(byl[akt]==0)
        {
            byl[akt]=1;
            while(byl[perm[akt]]!=1)
            {
                akt=perm[akt];
                dl++;
            }
            if(dl>max_dl)
            {
                max_dl=dl;
            }
        }
        else
        {
            if(dl>max_dl)
            {
                max_dl=dl;
            }
        }
    }
    printf("%d",max_dl);
    return 0;
}