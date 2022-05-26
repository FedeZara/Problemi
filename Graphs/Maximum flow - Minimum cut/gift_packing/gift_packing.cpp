// https://lightoj.com/problem/gift-packing
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int N;
        cin >> N;

        vector<vector<int>> adj(2 * N + 2);
        vector<vector<bool>> usable(2 * N + 2, vector<bool>(2 * N + 2, false));
        vector<vector<int>> cost(2 * N + 2, vector<int>(2 * N + 2, 0));

        int source = 2 * N, sink = 2 * N + 1;

        for (int i = 0; i < N; i++)
        {
            adj[source].push_back(i);
            adj[i].push_back(source);
            usable[source][i] = true;
            cost[source][i] = cost[i][source] = 0;

            adj[i + N].push_back(sink);
            adj[sink].push_back(i + N);
            usable[i + N][sink] = true;
            cost[sink][i + N] = cost[i + N][sink] = 0;
        }

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                int v;
                cin >> v;

                adj[i].push_back(j + N);
                adj[j + N].push_back(i);
                usable[i][j + N] = true;
                cost[i][j + N] = -v;
                cost[j + N][i] = -cost[i][j + N];
            }
        }

        int result = 0;
        bool found_more = false;
        do
        {
            found_more = false;
            queue<int> q;
            vector<bool> in_queue(2 * N + 2, false);
            vector<int> dist(2 * N + 2, INT_MAX);
            vector<int> prev(2 * N + 2, -1);

            q.push(source);
            in_queue[source] = true;
            dist[source] = 0;
            prev[source] = source;

            while (!q.empty())
            {
                int node = q.front();
                q.pop();

                in_queue[node] = false;

                for (int next : adj[node])
                {
                    if (usable[node][next] && dist[next] > dist[node] + cost[node][next])
                    {
                        dist[next] = dist[node] + cost[node][next];
                        prev[next] = node;
                        if (!in_queue[next])
                        {
                            in_queue[next] = true;
                            q.push(next);
                        }
                    }
                }
            }

            if (dist[sink] < INT_MAX)
            {
                found_more = true;
                result += dist[sink];
                int node = sink;
                while (node != source)
                {
                    int p = prev[node];
                    usable[p][node] = false;
                    usable[node][p] = true;
                    node = p;
                }
            }

        } while (found_more);

        cout << "Case " << t + 1 << ": " << -result << endl;
    }
}