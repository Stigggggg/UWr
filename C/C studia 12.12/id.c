#include<stdio.h>
#include<stdlib.h>

char tab[1024][1024];
int ile_unikatowych[1024];
int tab_wyst[26][2];

int linia_max_id(int n, int k)
{
    for(int j=0; j<k; j++)
    {
        for(int i=0; i<n; i++)
        {
            int znak=tab[i][j];
            tab_wyst[znak-'a'][0]++;
            tab_wyst[znak-'a'][1]=i;
        }
        for(int l=0; l<26; l++)
        {
            if(tab_wyst[l][0]==1)
            {
                ile_unikatowych[tab_wyst[l][1]]++;
            }
        }
        for(int l=0; l<26; l++)
        {
            tab_wyst[l][0]=0;
            tab_wyst[l][1]=0;
        }
    }
    int linia_max=0;
    for(int i=1; i<n; i++)
    {
        if(ile_unikatowych[i]>ile_unikatowych[linia_max])
        {
            linia_max=i;
        }
    }
    return linia_max;
}

int main()
{
    int n,k;
    if(scanf("%d %d",&n,&k)!=2) 
    {
        return -1;
    }
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<k; j++)
        {
            if(scanf(" %c",&tab[i][j])!=1) 
            {
                return -1;
            }
        }
    }
    int linia=linia_max_id(n,k);
    for (int l=0; l<k; l++)
    {
        printf("%c", tab[linia][l]);
    }
    printf("\n%i", ile_unikatowych[linia]);
    return 0;
}