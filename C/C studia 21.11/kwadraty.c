#include<stdio.h>
#include<stdlib.h>

int tab[1024][1024];
int byl[1024][1024];

void wczytaj(int n)
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            scanf("%d",&tab[i][j]);
        }
    }
}

void wypisz(int n)
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            printf("%d", tab[i][j]);
        }
        putchar('\n');
    }
}

int row(int n)
{
    int akt=0,max_row=0,poprz=0;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(tab[i][j]==1)
            {
                akt++;
            }
            else if(poprz==1)
            {
                if(akt>max_row)
                {
                    max_row=akt;
                }
                akt=0;
            }
            poprz=tab[i][j];
        }
    }
    if(akt>max_row)
    {
        max_row=akt;
    }
    return max_row;
}

int snake(int n)
{
    int max_snake=0,akt=0,poprz=0;
    for(int i=0; i<n; i++)
    {
        if(i%2==0)
        {
            for(int j=0; j<n; j++)
            {
                if(tab[i][j]==1)
                {
                    akt++;
                }
                else if(poprz==1)
                {
                    if(akt>max_snake)
                    {
                        max_snake=akt;
                    }
                    akt=0;
                }
                poprz=tab[i][j];
            }
        }
        else
        {
            for(int j=n-1; j>=0; j--)
            {
                if(tab[i][j]==1)
                {
                    akt++;
                }
                else if(poprz==1)
                {
                    if(akt>max_snake)
                    {
                        max_snake=akt;
                    }
                    akt=0;
                }
                poprz=tab[i][j];
            }
        }
    }
    if(akt>max_snake)
    {
        max_snake=akt;
    }
    return max_snake;
}

int diagonal(int n) 
{
    int curr = 0, max = 0, prev = 0;
    for(int i = 0; i < n; i++) 
    {
        if(i % 2 == 0) 
        {
            for(int j = 0; j <= i; j++) 
            {
                if(tab[i - j][j] == 1) 
                {
                    curr++;
                }
                else if(prev == 1) 
                {
                    if(curr > max) 
                    {
                        max = curr;
                    }
                    curr = 0;
                }
                prev = tab[i - j][j];
            }
        }
        else 
        {
            for(int j = 0; j <= i; j++) 
            {
                if(tab[j][i - j] == 1) 
                {
                    curr++;
                }
                else if(prev == 1) 
                {
                    if(curr > max) 
                    {
                        max = curr;
                    }
                    curr = 0;
                }
                prev = tab[j][i - j];
            }
        }
    }
    for(int i = n; i < 2*n - 1; i++) 
    {
        if(i % 2 == 0) 
        {
            for(int j = n - 1; (i - j) < n; j--) 
            {
                if(tab[j][i - j] == 1) 
                {
                    curr++;
                }
                else if(prev == 1) 
                {
                    if(curr > max) 
                    {
                        max = curr;
                    }
                    curr = 0;
                }
                prev = tab[j][i - j];
            }
        }
        else 
        {
            for(int j = n - 1; (i - j) < n; j--) 
            {
                if(tab[i - j][j] == 1) 
                {
                    curr++;
                }
                else if(prev == 1) 
                {
                    if(curr > max) 
                    {
                        max = curr;
                    }
                    curr = 0;
                }
                prev = tab[i - j][j];
            }
        }
    }
    if(curr > max) 
    {
        max = curr;
    }
    return max;
}

void sprawdz(int x, int y, int n)
{
    byl[y][x]=1;
    if(y-1>=0 && tab[y-1][x]==1 && !byl[y-1][x]) 
    {
        sprawdz(x,y-1,n);
    }
    if(y+1<n && tab[y+1][x]==1 && !byl[y+1][x]) 
    {
        sprawdz(x,y+1,n);
    }
    if(x-1>=0 && tab[y][x-1]==1 && !byl[y][x-1]) 
    {
        sprawdz(x-1,y,n);
    }
    if(x+1<n && tab[y][x+1]==1 && !byl[y][x+1]) 
    {
        sprawdz(x+1,y,n);
    }
}

int main()
{
    int n;
    scanf("%d",&n);
    wczytaj(n);
    printf("%d %d %d\n",row(n),snake(n),diagonal(n));
    int obszary=0;
    if(n>=6 && n%3==0)
    {
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                if(tab[i][j]==1 && !byl[i][j])
                {
                    sprawdz(j,i,n);
                    obszary++;
                }
            }
        }
        printf("%d",obszary);
    }
    return 0;
}


