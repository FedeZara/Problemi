// https://www.codechef.com/START49B/problems/HIGHFREQ
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
        set<int> found;
        map<int, int> count;

        for (int i = 0; i < N; i++)
        {
            int v;
            cin >> v;
            found.insert(v);

            if (count.find(v) == count.end())
            {
                count[v] = 1;
            }
            else
            {
                count[v]++;
            }
        }

        priority_queue<int> pq;
        for (int el : found)
            pq.push(count[el]);

        int maxi = (pq.top() + 1) / 2;

        pq.pop();

        if (pq.empty() || pq.top() < maxi)
            cout << maxi << "\n";
        else
            cout << pq.top() << "\n";
    }
}