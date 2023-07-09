#include<iostream>
using namespace std;

int silnia(int n)
{
    if(n==0)
    {
        return 1;
    }
    return n*silnia(n-1);
}

string przeliczanie(int n)
{
    string w="";
    int i=0;
    while(silnia(i)<=n)
    {
        i++;
    }
    i-=1;
    while(i>0)
    {
        w+=(n/silnia(i))+'0';
        n=n%silnia(i);
        i--;
    }
    return w;
}

int main()
{
    cout<<przeliczanie(1548);
    return 0;
}