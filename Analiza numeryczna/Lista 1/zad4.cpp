#include<iostream>
#include<vector>
using namespace std;

int main()
{
    double y0=1.0;
    double y1=-1.0/9.0;
    vector<double> v={y0,y1};
    for(int i=2; i<=50; i++)
    {
        v.push_back((80.0/9.0)*v[i-1]+v[i-2]);
    }
    for(int i=0; i<=50; i++)
    {
        cout<<v[i]<<endl;
    }
    return 0;
}