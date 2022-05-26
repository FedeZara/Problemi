// https://lightoj.com/problem/karate-competition
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

        vector<int> values(N);
        for (int i = 0; i < N; i++)
            cin >> values[i];

        int source = 2 * N, sink = 2 * N + 1;

        vector<vector<int>> adj(2 * N + 2);
        vector<vector<bool>> usable(2 * N + 2, vector<bool>(2 * N + 2, false));
        vector<vector<int>> cost(2 * N + 2, vector<int>(2 * N + 2, 0));

        for (int j = 0; j < N; j++)
        {
            int v;
            cin >> v;
            for (int i = 0; i < N; i++)
            {
                adj[i].push_back(j + N);
                adj[j + N].push_back(i);
                usable[i][j + N] = true;
                if (v > values[i])
                    cost[i][j + N] = 2;
                else if (v == values[i])
                    cost[i][j + N] = 1;
                cost[j + N][i] = -cost[i][j + N];
            }
        }

        for (int i = 0; i < N; i++)
        {
            adj[source].push_back(i);
            adj[i + N].push_back(sink);
            usable[source][i] = true;
            usable[i + N][sink] = true;
        }

        int result = 0;
        bool found_more = false;
        do
        {
            queue<int> q;
            vector<bool> in_queue(2 * N + 2, false);
            q.push(source);
            in_queue[source] = true;
            vector<int> dist(2 * N + 2, INT_MAX);
            vector<int> predecessor(2 * N + 2, -1);
            dist[source] = 0;

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
                        predecessor[next] = node;
                        if (!in_queue[next])
                        {
                            q.push(next);
                            in_queue[next] = true;
                        }
                    }
                }
            }

            found_more = dist[sink] < INT_MAX;
            if (found_more)
            {
                result += dist[sink];
                int node = sink;
                while (node != source)
                {
                    int pred = predecessor[node];
                    usable[pred][node] = false;
                    usable[node][pred] = true;
                    node = pred;
                }
            }
        } while (found_more);

        cout << "Case " << t + 1 << ": " << 2 * N - result << endl;
    }
}