#include<stdio.h>
#include<stdlib.h>

char cezar(char c)
{
    if(c>='x')
    {
        c=c-23;
    }
    else
    {
        c=c+3;
    }
    return c;
}

char pisanie(char c, char l)
{
    if(c==9)
    {
        return ' ';
    }
    if(c>='a' && c<='z')
    {
        return cezar(c);
    }
    if(c==l==' ')
    {
        return 8;
    }
    if(c>=32 && c<=126 || c==10)
    {
        return c;
    }
    return 8;
}

int main()
{
    char c,l='a';
    while((c=getchar())!=EOF)
    {
        if(pisanie(c,l)!=8)
        {
            putchar(pisanie(c,l));
        }
        l=c;
    }
    return 0;
}