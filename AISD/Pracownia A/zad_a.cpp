#include<iostream>
#include<vector>
using namespace std;

int main()
{
    int n,q;
    cin>>n>>q;
    vector<int> parents(n+1);
    for(int i=2; i<=n; i++)
    {
        cin>>parents[i];
    }
    for(int i=0; i<q; i++)
    {
        int p,c;
        cin>>p>>c;
        while(c!=1)
        {
            if(parents[c]==p)
            {
                cout<<"TAK"<<endl;
                break;
            }
            c=parents[c];
        }
        if(c==1)
        {
            cout<<"NIE"<<endl;
        }
    }
    return 0;
}