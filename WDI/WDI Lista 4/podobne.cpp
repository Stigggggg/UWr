#include<iostream>
using namespace std;

bool czy_podobne(string n, string m)
{
    int tab_wyst_n[10]={0};
    int tab_wyst_m[10]={0};
    for(int i=0; i<n.length(); i++)
    {
        tab_wyst_n[n[i]-'0']++;
    }
    for(int i=0; i<m.length(); i++)
    {
        tab_wyst_m[m[i]-'0']++;
    }
    for(int i=0; i<10; i++)
    {
        if(tab_wyst_m[i]!=tab_wyst_n[i])
        {
            return false;
        }
    }
    return true;
}

int main()
{
    string n,m;
    cin>>n>>m;
    cout<<czy_podobne(n,m);
    return 0;
}