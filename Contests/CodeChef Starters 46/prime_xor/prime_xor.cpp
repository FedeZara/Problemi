// https://www.codechef.com/START46C/problems/PRIME_XOR
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int X, Y, Z;
        cin >> X >> Y;

        Z = X ^ Y;

        vector<int> values(1, 2);
        if (X % 2 == 0)
        {
            values.push_back(Z ^ 2);
            values.push_back(Y ^ 2);
        }
        else if (Y % 2 == 0)
        {
            values.push_back(X ^ 2);
            values.push_back(Z ^ 2);
        }
        else
        {
            values.push_back(X ^ 2);
            values.push_back(Y ^ 2);
        }

        sort(values.begin(), values.end());

        for (int i = 0; i < 3; i++)
            cout << values[i] << " ";

        cout << endl;
    }
}