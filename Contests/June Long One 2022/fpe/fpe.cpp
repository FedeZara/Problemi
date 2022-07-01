// https://www.codechef.com/JUNE221D/problems/FPE
#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> adj;
vector<long long> values;
vector<bool> visited;

void init(int N)
{
    adj.clear();
    adj.resize(N);
    values.clear();
    values.resize(N);
    visited.clear();
    visited.resize(N);
}

long long gcd(long long a, long long b)
{
    if (a == 0)
        return b;

    return gcd(b % a, a);
}

pair<long long, long long> dfs(int node)
{
    visited[node] = true;

    long long node_gcd = values[node];
    long long res = 0;
    long long diff = 0;
    for (int next : adj[node])
    {
        if (visited[next])
            continue;
        pair<long long, long long> next_vals = dfs(next);
        node_gcd = gcd(node_gcd, next_vals.first);

        if (next_vals.second - next_vals.first > diff)
        {
            res += next_vals.second;
            res -= diff;
            diff = next_vals.second - next_vals.first;
        }
        else
            res += next_vals.first;
    }

    return {node_gcd, res};
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
            cin >> values[i];

        for (int i = 0; i < N - 1; i++)
        {
            int u, v;
            cin >> u >> v;
            u--;
            v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        auto res = dfs(0);

        cout << res.second << "\n";
    }
}