#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
    char *T=argv[1];
    if(argc!=2)
    {
        printf("za duzo argumentow");
    }
    else if(T[0]=='0')
    {
        printf("zla liczba");
    }
    else
    {
        int k=0;
        int N;
        scanf("%d",&N);
        while(N>0)
        {
            for(int i=0; ; i++)
            {
                if(T[i]=='\0')
                {
                    break;
                }
                k=(k*10+(T[i]-'0'))%N;
            }
            if(k==0)
            {
                printf("TAK\n");
            }
            else
            {
                printf("NIE\n");
            }
            scanf("%d",&N);
        }
    }
    return 1;
}
