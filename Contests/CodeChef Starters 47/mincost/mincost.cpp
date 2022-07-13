// https://www.codechef.com/START47B/problems/MINCOST
#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> adj;
vector<tuple<long long, long long, long long>> v;
vector<bool> visited;
vector<vector<long long>> memo;

void init(int N)
{
    adj.clear();
    adj.resize(N);

    v.clear();
    v.resize(N);

    visited.clear();
    visited.resize(N, false);

    memo.clear();
    memo.resize(N, vector<long long>(2, -1));
}

long long dfs(int node, bool part_of_s)
{
    if (memo[node][part_of_s ? 0 : 1] == -1)
    {
        visited[node] = true;

        long long dist = 0;
        if (part_of_s)
        {
            vector<long long> val;
            for (int next : adj[node])
            {
                val.push_back(get<1>(v[next]));
            }

            sort(val.begin(), val.end());
            long long z = val.size();
            long long med = val[(z - 1) / 2];

            long long chosen_val;
            if (med < get<0>(v[node]))
                chosen_val = get<0>(v[node]);
            else if (med > get<2>(v[node]))
                chosen_val = get<2>(v[node]);
            else
                chosen_val = med;

            for (int next : adj[node])
            {
                dist += abs(get<1>(v[next]) - chosen_val);
            }
        }

        for (int next : adj[node])
        {
            if (!visited[next])
            {
                if (part_of_s)
                {
                    dist += dfs(next, false);
                }
                else
                {
                    dist += min(dfs(next, false) + abs(get<1>(v[node]) - get<1>(v[next])), dfs(next, true));
                }
            }
        }

        visited[node] = false;
        memo[node][part_of_s ? 0 : 1] = dist;
    }

    return memo[node][part_of_s ? 0 : 1];
}

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int N;
        cin >> N;
        init(N);

        for (int i = 0; i < N; i++)
        {
            long long l, a, r;
            cin >> l >> a >> r;
            v[i] = {l, a, r};
        }

        for (int i = 0; i < N - 1; i++)
        {
            int u, v;
            cin >> u >> v;
            u--;
            v--;

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        cout << min(dfs(0, true), dfs(0, false)) << "\n";
    }
}