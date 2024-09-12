#include<iostream>
#include<vector>
#include<utility>
#include<cmath>
#include<algorithm>
using namespace std;

double dist(pair<int,int> p1, pair<int,int> p2)
{
    return sqrt((p2.first-p1.first)*(p2.first-p1.first)+(p2.second-p1.second)*(p2.second-p1.second));
}

int main()
{
    int n;
    cin>>n;
    vector<pair<int,int>> points;
    int x,y;
    for(int i=0; i<n; i++)
    {
        cin>>x>>y;
        points.push_back(make_pair(x,y));
    }
    sort(points.begin(),points.end());
    vector<pair<int,int>> wynik(3);
    double najm_obw=1e18;
    double obw;
    for(int i=0; i<n-2; i++)
    {
        for(int j=i+1; j<n-1; j++)
        {
            for(int k=j+1; k<n; k++)
            {
                obw=dist(points[i],points[j])+dist(points[j],points[k])+dist(points[k],points[i]);
                if(obw<najm_obw)
                {
                    najm_obw=obw;
                    wynik={points[i],points[j],points[k]};
                }
            }
        }
    }
    for(int i=0; i<3; i++)
    {
        cout<<wynik[i].first<<" "<<wynik[i].second<<endl;
    }
    cout<<najm_obw<<endl;
    return 0;
}