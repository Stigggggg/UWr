#include<iostream>
#include<vector>
using namespace std;

int main()
{
    // double y[51];
    // y[0]=1.0;
    // y[1]=-1.0/9.0;
    // for(int i=2; i<=50; i++)
    // {
    //     y[i]=(80.0/9.0)*y[i-1]+y[i-2];
    // }
    // for(int i=0; i<=50; i++)
    // {
    //     cout<<y[i]<<endl;
    // }
    // return 0;
    double y0=1.0;
    double y1=-1.0/9.0;
    double yn;
    cout<<y0<<endl<<y1<<endl;
    for(int i=2; i<=50; i++)
    {
        yn=(80.0/9.0)*y1+y0;
        y0=y1;
        y1=yn;
        cout<<yn<<endl;
    }
    return 0;
}