#include<iostream>
using namespace std;

bool czy_palindrom(string s)
{
    for(int i=0; i<s.length()/2; i++)
    {
        if(s[i]!=s[s.length()-i-1])
        {
            return false;
        }
    }
    return true;
}

int main()
{
    string s;
    cin>>s;
    cout<<czy_palindrom(s);
    return 0;
}