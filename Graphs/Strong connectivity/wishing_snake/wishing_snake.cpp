// https://lightoj.com/problem/wishing-snake

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
    {
        dfs1(next);
    }

    trav.push_back(node);
}

int component_count;
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

void init(int M)
{
    adj_rev.clear();
    adj_rev.resize(M);
    for (int i = 0; i < adj.size(); i++)
    {
        for (int next : adj[i])
            adj_rev[next].push_back(i);
    }
    visited.clear();
    visited.resize(M, false);
    trav.clear();
    component_count = 0;
    node_to_component.clear();
    node_to_component.resize(M, -1);
}

int main()
{
    int T;
    cin >> T;

    for (int t = 0; t < T; t++)
    {

        int N;
        cin >> N;

        adj.clear();

        map<int, int> node_to_id;
        vector<int> id_to_node;

        node_to_id[0] = 0;
        id_to_node.push_back(0);
        adj.emplace_back(vector<int>());

        for (int i = 0; i < N; i++)
        {
            int K;
            cin >> K;
            for (int j = 0; j < K; j++)
            {
                int a, b;

                cin >> a >> b;

                for (int node : {a, b})
                {
                    if (node_to_id.find(node) == node_to_id.end())
                    {
                        node_to_id[node] = id_to_node.size();
                        id_to_node.push_back(node);
                        adj.emplace_back(vector<int>());
                    }
                }
                adj[node_to_id[a]].push_back(node_to_id[b]);
            }
        }

        int M = id_to_node.size();

        init(M);

        for (int i = 0; i < M; i++)
        {
            dfs1(i);
        }

        for (int i = M - 1; i >= 0; i--)
        {
            int node = trav[i];
            if (node_to_component[node] == -1)
            {
                dfs2(node, component_count++);
            }
        }

        vector<bool> has_out_node(component_count, false);
        vector<bool> has_in_node(component_count, false);
        int out_node_count = 0;
        int int_node_count = 0;

        bool correct = true;
        for (int node = 0; node < M && correct; node++)
        {
            int from = node_to_component[node];
            for (int next : adj[node])
            {
                int to = node_to_component[next];
                if (from != to)
                {
                    if (has_out_node[from] || has_in_node[to])
                    {
                        correct = false;
                        break;
                    }
                    else
                    {
                        has_out_node[from] = true;
                        has_in_node[to] = true;
                        out_node_count++;
                        int_node_count++;
                    }
                }
            }
        }

        if (correct && (out_node_count != component_count - 1 || int_node_count != component_count - 1 || has_in_node[node_to_component[0]]))
            correct = false;

        cout << "Case " << (t + 1) << ": " << (correct ? "YES" : "NO") << endl;
    }
}