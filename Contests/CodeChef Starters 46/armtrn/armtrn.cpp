// https://www.codechef.com/START46C/problems/ARMTRN
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
        vector<long long> a(N);
        for (int i = 0; i < N; i++)
            cin >> a[i];

        sort(a.begin(), a.end(), greater<long long>());

        vector<long long> prefix_sum(N);
        prefix_sum[0] = a[0];
        for (int i = 1; i < N; i++)
            prefix_sum[i] = prefix_sum[i - 1] + a[i];

        long long max = 0;
        for (int i = 0; i < N - 1; i++)
        {
            long long val = prefix_sum[i] * (1000 * (N - i - 1) - prefix_sum[N - 1] + prefix_sum[i]);
            if (val > max)
                max = val;
        }
        cout << max << "\n";
    }
}