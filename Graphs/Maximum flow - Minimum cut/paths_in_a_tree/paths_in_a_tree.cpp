// https://lightoj.com/problem/paths-in-a-tree
#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> adj;

vector<bool> visited;
vector<vector<int>> adj_reachable_nodes;

void dfs_reachable_nodes(int node)
{
    if (visited[node])
        return;

    visited[node] = true;

    for (int next : adj[node])
    {
        dfs_reachable_nodes(next);
        adj_reachable_nodes[node].push_back(next);
        for (int reachable_node : adj_reachable_nodes[next])
            adj_reachable_nodes[node].push_back(reachable_node);
    }
}

vector<bool> source_nodes_usable;
vector<bool> nodes_sink_usable;
vector<vector<int>> adj_reachable_nodes_rev;
vector<vector<bool>> nodes_nodes_usable;

vector<vector<bool>> visited_2;

bool ford_fulkerson(int node, bool is_left = true)
{
    // cout << node << " " << is_left << endl;
    if (is_left)
    {
        visited_2[node][0] = true;
        for (int next : adj_reachable_nodes[node])
        {
            if (!visited_2[next][1] && nodes_nodes_usable[node][next])
            {
                bool found = ford_fulkerson(next, false);
                if (found)
                {
                    nodes_nodes_usable[node][next] = false;
                    nodes_nodes_usable[next][node] = true;
                    return true;
                }
            }
        }
    }
    else
    {
        visited_2[node][1] = true;
        if (nodes_sink_usable[node])
        {
            nodes_sink_usable[node] = false;
            return true;
        }

        for (int next : adj_reachable_nodes_rev[node])
        {
            if (!visited_2[next][0] && nodes_nodes_usable[node][next])
            {
                bool found = ford_fulkerson(next, true);
                if (found)
                {
                    nodes_nodes_usable[node][next] = false;
                    nodes_nodes_usable[next][node] = true;
                    return true;
                }
            }
        }
    }
    return false;
}

void init(int N)
{
    adj.clear();
    adj.resize(N);
    visited.clear();
    visited.resize(N, false);
    adj_reachable_nodes.clear();
    adj_reachable_nodes.resize(N);
    source_nodes_usable.clear();
    source_nodes_usable.resize(N, true);
    nodes_sink_usable.clear();
    nodes_sink_usable.resize(N, true);
    adj_reachable_nodes_rev.clear();
    adj_reachable_nodes_rev.resize(N);
    nodes_nodes_usable.clear();
    nodes_nodes_usable.resize(N, vector<bool>(N, false));
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

        for (int i = 0; i < N - 1; i++)
        {
            int a, b;
            cin >> a >> b;

            adj[b].push_back(a);
        }

        for (int i = 0; i < N; i++)
            dfs_reachable_nodes(i);

        for (int node = 0; node < N; node++)
        {
            for (int next : adj_reachable_nodes[node])
            {
                nodes_nodes_usable[node][next] = true;
                adj_reachable_nodes_rev[next].push_back(node);
            }
        }

        bool found_more = false;
        int count = 0;

        do
        {
            found_more = false;
            for (int i = 0; i < N; i++)
            {
                visited_2.clear();
                visited_2.resize(N, vector<bool>(2, false));
                if (source_nodes_usable[i])
                {
                    // cout << "started at " << i << endl;
                    if (ford_fulkerson(i))
                    {
                        // cout << "found" << endl;
                        source_nodes_usable[i] = false;
                        found_more = true;
                        count++;
                    }
                }
            }
        } while (found_more);

        cout << "Case " << t + 1 << ": " << N - count << endl;
    }
}