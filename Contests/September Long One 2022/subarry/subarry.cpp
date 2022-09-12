// https://www.codechef.com/SEP221D/problems/SUBARRY
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

        bool has_negatives = false;
        bool has_positives = false;
        priority_queue<long long> max_pq;
        priority_queue<long long, vector<long long>, greater<long long>> min_pq;

        for (int i = 0; i < N; i++)
        {
            long long v;
            cin >> v;
            max_pq.push(v);
            min_pq.push(v);
            if (v < 0)
                has_negatives = true;
            if (v > 0)
                has_positives = true;
        }

        long long max1 = max_pq.top(), min1 = min_pq.top();
        min_pq.pop();
        max_pq.pop();
        long long min2 = min_pq.top();
        long long max2 = max_pq.top();

        long long max_result = max(max1 * max1, min1 * min1), min_result = 0;
        if (has_positives && has_negatives)
            min_result = max1 * min1;
        else if (!has_negatives && has_positives)
            min_result = min1 * min1;
        else if (has_negatives && !has_positives)
            min_result = max1 * max1;

        cout << min_result << " " << max_result << "\n";
    }
}