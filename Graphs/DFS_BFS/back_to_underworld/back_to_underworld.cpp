// https://lightoj.com/problem/back-to-underworld

#include <bits/stdc++.h>

#define MAX_N 20000

using namespace std;

vector<vector<int>> adj(MAX_N);

bool visited[MAX_N];

pair<int, int> dfs(int node, bool value)
{
    if (visited[node] || adj[node].empty())
        return {0, 0};

    visited[node] = true;

    pair<int, int> res{0, 0};

    if (value)
        res.first = 1;
    else
        res.second = 1;

    for (int next : adj[node])
    {
        auto p = dfs(next, !value);
        res.first += p.first;
        res.second += p.second;
    }

    return res;
}

int main()
{
    int T;
    cin >> T;

    for (int t = 0; t < T; t++)
    {
        adj.clear();
        adj.resize(MAX_N);
        memset(visited, 0, sizeof(visited));

        int M;
        cin >> M;

        int N;

        for (int i = 0; i < M; i++)
        {
            int a, b;
            cin >> a >> b;

            N = max(max(a, b), N);

            a--;
            b--;

            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        int res = 0;
        for (int i = 0; i < N; i++)
        {
            auto r = dfs(i, true);
            res += max(r.first, r.second);
        }

        cout << "Case " << (t + 1) << ": " << res << endl;
    }
}