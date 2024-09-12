#include <iostream>
using namespace std;
 
string lcs(const string& s1, const string& s2)
{
    int m = s1.length(), n = s2.length();
    int prev[n + 1] = {};
    int curr[n+1]={};
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if(s1[i-1]==s2[j-1])
            {
                curr[j]=1+prev[j-1];
            }
            else
            {
                curr[j]=max(curr[j-1],prev[j]);
            }
        }
        for(int i=0; i<=n; i++)
        {
            prev[i]=curr[i];
        }
    }
    //odtworzenie
    string lcs;
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if(s1[i-1]==s2[j-1])
        {
            lcs = s1[i - 1] + lcs;
            i--;
            j--;
            for(int k=0; k<=n; k++)
            {
                curr[k]=prev[k];
            }
            prev[j]--;
        }
        else if(prev[j]>curr[j-1])
        {
            i--;
        }
        else
        {
            j--;
        }
    }
    for(int i=0; i<=n; i++)
    {
        cout<<prev[i]<<" ";
    }
    cout<<endl;
    for(int i=0; i<=n; i++)
    {
        cout<<curr[i]<<" ";
    }
    cout<<endl;
    return lcs;
}
 
int main()
{
    string s1 = "ABZXYC", s2 = "ABCXYZ";
    string r = lcs(s1, s2);
    cout<<"LCS: "<<r<<endl;
    return 0;
}
