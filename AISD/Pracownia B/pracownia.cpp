#include<iostream>
#include<vector>
#include<utility>
#include<cmath>
#include<algorithm>
#include<cfloat>

using namespace std;

double dist(pair<int,int> p1, pair<int,int> p2)
{
    long long x=pow((p2.first-p1.first),2);
    long long y=pow((p2.second-p1.second),2);
    return sqrt(x+y);
} 

struct Triangle
{
    pair<int,int> p1,p2,p3;
};

pair<double,Triangle> closest(vector<pair<int,int>>& points)
{
    double min_obw=DBL_MAX;
    Triangle t;
    if(points.size()<6)
    {
        for(int i=0; i<static_cast<int>(points.size())-2; i++)
        {
            for(int j=i+1; j<static_cast<int>(points.size())-1; j++)
            {
                for(int k=j+1; k<static_cast<int>(points.size()); k++)
                {
                    double obw=dist(points[i],points[j])+dist(points[j],points[k])+dist(points[k],points[i]);
                    if(obw<min_obw)
                    {
                        min_obw=obw;
                        t.p1=points[i];
                        t.p2=points[j];
                        t.p3=points[k];
                    }
                }
            }
        }
        return make_pair(min_obw,t);
    }
    int mid=static_cast<int>(points.size())/2;
    vector<pair<int,int>> left(points.begin(),points.begin()+mid);
    vector<pair<int,int>> right(points.begin()+mid,points.end());
    pair<double,Triangle> closest_l=closest(left);
    pair<double,Triangle> closest_r=closest(right);
    double temp_min=min(closest_l.first,closest_r.first);
    if(temp_min==closest_l.first)
    {
        t=closest_l.second;
    }
    else
    {
        t=closest_r.second;
    }
    vector<pair<int,int>> strip;
    for(int i=0; i<static_cast<int>(points.size()); i++)
    {
        if(abs(points[i].first-points[mid].first)<temp_min/2)
        {
            strip.push_back(points[i]);
        }
    }
    sort(strip.begin(),strip.end(),[](const pair<int,int>& p1,const pair<int,int>& p2) 
    {
        return p1.second<p2.second;
    });
    Triangle smallest_t=t;
    double odl;
    for(int i=0; i<static_cast<int>(strip.size()); i++)
    {
        pair<int,int> p1=strip[i];
        for(int j=i+1; j<static_cast<int>(strip.size()) && abs(strip[j].second-p1.second)<temp_min; j++)
        {
            for(int k=j+1; k<static_cast<int>(strip.size()) && abs(strip[k].second-p1.second)<temp_min; k++)
            {
                odl=dist(p1,strip[j])+dist(strip[j],strip[k])+dist(strip[k],p1);
                if(odl<temp_min)
                {
                    smallest_t.p1=p1;
                    smallest_t.p2=strip[j];
                    smallest_t.p3=strip[k];
                }
            }
        }
    }
    odl=dist(smallest_t.p1,smallest_t.p2)+dist(smallest_t.p2,smallest_t.p3)+dist(smallest_t.p3,smallest_t.p1);
    if(odl<temp_min)
    {
        return make_pair(odl,smallest_t);
    }
    else
    {
        return make_pair(temp_min,t);
    }
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
    pair<double,Triangle> res=closest(points);
    cout<<res.second.p1.first<<" "<<res.second.p1.second<<endl;
    cout<<res.second.p2.first<<" "<<res.second.p2.second<<endl;
    cout<<res.second.p3.first<<" "<<res.second.p3.second<<endl;
    cout<<res.first<<endl;
    return 0;
}