#include<stdio.h>
#include<stdlib.h>

void selection_sort(int n, int tab[])
{
    for(int i=0; i<n-1; i++)
    {
        int min_ind=i;
        for(int j=i+1; j<n; j++)
        {
            if(tab[j]<tab[min_ind])
            {
                min_ind=j;
            }
        }
        int tmp=tab[i];
        tab[i]=tab[min_ind];
        tab[min_ind]=tmp;
        
    }
    for(int i=0; i<n; i++)
    {
        printf("%d ",tab[i]);
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
    selection_sort(n,tab);
    return 0;
}
//n^2, bo 2 pętle: jedna wybiera element po elemencie (O(n)), druga przechodzi przez pozostałe: (O(n))
//Instrukcje dominujące: linia 11
//Uporządkowany: 0 podstawień, (n-1)*n/2 porównań
//Odwrócony: tyle samo porównań, podłoga(n/2) podstawień