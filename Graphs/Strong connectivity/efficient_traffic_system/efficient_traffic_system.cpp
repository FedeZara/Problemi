// https://lightoj.com/problem/efficient-traffic-system

#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> adj;
vector<vector<int>> adj_rev;

vector<int> trav;
vector<bool> visited;
void dfs1(int node)
{
    if (visited[node])
        return;

    visited[node] = true;

    for (int next : adj[node])
    {
        dfs1(next);
    }

    trav.push_back(node);
}

int components_count;
vector<int> node_to_component;
void dfs2(int node, int component)
{
    if (node_to_component[node] != -1)
        return;

    node_to_component[node] = component;

    for (int next : adj_rev[node])
    {
        dfs2(next, component);
    }
}

void init(int N)
{
    adj.clear();
    adj.resize(N);
    adj_rev.clear();
    adj_rev.resize(N);

    trav.clear();
    visited.clear();
    visited.resize(N, false);
    components_count = 0;
    node_to_component.clear();
    node_to_component.resize(N, -1);
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
            adj_rev[b].push_back(a);
        }

        for (int i = 0; i < N; i++)
            dfs1(i);

        for (int i = N - 1; i >= 0; i--)
        {
            int node = trav[i];
            if (node_to_component[node] == -1)
                dfs2(node, components_count++);
        }

        vector<bool> out_edge_counted(components_count, false);
        vector<bool> in_edge_counted(components_count, false);
        int no_in_edges_count = components_count;
        int no_out_edges_count = components_count;

        for (int node = 0; node < N; node++)
        {
            for (int next : adj[node])
            {
                int node_component = node_to_component[node], next_component = node_to_component[next];
                if (node_component == next_component)
                    continue;

                if (!out_edge_counted[node_component])
                {
                    out_edge_counted[node_component] = true;
                    no_out_edges_count--;
                }

                if (!in_edge_counted[next_component])
                {
                    in_edge_counted[next_component] = true;
                    no_in_edges_count--;
                }
            }
        }

        cout << "Case " << (t + 1) << ": " << (components_count == 1 ? 0 : max(no_in_edges_count, no_out_edges_count)) << endl;
    }
}