// https://www.codechef.com/START48B/problems/STRPERM
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int N, M;
        cin >> N >> M;

        vector<vector<int>> pos_to_numbers(N);
        vector<bool> found(N + 1);
        for (int i = 0; i < M; i++)
        {
            int num, pos;
            cin >> num >> pos;

            pos--;

            pos_to_numbers[pos].push_back(num);

            found[num] = true;
        }

        for (int i = 1; i <= N; i++)
        {
            if (!found[i])
                pos_to_numbers[N - 1].push_back(i);
        }

        priority_queue<int> pq;
        vector<int> res;

        bool possible = true;

        for (int i = N - 1; i >= 0; i--)
        {
            for (int num : pos_to_numbers[i])
                pq.push(num);

            if (pq.empty())
            {
                possible = false;
                break;
            }
            else
            {
                res.push_back(pq.top());
                pq.pop();
            }
        }

        if (possible)
        {
            for (int i = N - 1; i >= 0; i--)
                cout << res[i] << " ";

            cout << "\n";
        }
        else
        {
            cout << -1 << "\n";
        }
    }
}