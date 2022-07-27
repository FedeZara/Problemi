// https://www.codechef.com/START49B/problems/MONKS
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        long long N;
        cin >> N;
        vector<long long> arr(N);

        for (int i = 0; i < N; i++)
            cin >> arr[i];

        sort(arr.begin(), arr.end());

        vector<long long> prefix_sum(N);
        prefix_sum[0] = arr[0];

        for (int i = 1; i < N; i++)
            prefix_sum[i] = prefix_sum[i - 1] + arr[i];

        long long a = 1, b = N;
        long long maxi = -1;

        while (a <= b)
        {
            long long t = (a + b) / 2;

            if (prefix_sum[N - 1] >= arr[t - 1] * t)
            {
                maxi = max(maxi, t);
                a = t + 1;
            }
            else
            {
                b = t - 1;
            }
        }

        cout << N - maxi << "\n";
    }
}