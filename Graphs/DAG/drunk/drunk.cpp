// https://lightoj.com/problem/drunk

#include <bits/stdc++.h>

#define MAX_N 20000

using namespace std;

vector<vector<int>> adj(MAX_N);
int state[MAX_N];

bool dfs(int node)
{
    if (state[node] == 2)
        return true;

    if (state[node] == 1)
        return false;

    state[node] = 1;

    for (int next : adj[node])
    {
        if (!dfs(next))
            return false;
    }

    state[node] = 2;

    return true;
}

int main()
{
    int T;
    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int M;
        cin >> M;

        adj.clear();
        adj.resize(MAX_N);
        memset(state, 0, sizeof(state));

        map<string, int> m;

        int nodes_count = 0;

        for (int i = 0; i < M; i++)
        {
            string a, b;

            cin >> a >> b;

            if (m.find(a) == m.end())
                m[a] = nodes_count++;

            if (m.find(b) == m.end())
                m[b] = nodes_count++;

            adj[m[a]].push_back(m[b]);
        }

        bool correct = true;
        for (int i = 0; i < nodes_count; i++)
        {
            if (!(correct = dfs(i)))
                break;
        }

        cout << "Case " << t + 1 << ": " << (correct ? "Yes" : "No") << endl;
    }
}