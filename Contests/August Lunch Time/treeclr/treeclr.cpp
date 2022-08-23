// https://www.codechef.com/LTIME111A/problems/TREECLR
#include <bits/stdc++.h>

#define MOD 1000000007

using namespace std;

vector<vector<int>> adj;
long long res;
long long C;

void init(int N)
{
    adj.clear();
    adj.resize(N);

    res = C;
}

void dfs(int node, int p)
{
    long long max_colors = C - 1;
    if (p != -1)
        max_colors--;

    for (int next : adj[node])
    {
        if (next == p)
            continue;

        res = (res * max_colors) % MOD;
        max_colors--;

        // cout << next << " " << max_colors << endl;

        dfs(next, node);

        if (res == 0)
            return;
    }
}

int main()
{
    int N;

    cin >> N >> C;

    init(N);

    for (int i = 0; i < N - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;

        // cout << u << " " << v << endl;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(0, -1);

    cout << res << "\n";
}