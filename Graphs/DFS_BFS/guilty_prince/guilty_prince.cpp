// https://lightoj.com/problem/country-roads

#include <bits/stdc++.h>

#define MAX_N 400

using namespace std;

int W, H;
vector<vector<int>> adj;
vector<bool> is_land;
vector<bool> visited;
int reached;

int coord_to_node(int x, int y)
{
    return y * W + x;
}

void dfs(int node)
{
    if (!is_land[node] || visited[node])
        return;

    visited[node] = true;
    reached++;

    for (int next : adj[node])
        dfs(next);
}

int main()
{
    int T;
    cin >> T;

    for (int t = 0; t < T; t++)
    {

        cin >> W >> H;

        adj.clear();
        adj.resize(W * H);
        is_land.clear();
        is_land.resize(W * H, false);
        visited.clear();
        visited.resize(W * H, false);

        reached = 0;

        int start;

        for (int y = 0; y < H; y++)
        {
            string line;
            cin >> line;

            for (int x = 0; x < W; x++)
            {
                int node = coord_to_node(x, y);
                is_land[node] = line[x] != '#';
                if (line[x] == '@')
                    start = node;

                if (x > 0)
                    adj[node].push_back(coord_to_node(x - 1, y));
                if (x < W - 1)
                    adj[node].push_back(coord_to_node(x + 1, y));
                if (y > 0)
                    adj[node].push_back(coord_to_node(x, y - 1));
                if (y < H - 1)
                    adj[node].push_back(coord_to_node(x, y + 1));
            }
        }

        dfs(start);

        cout << "Case " << t + 1 << ": " << reached << endl;
    }
}