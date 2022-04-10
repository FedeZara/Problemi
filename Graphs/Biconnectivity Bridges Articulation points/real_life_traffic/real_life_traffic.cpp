// https://lightoj.com/problem/real-life-traffic

#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> adj;
vector<set<int>> adj_without_bridges;
vector<pair<int, int>> bridges;

vector<int> disc;
vector<int> low;

int t;
void dfs(int node, int p = -1)
{
    low[node] = disc[node] = t++;

    for (int next : adj[node])
    {
        if (next == p)
            continue;
        if (disc[next] != -1)
            low[node] = min(low[node], disc[next]);
        else
        {
            dfs(next, node);
            low[node] = min(low[node], low[next]);
            if (low[next] > disc[node])
            {
                adj_without_bridges[next].erase(node);
                adj_without_bridges[node].erase(next);
                bridges.push_back({node, next});
            }
        }
    }
}

int components_count;
vector<int> node_to_component;
void dfs_without_bridges(int node, int component)
{
    if (node_to_component[node] != -1)
        return;

    node_to_component[node] = component;

    for (int next : adj_without_bridges[node])
        dfs_without_bridges(next, component);
}

void init(int N)
{
    adj.clear();
    adj.resize(N);
    adj_without_bridges.clear();
    adj_without_bridges.resize(N);
    disc.clear();
    disc.resize(N, -1);
    low.clear();
    low.resize(N, -1);
    bridges.clear();
    t = 0;
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
            adj[a].push_back(b);
            adj[b].push_back(a);
            adj_without_bridges[a].insert(b);
            adj_without_bridges[b].insert(a);
        }

        dfs(0);

        for (int i = 0; i < N; i++)
        {
            if (node_to_component[i] == -1)
            {
                dfs_without_bridges(i, components_count++);
            }
        }

        vector<int> component_degree(components_count, 0);

        for (auto edge : bridges)
        {
            component_degree[node_to_component[edge.first]]++;
            component_degree[node_to_component[edge.second]]++;
        }

        int count = 0;
        for (int degree : component_degree)
            if (degree == 1)
                count++;

        cout << "Case " << t + 1 << ": " << (count + 1) / 2 << endl;
    }
}