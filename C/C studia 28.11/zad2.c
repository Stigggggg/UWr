#include<stdio.h>

unsigned jakiBit(unsigned liczba, unsigned nrBitu)
{
    liczba=liczba>>nrBitu;
    return liczba%2;
}

int main()
{
    int n,s;
    scanf("%d %d",&n,&s);
    for(int i=31; i>=0; i--)
    {
        printf("%u",jakiBit(n,i));
    }
    printf("\n");
    if(s>0)
    {
        n=n<<s;
        for(int i=31; i>=0; i--)
        {
            printf("%u",jakiBit(n,i));
        }
    }
    else
    {
        if(s<0)
        {
            s*=-1;
            unsigned lewo=n<<(32-s);
            n=n>>s;
            n=n|lewo;
            for(int i=31; i>=0; i--)
            {
                printf("%u",jakiBit(n,i));
            }
        }
    }
    return 0;
}