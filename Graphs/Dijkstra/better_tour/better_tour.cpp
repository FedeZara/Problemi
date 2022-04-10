// https://lightoj.com/problem/better-tour

#include <bits/stdc++.h>

using namespace std;

typedef tuple<int, int, int> qe;

int main()
{
    int T;
    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int N;
        cin >> N;

        int max_node = -1;

        vector<int> nodes;

        for (int i = 0; i < N; i++)
        {
            int n;
            cin >> n;
            nodes.push_back(n - 1);

            if (n > max_node)
                max_node = n;
        }

        vector<vector<int>> adj(max_node);

        int prev_node = nodes[0];
        for (int i = 1; i < nodes.size(); i++)
        {
            int node = nodes[i];
            adj[node].push_back(prev_node);
            adj[prev_node].push_back(node);
            prev_node = node;
        }

        for (int i = 0; i < adj.size(); i++)
            sort(adj[i].begin(), adj[i].end());

        queue<int> q;

        vector<int> prev(max_node, INT_MAX);
        vector<bool> added(max_node, false);

        prev[nodes[0]] = -1;
        added[nodes[0]] = true;
        q.push(nodes[0]);

        while (!q.empty())
        {
            int node = q.front();
            q.pop();

            if (node == nodes[nodes.size() - 1])
                break;

            for (int next : adj[node])
            {
                if (!added[next])
                {
                    prev[next] = node;
                    added[next] = true;

                    q.push(next);
                }
            }
        }

        cout << "Case " << t + 1 << ":" << endl;

        vector<int> path;
        int node = nodes[nodes.size() - 1];
        while (node != -1)
        {
            path.push_back(node);
            node = prev[node];
        }

        for (int i = path.size() - 1; i >= 0; i--)
        {
            cout << path[i] + 1 << " ";
        }

        cout << endl;
    }
}