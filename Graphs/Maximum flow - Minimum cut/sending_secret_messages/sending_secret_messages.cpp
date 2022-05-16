// https://lightoj.com/problem/sending-secret-messages
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int N, M, P;
        cin >> N >> M >> P;

        int source = 0, sink = N - 1;
        vector<vector<int>> adj(N);
        vector<vector<int>> reversed_adj(N);
        vector<vector<int>> capacity(N, vector<int>(N, 0));
        vector<vector<int>> reversed_capacity(N, vector<int>(N, 0));
        vector<vector<int>> cost(N, vector<int>(N, INT_MAX));

        for (int i = 0; i < M; i++)
        {
            int u, v, w, c;

            cin >> u >> v >> w >> c;
            u--;
            v--;

            adj[u].push_back(v);
            reversed_adj[v].push_back(u);
            capacity[u][v] = w;
            reversed_capacity[v][u] = 0;
            cost[u][v] = c;

            adj[v].push_back(u);
            reversed_adj[u].push_back(v);
            capacity[v][u] = w;
            reversed_capacity[u][v] = 0;
            cost[v][u] = c;
        }

        int flow = 0;
        int new_flow = 0;
        int total_cost = 0;

        do
        {
            new_flow = 0;

            queue<int> q;
            vector<bool> in_queue(N, false);
            vector<int> prev(N, -1);
            vector<int> dist(N, INT_MAX);
            vector<bool> used_rev_edge(N, false);

            q.push(source);
            in_queue[source] = true;
            prev[source] = source;
            dist[source] = 0;

            while (!q.empty())
            {
                int node = q.front();
                q.pop();

                in_queue[node] = false;

                for (int next : adj[node])
                {
                    if (capacity[node][next] > 0 && dist[next] > dist[node] + cost[node][next])
                    {
                        dist[next] = dist[node] + cost[node][next];
                        prev[next] = node;
                        used_rev_edge[next] = false;
                        if (!in_queue[next])
                        {
                            q.push(next);
                            in_queue[next] = true;
                        }
                    }
                }

                for (int next : reversed_adj[node])
                {
                    if (reversed_capacity[node][next] > 0 && dist[next] > dist[node] - cost[next][node])
                    {
                        dist[next] = dist[node] - cost[next][node];
                        prev[next] = node;
                        used_rev_edge[next] = true;
                        if (!in_queue[next])
                        {
                            q.push(next);
                            in_queue[next] = true;
                        }
                    }
                }
            }

            if (prev[sink] != -1)
            {
                new_flow = P - flow;
                int node = sink;
                while (node != source)
                {
                    int p = prev[node];
                    if (used_rev_edge[node])
                        new_flow = min(new_flow, reversed_capacity[p][node]);
                    else
                        new_flow = min(new_flow, capacity[p][node]);
                    node = p;
                }

                total_cost += new_flow * dist[sink];
                flow += new_flow;

                node = sink;
                while (node != source)
                {
                    int p = prev[node];
                    if (used_rev_edge[node])
                    {
                        reversed_capacity[p][node] -= new_flow;
                        capacity[node][p] += new_flow;
                    }
                    else
                    {
                        capacity[p][node] -= new_flow;
                        reversed_capacity[node][p] += new_flow;
                    }
                    node = p;
                }
            }

        } while (new_flow > 0 && flow < P);

        if (flow < P)
            cout << "Case " << t + 1 << ": impossible" << endl;
        else
            cout << "Case " << t + 1 << ": " << total_cost << endl;
    }
}