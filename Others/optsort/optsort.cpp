// https://www.codechef.com/submit/OPTSORT
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
        vector<pair<int, int>> a(N);

        for (int i = 0; i < N; i++)
        {
            cin >> a[i].first;
            a[i].second = i;
        }

        sort(a.begin(), a.end());

        int result = 0;

        int max_index = -1, maxi = -1, mini = INT_MAX;
        for (int i = 0; i < N; i++)
        {
            max_index = max(max_index, a[i].second);
            maxi = max(maxi, a[i].first);
            mini = min(mini, a[i].first);

            if (max_index == i)
            {
                result += maxi - mini;
                max_index = -1;
                maxi = -1;
                mini = INT_MAX;
            }
        }
        cout << result << "\n";
    }
}