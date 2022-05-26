// https://lightoj.com/problem/internet-bandwidth
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int source, sink;
        int N, M;
        cin >> N >> source >> sink >> M;

        source--;
        sink--;

        vector<vector<int>> adj(N);
        vector<vector<int>> c(N, vector<int>(N, 0));

        for (int i = 0; i < M; i++)
        {
            int u, v, w;
            cin >> u >> v >> w;
            u--;
            v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
            c[u][v] += w;
            c[v][u] += w;
        }

        int result = 0;
        int delta_flow = 0;

        do
        {
            delta_flow = 0;
            vector<int> parent(N, -1);
            parent[source] = -2;

            queue<pair<int, int>> q;
            q.push({source, INT_MAX});

            while (!q.empty() && delta_flow == 0)
            {
                pair<int, int> e = q.front();
                q.pop();

                int node = e.first, flow = e.second;

                for (int next : adj[node])
                {
                    if (parent[next] == -1 && c[node][next] > 0)
                    {
                        parent[next] = node;

                        int new_flow = min(flow, c[node][next]);
                        if (next == sink)
                        {
                            delta_flow = new_flow;
                            break;
                        }
                        else
                        {
                            q.push({next, new_flow});
                        }
                    }
                }
            }

            if (delta_flow > 0)
            {
                result += delta_flow;
                int node = sink;
                while (node != source)
                {
                    c[parent[node]][node] -= delta_flow;
                    c[node][parent[node]] += delta_flow;
                    node = parent[node];
                }
            }
        } while (delta_flow > 0);

        cout << "Case " << t + 1 << ": " << result << endl;
    }
}