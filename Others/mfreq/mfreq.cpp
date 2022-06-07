// https://www.codechef.com/submit-v2/MFREQ
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N, M;
    cin >> N >> M;

    vector<int> values(N);
    vector<pair<int, int>> ranges;
    vector<int> pos_to_range(N);

    for (int i = 0; i < N; i++)
    {
        cin >> values[i];
        if (i == 0 || values[i] != values[i - 1])
        {
            pos_to_range[i] = ranges.size();
            ranges.push_back({i, i});
        }
        else
        {
            pos_to_range[i] = pos_to_range[i - 1];
            ranges[pos_to_range[i]].second = i;
        }
    }

    for (int i = 0; i < M; i++)
    {
        int L, R, k;
        cin >> L >> R >> k;
        L--;
        R--;

        int mid = (L + R + 1) / 2;

        pair<int, int> range = ranges[pos_to_range[mid]];

        int start = max(L, range.first);
        int end = min(R, range.second);

        if (end - start + 1 >= k)
        {
            cout << values[mid] << endl;
        }
        else
        {
            cout << -1 << endl;
        }
    }
}