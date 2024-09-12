#include<iostream>
#include<vector>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int a,b,c,d;
    cin>>a>>b>>c>>d;
    vector<vector<char>> wzor(a,vector<char>(b));
    vector<vector<char>> tab(c,vector<char>(d));
    int ile=0;
    for(int i=0; i<a; i++)
    {
        for(int j=0; j<b; j++)
        {
            cin>>wzor[i][j];
        }
    }
    for(int i=0; i<c; i++)
    {
        for(int j=0; j<d; j++)
        {
            cin>>tab[i][j];
        }
    }
    for(int i=0; i<c-a+1; i++)
    {
        for(int j=0; j<d-b+1; j++)
        {
            bool git=true;
            for(int k=0; k<a; k++)
            {
                for(int l=0; l<b; l++)
                {
                    if(tab[i+k][j+l]!=wzor[k][l])
                    {
                        git=false;
                        break;
                    }
                }
                if(git==false) //jesli jeden wiersz sie nie zgadza, to nie ma co szukac dalej
                {
                    break;
                }
            }
            if(git==true)
            {
                ile++;
            }
        }
    }
    cout<<ile<<endl;
    return 0;
}