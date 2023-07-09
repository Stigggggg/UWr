#include<stdio.h>
#include<stdlib.h>

void bubble_sort(int n, int tab[])
{
    for(int i=0; i<n-1; i++)
    {
        for(int j=i+1; j<n; j++)
        {
            if(tab[i]>tab[j])
            {
                int tmp=tab[i];
                tab[i]=tab[j];
                tab[j]=tmp;
            }
        }
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
    bubble_sort(n,tab);
    return 0;
}
//n^2, bo 2 pętle: jedna wybiera element po elemencie (O(n)), druga przechodzi przez pozostałe: (O(n))
//Instrukcje dominujące: linia 10
//Uporządkowany: 0 podstawień, ((n-1)*n)/2 porównań
//Odwrócony: tyle samo porównań, tyle podstawień, co porównań