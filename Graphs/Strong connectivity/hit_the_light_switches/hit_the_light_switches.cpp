// https://lightoj.com/problem/hit-the-light-switches

#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> adj;
vector<vector<int>> adj_rev;

vector<bool> visited;
vector<int> trav;

void dfs1(int node)
{
    if (visited[node])
        return;

    visited[node] = true;

    for (int next : adj[node])
        dfs1(next);

    trav.push_back(node);
}

int components_count;
vector<int> nodes_component;

void dfs2(int node, int component)
{
    if (nodes_component[node] != -1)
        return;

    nodes_component[node] = component;

    for (int next : adj_rev[node])
        dfs2(next, component);
}

int main()
{
    int T;
    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int N, M;
        cin >> N >> M;

        adj.clear();
        adj.resize(N);
        adj_rev.clear();
        adj_rev.resize(N);
        visited.clear();
        visited.resize(N, false);
        nodes_component.clear();
        nodes_component.resize(N, -1);
        trav.clear();
        components_count = 0;

        for (int i = 0; i < M; i++)
        {
            int a, b;
            cin >> a >> b;
            a--;
            b--;
            adj[a].push_back(b);
            adj_rev[b].push_back(a);
        }

        for (int i = 0; i < N; i++)
            dfs1(i);

        for (int i = N - 1; i >= 0; i--)
        {
            int node = trav[i];
            if (nodes_component[node] == -1)
                dfs2(node, components_count++);
        }

        int count = components_count;
        vector<bool> has_in_edges(components_count, false);
        for (int i = 0; i < N; i++)
        {
            for (int next : adj[i])
            {
                if (nodes_component[i] != nodes_component[next] && !has_in_edges[nodes_component[next]])
                {
                    has_in_edges[nodes_component[next]] = true;
                    count--;
                }
            }
        }

        cout << "Case " << t + 1 << ": " << count << endl;
    }
}