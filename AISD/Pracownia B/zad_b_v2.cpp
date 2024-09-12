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

struct Triangle
{
    pair<int,int> p1,p2,p3;
};

Triangle findClosestTriangle(vector<pair<int,int>>& points) 
{
    int n=points.size();
    if(n<=3) 
    {
        return {points[0],points[1],points[2]};
    }
    int mid=n/2;
    vector<pair<int,int>> left(points.begin(),points.begin()+mid);
    vector<pair<int,int>> right(points.begin()+mid,points.end());
    Triangle closestLeft=findClosestTriangle(left);
    Triangle closestRight=findClosestTriangle(right);
    double minDist=min(dist(closestLeft.p1,closestLeft.p2),min(dist(closestLeft.p2,closestLeft.p3),dist(closestLeft.p3,closestLeft.p1)));
    minDist=min(minDist,min(dist(closestRight.p1,closestRight.p2),min(dist(closestRight.p2,closestRight.p3),dist(closestRight.p3,closestRight.p1))));
    vector<pair<int,int>> strip;
    for(const auto& point: points) 
    {
        if(abs(point.second-points[mid].second)<minDist) 
        {
            strip.push_back(point);
        }
    }
    sort(strip.begin(),strip.end(),[](const pair<int,int>& p1,const pair<int,int>& p2) 
    {
        return p1.second<p2.second;
    });
    Triangle closestStrip={strip[0],strip[1],strip[2]};
    for(int i=0; i<strip.size(); i++) 
    {
        for(int j=i+1; j<min(i+7,(int)strip.size()); j++) 
        {
            for(int k=j+1; k<min(i+7,(int)strip.size()); k++) 
            {
                double distanceIJ=dist(strip[i],strip[j]);
                double distanceIK=dist(strip[i],strip[k]);
                double distanceJK=dist(strip[j],strip[k]);
                double perimeter=distanceIJ+distanceIK+distanceJK;
                if(perimeter<dist(closestStrip.p1,closestStrip.p2)+dist(closestStrip.p2,closestStrip.p3)+dist(closestStrip.p3,closestStrip.p1)) 
                {
                    closestStrip={strip[i],strip[j],strip[k]};
                }
            }
        }
    }
    if(dist(closestLeft.p1,closestLeft.p2)+dist(closestLeft.p2,closestLeft.p3)+dist(closestLeft.p3,closestLeft.p1)<dist(closestRight.p1,closestRight.p2)+dist(closestRight.p2,closestRight.p3)+dist(closestRight.p3,closestRight.p1)) 
    {
        if(dist(closestLeft.p1,closestLeft.p2)+dist(closestLeft.p2,closestLeft.p3)+dist(closestLeft.p3,closestLeft.p1)<dist(closestStrip.p1,closestStrip.p2)+dist(closestStrip.p2,closestStrip.p3)+dist(closestStrip.p3,closestStrip.p1)) 
        {
            return closestLeft;
        } 
        else 
        {
            return closestStrip;
        }
    } 
    else 
    {
        if(dist(closestRight.p1,closestRight.p2)+dist(closestRight.p2,closestRight.p3)+dist(closestRight.p3,closestRight.p1)<dist(closestStrip.p1,closestStrip.p2)+dist(closestStrip.p2,closestStrip.p3)+dist(closestStrip.p3,closestStrip.p1)) 
        {
            
            return closestRight;
        } 
        else 
        {
            return closestStrip;
        }
    }
}

int main()
{
    int n;
    cin>>n;
    vector<pair<int,int>> points(n);
    for(int i=0; i<n; i++)
    {
        cin>>points[i].first>>points[i].second;
    }
    sort(points.begin(),points.end(),[](const pair<int,int>& p1, const pair<int,int>& p2) 
    {
        return p1.first<p2.first;
    });
    Triangle wynik=findClosestTriangle(points);
    cout<<wynik.p1.first<<" "<<wynik.p1.second<<endl;
    cout<<wynik.p2.first<<" "<<wynik.p2.second<<endl;
    cout<<wynik.p3.first<<" "<<wynik.p3.second<<endl;
    return 0;
}