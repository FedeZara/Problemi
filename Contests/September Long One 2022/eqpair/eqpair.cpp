// https://www.codechef.com/SEP221D/problems/EQPAIR
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

        sort(a.begin(), a.end());

        long long result = 0;
        long long curr_number = a[0], curr_number_times = 1;
        for (int i = 1; i < N; i++)
        {
            if (curr_number == a[i])
            {
                curr_number_times++;
            }
            else
            {
                result += curr_number_times * (curr_number_times - 1) / 2;
                curr_number_times = 1;
                curr_number = a[i];
            }
        }

        result += curr_number_times * (curr_number_times - 1) / 2;

        cout << result << "\n";
    }
}