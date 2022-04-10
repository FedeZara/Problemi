// https://lightoj.com/problem/critical-links

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> edge;

vector<vector<int>> adj;
vector<bool> visited;
vector<int> tin;
vector<int> low;
vector<edge> bridges;
int timer;

void init(int N)
{
    adj.clear();
    adj.resize(N);
    visited.clear();
    visited.resize(N);
    tin.clear();
    tin.resize(N);
    low.clear();
    low.resize(N);
    bridges.clear();

    timer = 0;
}

void dfs(int node, int p)
{
    visited[node] = true;
    tin[node] = low[node] = timer++;

    for (int next : adj[node])
    {
        if (next == p)
            continue;
        if (visited[next])
        {
            low[node] = min(low[node], tin[next]);
        }
        else
        {
            dfs(next, node);
            low[node] = min(low[node], low[next]);

            if (low[next] > tin[node])
            {
                if (next > node)
                    bridges.push_back({node, next});
                else
                    bridges.push_back({next, node});
            }
        }
    }
}

int main()
{
    int T;
    cin >> T;

    for (int t = 0; t < T; t++)
    {
        cout << "Case " << (t + 1) << ":" << endl;

        int N;
        cin >> N;

        init(N);

        for (int i = 0; i < N; i++)
        {
            int node, M;
            cin >> node;

            scanf(" (%d) ", &M);

            for (int j = 0; j < M; j++)
            {
                int next;
                cin >> next;
                adj[node].push_back(next);
            }
        }

        for (int i = 0; i < N; i++)
        {
            if (!visited[i])
                dfs(i, -1);
        }

        sort(bridges.begin(), bridges.end());

        cout << bridges.size() << " critical links" << endl;
        for (edge b : bridges)
            cout << b.first << " - " << b.second << endl;
    }
}