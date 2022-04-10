// https://lightoj.com/problem/civil-and-evil-engineer

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> edge;

int main()
{
    int T;
    cin >> T;

    for (int t = 0; t < T; t++)
    {

        int N;
        cin >> N;

        vector<vector<edge>> adj(N + 1);

        bool finished = false;
        while (!finished)
        {
            int a, b, w;
            cin >> a >> b >> w;

            if (a == 0 && b == 0 && w == 0)
            {
                finished = true;
            }
            else
            {
                adj[a].push_back({w, b});
                adj[b].push_back({w, a});
            }
        }

        vector<bool> included(N + 1);

        included[0] = true;

        priority_queue<edge, vector<edge>, greater<edge>> pq1;

        for (edge e : adj[0])
            pq1.push(e);

        int minimum = 0;

        while (!pq1.empty())
        {
            edge e = pq1.top();
            pq1.pop();

            int node = e.second, weight = e.first;

            if (included[node])
                continue;

            included[node] = true;
            minimum += weight;

            for (edge e1 : adj[node])
                pq1.push(e1);
        }

        included.clear();
        included.resize(N + 1);

        included[0] = true;

        priority_queue<edge, vector<edge>, less<edge>> pq2;

        for (edge e : adj[0])
            pq2.push(e);

        int maximum = 0;

        while (!pq2.empty())
        {
            edge e = pq2.top();
            pq2.pop();

            int node = e.second, weight = e.first;

            if (included[node])
                continue;

            included[node] = true;
            maximum += weight;

            for (edge e1 : adj[node])
                pq2.push(e1);
        }

        int sum = maximum + minimum;

        if (sum % 2 == 0)
            cout << "Case " << (t + 1) << ": " << sum / 2 << endl;
        else
            cout << "Case " << (t + 1) << ": " << sum << "/2" << endl;
    }
}