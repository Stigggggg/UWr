#include<iostream>
#include<cmath>
using namespace std;

int main()
{
    double I[21];
    I[0]=log(2024.0/2023.0);
    for(int i=1; i<=20; i++)
    {
        I[i]=(1.0/i)-2023.0*I[i-1];
    } 
    for(int i=1; i<=19; i+=2)
    {
        cout<<I[i]<<" "<<I[i+1]<<endl;
    }
    return 0;  
}