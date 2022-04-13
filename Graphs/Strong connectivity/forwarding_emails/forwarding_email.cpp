// https://lightoj.com/problem/forwarding-emails
#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> adj;
vector<vector<int>> adj_rev;

vector<int> trav;
vector<bool> visited;
void dfs_1(int node)
{
    if (visited[node])
        return;

    visited[node] = true;

    for (int next : adj[node])
        dfs_1(next);

    trav.push_back(node);
}

int components_count;
vector<int> node_to_component;
vector<int> component_dim;
void dfs_2(int node, int component)
{
    if (node_to_component[node] != -1)
        return;

    node_to_component[node] = component;
    component_dim[component]++;

    for (int next : adj_rev[node])
        dfs_2(next, component);
}

vector<int> max_path;
void dfs_3(int node)
{
    if (max_path[node] != -1)
        return;

    if (component_dim[node_to_component[node]] > 1)
    {
        max_path[node] = component_dim[node_to_component[node]];
    }
    else
    {
        max_path[node] = 1;

        for (int next : adj[node])
        {
            dfs_3(next);
            max_path[node] += max_path[next];
        }
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
    visited.resize(N);
    components_count = 0;
    node_to_component.clear();
    node_to_component.resize(N, -1);
    component_dim.clear();
    max_path.clear();
    max_path.resize(N, -1);
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
            int a, b;
            cin >> a >> b;
            a--;
            b--;

            adj[a].push_back(b);
            adj_rev[b].push_back(a);
        }

        for (int i = 0; i < N; i++)
            dfs_1(i);

        for (int i = trav.size() - 1; i >= 0; i--)
        {
            int node = trav[i];
            if (node_to_component[node] == -1)
            {
                component_dim.push_back(0);
                dfs_2(node, components_count++);
            }
        }

        int max = -1, max_node;
        for (int i = 0; i < N; i++)
        {
            dfs_3(i);
            if (max_path[i] > max)
            {
                max = max_path[i];
                max_node = i;
            }
            else if (max_path[i] == max)
                max_node = min(i, max_node);
        }

        cout << "Case " << t + 1 << ": " << max_node + 1 << endl;
    }
}