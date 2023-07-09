#include<iostream>
using namespace std;

bool czy_palindrom(string s, int k)
{
    for(int i=0; i<s.length()/2; i++)
    {
        if(s[i]-'0'>=k || s[s.length()-i-1]-'0'>=k)
        {
            return false;
        }
        else if(s[i]!=s[s.length()-i-1])
        {
            return false;
        }
    }
    return true;
}

int main()
{
    string s;
    int k;
    cin>>s>>k;
    cout<<czy_palindrom(s,k);
    return 0;
}