#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>
#include<stack>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n,q;
    cin>>n>>q;
    vector<pair<int,int>> v;
    int parent;
    for(int i=2; i<=n; i++)
    {
        cin>>parent;
        v.push_back(make_pair(parent,i));
    }
    // for(int i=0; i<v.size(); i++)
    // {
    //     cout<<v[i].first<<" "<<v[i].second<<endl;
    // }
    sort(v.begin(),v.end()); //!!
    // for(int i=0; i<v.size(); i++)
    // {
    //     cout<<v[i].first<<" "<<v[i].second<<endl;
    // }
    stack<int> s;
    vector<bool> visited(1e6+5,false); //!!
    int time=0;
    vector<pair<int,int>> in_out(1e6+5); //!!
    s.push(1);
    int d;
    while(!s.empty())
    {
        int curr=s.top();
        if(!visited[curr])
        {
            visited[curr]=true;
            in_out[curr].first=++time;
            // for(const auto& edge: v)
            // {
            //     if(edge.first==curr)
            //     {
            //         s.push(edge.second);
            //     }
            // }
            auto it=lower_bound(v.begin(),v.end(),make_pair(curr,INT32_MIN));
            if(it!=v.end() && it->first==curr)
            {
                d=distance(v.begin(),it);
            }
            else
            {
                d=v.size()+1;
            }
            // cout<<d<<endl;
            while(d<v.size() && v[d].first==curr)
            {
                s.push(v[d].second);
                d++;
            }
        }
        else
        {
            s.pop();
            in_out[curr].second=++time;
        }    
    }
    for(int i=0; i<q; i++)
    {
        int a,b;
        cin>>a>>b;
        if(in_out[a].first<in_out[b].first && in_out[a].second>in_out[b].second)
        {
            cout<<"TAK"<<endl;
        }
        else
        {
            cout<<"NIE"<<endl;
        }
    }
    return 0;
}