// https://lightoj.com/problem/prison-break

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, long long> edge;
typedef tuple<long long, int, int> qe;

int main()
{
    int T;
    cin >> T;

    for (int t = 0; t < T; t++)
    {
        cout << "Case " << t + 1 << ": " << endl;

        int N, M;
        cin >> N >> M;

        int fuel_cost[N];

        for (int i = 0; i < N; i++)
            cin >> fuel_cost[i];

        vector<vector<edge>> adj(N);

        for (int i = 0; i < M; i++)
        {
            int a, b, w;
            cin >> a >> b >> w;
            adj[a].push_back({b, w});
            adj[b].push_back({a, w});
        }

        int Q;
        cin >> Q;

        for (int q = 0; q < Q; q++)
        {
            int c, s, t;
            cin >> c >> s >> t;

            vector<vector<bool>> processed(N, vector<bool>(c + 1, false));
            vector<vector<int>> cost(N, vector<int>(c + 1, INT_MAX));

            priority_queue<qe, vector<qe>, greater<qe>> pq;
            cost[s][0] = 0;
            pq.push({0, 0, s});

            int mini = INT_MAX;
            while (!pq.empty())
            {
                qe el = pq.top();
                pq.pop();

                int node_cost = get<0>(el), remaining = get<1>(el), node = get<2>(el);

                if (node == t)
                {
                    mini = node_cost;
                    break;
                }

                if (processed[node][remaining])
                    continue;

                processed[node][remaining] = true;

                for (int i = 1; i <= c - remaining; i++)
                {
                    int next_cost = node_cost + i * fuel_cost[node];
                    if (!processed[node][remaining + i] && cost[node][remaining + i] > next_cost)
                    {
                        cost[node][remaining + i] = next_cost;
                        pq.push({next_cost, remaining + i, node});
                    }
                }

                for (edge e : adj[node])
                {
                    int next = e.first, distance = e.second;
                    if (remaining >= distance && !processed[next][remaining - distance] && cost[next][remaining - distance] > node_cost)
                    {
                        cost[next][remaining - distance] = node_cost;
                        pq.push({node_cost, remaining - distance, next});
                    }
                }
            }
            if (mini == INT_MAX)
                cout << "impossible" << endl;
            else
                cout << mini << endl;
        }
    }
}