#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

using namespace std;

struct Coin 
{
    int value;
    int weight;
};

long long dp_min[1000010];
long long dp_max[1000010];
int coins_min[1000010];
int coins_max[1000010];

int main() 
{
    int F,C;
    cin>>F>>C;
    int temp=F;
    vector<Coin> coins(C);
    for (int i=0; i<C; i++) 
    {
        cin>>coins[i].value>>coins[i].weight;
    }
    for(int i=0; i<=F; i++)
    {
        dp_min[i]=INT_MAX;
        dp_max[i]=INT_MIN;
    }
    //szukam minimalnej wartosci
    dp_min[0]=0;
    for(const auto& coin: coins)
    {
        for(int j=coin.weight; j<=F; j++)
        {
            if(dp_min[j-coin.weight]!=INT_MAX)
            {
                dp_min[j]=min(dp_min[j],dp_min[j-coin.weight]+coin.value);
            }
        }
    }
    long long min_val=dp_min[F];
    //analogicznie szukam maksymalnej
    dp_max[0]=0;
    for(const auto& coin: coins)
    {
        for(int j=coin.weight; j<=F; j++)
        {
            if(dp_max[j-coin.weight]!=INT_MIN)
            {
                dp_max[j]=max(dp_max[j],dp_max[j-coin.weight]+coin.value);//
            }
        }
    }
    long long max_val=dp_max[F];
    if(min_val==INT_MAX || max_val==INT_MIN)
    {
        cout<<"NIE"<<endl;
    }
    else
    {
        cout<<"TAK"<<endl;
        cout<<min_val<<endl;
        //dla min_val sprawdzam, ile trzeba jakich monet zeby ja uzyskac
        for(int i=C-1; i>=0; i--)
        {
            while(dp_min[F]==dp_min[F-coins[i].weight]+coins[i].value && F>=coins[i].weight)
            {
                coins_min[i]++;
                F-=coins[i].weight;
            }
        }
        for(int i=0; i<C; i++)
        {
            cout<<coins_min[i]<<" ";
        }
        cout<<endl;
        cout<<max_val<<endl;
        //to samo dla max
        for(int i=C-1; i>=0; i--)
        {
            while(dp_max[temp]==dp_max[temp-coins[i].weight]+coins[i].value && temp>=coins[i].weight)
            {
                coins_max[i]++;
                temp-=coins[i].weight;
            }
        }
        for(int i=0; i<C; i++)
        {
            cout<<coins_max[i]<<" ";
        }
        cout<<endl;
    }
    return 0;
}