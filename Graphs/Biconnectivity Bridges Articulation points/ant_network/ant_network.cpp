// https://lightoj.com/problem/ant-network

#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> adj;
bool has_ap;
vector<bool> is_ap;
vector<int> disc;
vector<int> low;

int t;
void dfs(int node, int p = -1)
{
    low[node] = disc[node] = t++;

    int children = 0;

    for (int next : adj[node])
    {
        if (next == p)
            continue;
        if (disc[next] != -1)
            low[node] = min(low[node], disc[next]);
        else
        {
            children++;
            dfs(next, node);
            low[node] = min(low[node], low[next]);

            if (p != -1 && low[next] >= disc[node])
                has_ap = is_ap[node] = true;
        }
    }

    if (p == -1 && children > 1)
        has_ap = is_ap[node] = true;
}

set<int> aps;
unsigned long nodes_count;
vector<bool> visited;

void dfs2(int node)
{
    if (visited[node])
        return;

    if (is_ap[node])
    {
        aps.insert(node);
        return;
    }

    nodes_count++;

    visited[node] = true;

    for (int next : adj[node])
    {
        dfs2(next);
    }
}

void init(int N)
{
    adj.clear();
    adj.resize(N);
    disc.clear();
    disc.resize(N, -1);
    low.clear();
    low.resize(N);
    t = 0;
    is_ap.clear();
    is_ap.resize(N, false);
    visited.clear();
    visited.resize(N, false);
    has_ap = false;
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
            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        dfs(0);

        int result = 0;
        unsigned long possibilites = 1;

        if (has_ap)
        {
            for (int i = 0; i < N; i++)
            {
                if (!visited[i])
                {
                    aps.clear();
                    nodes_count = 0;

                    dfs2(i);

                    // If we have more than one articulation point, the component
                    // doesn't need any escape shaft (two ways to reach other shafts)
                    if (nodes_count > 0 && aps.size() < 2)
                    {
                        result++;
                        possibilites *= nodes_count;
                    }
                }
            }
        }
        // If the graph is 2-vertex-connected (no articulation points) we need
        // two nodes selected from the graph
        else
        {
            result = 2;
            possibilites = N * (N - 1) / 2;
        }

        cout << "Case " << t + 1 << ": " << result << " " << possibilites << endl;
    }
}