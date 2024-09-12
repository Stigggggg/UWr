#include<iostream>
#include<vector>
using namespace std;

struct Node
{
    int parent;
    vector<int> children;
};

vector<Node> build(int n)
{
    vector<Node> tree(n+1);
    for(int i=2; i<=n; i++)
    {
        int parent;
        cin>>parent;
        tree[i].parent=parent;
        tree[parent].children.push_back(i);
    }
    return tree;
}

void dfs(int v, vector<Node>& tree, vector<vector<int>>& ancestors)
{
    for(int c: tree[v].children)
    {
        for(int a: ancestors[v])
        {
            ancestors[c].push_back(a);
        }
        ancestors[c].push_back(v);
        dfs(c,tree,ancestors);
    }
}

void build_ancestors(vector<Node>& tree, vector<vector<int>>& ancestors)
{
    int n=tree.size()-1;
    ancestors.resize(n+1);
    dfs(1,tree,ancestors);
}

string is_ancestor(int p, int c, vector<vector<int>>& ancestors)
{
    for(int anc: ancestors[c])
    {
        if(anc==p)
        {
            return "TAK";
        }
    }
    return "NIE";
}

vector<string> answer(vector<vector<int>>& queries, vector<vector<int>>& ancestors)
{
    vector<string> res;
    for(auto& q: queries)
    {
        int a=q[0];
        int b=q[1];
        res.push_back(is_ancestor(a,b,ancestors));
    }
    return res;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n,q;
    cin>>n>>q;
    vector<Node> tree=build(n);
    vector<vector<int>> ancestors;
    build_ancestors(tree, ancestors);
    vector<vector<int>> queries(q,vector<int>(2));
    for(auto& query: queries)
    {
        cin>>query[0]>>query[1];
    }
    vector<string> results=answer(queries,ancestors);
    for(const string& r: results)
    {
        cout<<r<<endl;
    }
    return 0;
}