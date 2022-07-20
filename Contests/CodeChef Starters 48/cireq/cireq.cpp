// https://www.codechef.com/START48B/problems/CIREQ
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

        vector<int> val(N);

        for (int i = 0; i < N; i++)
            cin >> val[i];

        sort(val.begin(), val.end());

        int a = 1, b = N;
        int res = INT_MAX;

        while (a <= b)
        {
            int t = (a + b) / 2;

            bool possible = true;
            for (int i = 0; i < N && possible; i += t)
            {
                for (int j = i; j < N && j < i + t && possible; j++)
                {
                    if (val[j] < (i / t) + 1)
                        possible = false;
                }
            }

            if (possible)
            {
                res = min(res, t);
                b = t - 1;
            }
            else
            {
                a = t + 1;
            }
        }

        cout << res << "\n";
    }
}