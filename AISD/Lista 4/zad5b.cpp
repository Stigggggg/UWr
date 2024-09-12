#include<bits/stdc++.h>
using namespace std;

// Returns length of LCS and reconstructs the LCS itself
string lcs(string &X, string &Y)
{
    // Find lengths of two strings
    int m = X.length(), n = Y.length();

    int L[2][n + 1];

    // Binary index, used to
    // index current row and
    // previous row.
    bool bi;

    // Arrays to store the LCS characters
    vector<char> lcsChars;

    for (int i = 0; i <= m; i++)
    {
        // Compute current
        // binary index
        bi = i & 1;

        for (int j = 0; j <= n; j++)
        {
            if (i == 0 || j == 0)
                L[bi][j] = 0;

            else if (X[i-1] == Y[j-1]) {
                L[bi][j] = L[1 - bi][j - 1] + 1;
                lcsChars.push_back(X[i-1]);
            }
            else {
                if (L[1 - bi][j] > L[bi][j - 1])
                    L[bi][j] = L[1 - bi][j];
                else
                    L[bi][j] = L[bi][j - 1];
            }
        }
    }

    // Last filled entry contains
    // length of LCS
    int lengthOfLCS = L[bi][n];

    // Reconstructing LCS from lcsChars
    string lcsString;
    for (char c : lcsChars)
        lcsString.push_back(c);

    return lcsString;
}

// Driver code
int main()
{
    string X = "AGGTAB";
    string Y = "GXTXAYB";

    string lcsString = lcs(X, Y);

    cout << "Length of LCS is " << lcsString.length() << endl;
    cout << "LCS is: " << lcsString << endl;

    return 0;
}