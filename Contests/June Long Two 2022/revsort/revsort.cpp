// https://www.codechef.com/JUNE222D/problems/REVSORT
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        long long N, X;
        cin >> N >> X;
        vector<long long> values(N);
        for (int i = 0; i < N; i++)
            cin >> values[i];

        bool possible = true;
        for (int i = 1; i < N && possible; i++)
        {
            if (values[i - 1] > values[i])
            {
                if (values[i - 1] + values[i] <= X)
                    swap(values[i - 1], values[i]);
                else
                    possible = false;
            }
        }

        if (possible)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}