#include<iostream>
#include<algorithm>
using namespace std;

/*int ile_cyfr(string s)
{  
    int k=1;
    sort(s.begin(),s.end());
    for(int i=1; i<s.length(); i++)
    {
        if(s[i]!=s[i-1])
        {
            k++;
        }
    }
    return k;
}*/



int main()
{
    int n;
    cin>>n;
    int tab[10]={0};
    int k=0;
    while(n>0)
    {
        int cyfra=n%10;
        tab[cyfra]++;
        n/=10;
    }
    for(int i=0; i<10; i++)
    {
        if(tab[i]>0)
        {
            k++;
        }
    }
    cout<<k;
    return 0;
}