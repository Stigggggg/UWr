#include<iostream>
#include<string>
#include<vector>
#include<utility>

using namespace std;

bool czy_dobry_arg(string s)
{
    for(int i=0; i<s.length(); i++)
    {
        if(s[i]<'0' || s[i]>'9')
        {
            return 0;
        }
    }
    int n;
    try{n=stoi(s);}
    catch(...)
    {
        return 0;
    }
    if(n<1 || n>3999)
    {
        return 0;
    }
    return 1;
}

string bin2rzym(int x)
{
    const vector<pair<int,string>> rzym={{1000,"M"},{900,"CM"},{500,"D"},{400,"CD"},{100,"C"},{90,"XC"},{50,"L"},{40,"XL"},{10,"X"},{9,"IX"},{5,"V"},{4,"IV"},{1,"I"}};
    string wyn="";
    for(auto p: rzym)
    {
        while(x-p.first>=0)
        {
            wyn+=p.second;
            x-=p.first;
        }
    }
    return wyn;
}

int main(int argc, const char *argv[])
{
    if(argc<2)
    {
        clog<<"Za malo argumentow";
    }
    for(int i=1; i<argc; i++)
    {
        string s=argv[i];
        if(czy_dobry_arg(s)==0)
        {
            clog<<"Niewlasciwy argument na pozycji "<<i<<endl;
        }
        else
        {
            int n=stoi(s);
            cout<<bin2rzym(n)<<endl;
        }
    }
    return 0;
}