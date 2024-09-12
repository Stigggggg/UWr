//Mikołaj Drozd
//339139
//MBA
#include<iostream>
using namespace std;

int main()
{
    long long a,b;
    cin>>a>>b;
    for(int i=a; i<=b; i++)
    {
        if(i%2024==0)
        {
            cout<<i<<" ";
        }
    }
    return 0;
}