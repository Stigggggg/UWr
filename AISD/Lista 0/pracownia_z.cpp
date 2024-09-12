#include<iostream>
using namespace std;

int main()
{
    int a,b;
    cin>>a>>b;
    if(a>b)
    {
        int temp=a;
        a=b;
        b=temp;
    }
    for(int i=a; i<=b; i++)
    {
        cout<<i<<endl;
    }
    return 0;
}