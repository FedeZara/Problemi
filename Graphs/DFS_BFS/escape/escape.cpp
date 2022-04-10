// https://lightoj.com/problem/escape

#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> adj;
int res;
int reached_nodes;

vector<int> value;
bool dfs(int node, int val)
{
    if (value[node] != -1)
        return value[node] == val;

    value[node] = val;
    if (val == 1)
        res++;

    reached_nodes++;

    bool correct = true;
    for (int next : adj[node])
    {
        if (!dfs(next, val == 0 ? 1 : 0))
            correct = false;
    }

    return correct;
}

void init(int N)
{
    res = 0;
    reached_nodes = 0;
    adj.clear();
    adj.resize(N);
    value.clear();
    value.resize(N, -1);
}

int main()
{
    int T;
    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int N, M;
        cin >> N >> M;

        init(N);

        for (int i = 0; i < M; i++)
        {
            int a, b;
            cin >> a >> b;
            a--;
            b--;

            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        if (adj[0].empty())
            cout << "Case " << (t + 1) << ": " << 0 << endl;
        else if (dfs(0, 1))
            cout << "Case " << (t + 1) << ": " << res << endl;
        else
            cout << "Case " << (t + 1) << ": " << reached_nodes << endl;
    }
}