#include<stdio.h>

void insertion_sort(int n, int tab[])
{
    for(int i=0; i<n; i++)
    {
        int j=i;
        while(j>0 && tab[j-1]>tab[j])
        {
            int temp=tab[j-1];
            tab[j-1]=tab[j];
            tab[j]=temp;
            j--;
        }
    }
}

int main()
{
    int n;
    scanf("%d",&n);
    int tab[n];
    for(int i=0; i<n; i++)
    {
        scanf("%d",&tab[i]);
    }
    insertion_sort(n,tab);
    for(int i=0; i<n; i++)
    {
        printf("%d ",tab[i]);
    }
    return 0;
}