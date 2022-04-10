// https://lightoj.com/problem/monkey-banana-problem

#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;
    cin >> T;
    for (int t = 0; t < T; t++)
    {
        int N;
        cin >> N;
        vector<long> matrix[2 * N - 1];
        for (int l = 1; l <= N; l++)
        {
            matrix[l - 1].resize(l);
            for (int i = 0; i < l; i++)
            {
                cin >> matrix[l - 1][i];
            }
        }

        for (int l = N + 1; l <= 2 * N - 1; l++)
        {
            matrix[l - 1].resize(2 * N - l);
            for (int i = 0; i < 2 * N - l; i++)
            {
                cin >> matrix[l - 1][i];
            }
        }

        vector<long> maximum{matrix[0][0]};
        for (int l = 2; l <= N; l++)
        {
            vector<long> newMax;
            newMax.push_back(maximum[0] + matrix[l - 1][0]);

            for (int i = 1; i < l - 1; i++)
            {
                newMax.push_back(max(maximum[i - 1] + matrix[l - 1][i], maximum[i] + matrix[l - 1][i]));
            }

            newMax.push_back(maximum[l - 2] + matrix[l - 1][l - 1]);
            maximum = newMax;
        }

        for (int l = N + 1; l <= 2 * N - 1; l++)
        {
            vector<long> newMax;

            for (int i = 0; i < 2 * N - l; i++)
            {
                newMax.push_back(max(maximum[i] + matrix[l - 1][i], maximum[i + 1] + matrix[l - 1][i]));
            }

            maximum = newMax;
        }

        cout << "Case " << (t + 1) << ": " << maximum[0] << endl;
    }
}