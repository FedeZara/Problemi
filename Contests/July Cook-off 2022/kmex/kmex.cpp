// https://www.codechef.com/COOK143D/problems/KMEX
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int N, M, K;
        cin >> N >> M >> K;

        vector<int> times(N + 1, 0);
        for (int i = 0; i < N; i++)
        {
            int a;
            cin >> a;
            times[a]++;
        }

        int count = 0;
        bool possible = M >= K;
        if (possible)
            for (int i = 0; i <= N; i++)
            {
                if (i < K)
                {
                    if (times[i] == 0)
                    {
                        possible = false;
                        break;
                    }
                    count += times[i];
                }
                else if (i > K)
                {
                    count += times[i];
                    if (count >= M)
                        break;
                }
            }
        if (possible && count >= M)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}