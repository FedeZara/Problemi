// https://lightoj.com/problem/odd-personality

#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> adj;
vector<set<int>> adj_without_bridges;
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
            }
        }
    }
}

int nodes_count;
bool correct;
vector<int> node_to_color;
void dfs_without_bridges(int node, int color)
{
    nodes_count++;
    node_to_color[node] = color;

    for (int next : adj_without_bridges[node])
    {
        int next_color = color == 1 ? -1 : 1;
        if (node_to_color[next] == 0)
        {
            dfs_without_bridges(next, next_color);
        }
        else if (node_to_color[next] != next_color)
            correct = false;
    }
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
    low.resize(N);
    t = 0;
    node_to_color.clear();
    node_to_color.resize(N, 0);
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

        for (int i = 0; i < N; i++)
        {
            if (disc[i] == -1)
                dfs(i);
        }

        int result = 0;
        for (int i = 0; i < N; i++)
        {
            if (node_to_color[i] == 0)
            {
                correct = true;
                nodes_count = 0;
                dfs_without_bridges(i, 1);
                if (!correct && nodes_count > 1)
                    result += nodes_count;
            }
        }

        cout << "Case " << t + 1 << ": " << result << endl;
    }
}