// https://lightoj.com/problem/new-traffic-system

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
        int N, M, K, D;
        cin >> N >> M >> K >> D;

        vector<vector<edge>> adj(N);
        vector<vector<edge>> adj_proposed(N);

        for (int i = 0; i < M; i++)
        {
            int a, b, w;
            cin >> a >> b >> w;

            adj[a].push_back({b, w});
        }

        for (int i = 0; i < K; i++)
        {
            int a, b, w;
            cin >> a >> b >> w;

            adj_proposed[a].push_back({b, w});
        }

        priority_queue<qe, vector<qe>, greater<qe>> pq;

        vector<vector<long long>> dist(N, vector<long long>(D + 1, __LONG_LONG_MAX__));
        vector<vector<bool>> processed(N, vector<bool>(D + 1, false));

        dist[0][0] = 0;
        pq.push({0, 0, 0});

        while (!pq.empty())
        {
            qe el = pq.top();
            pq.pop();

            long long distance = get<0>(el);
            int roads = get<1>(el), node = get<2>(el);

            if (processed[node][roads])
                continue;

            processed[node][roads] = true;

            for (edge e : adj[node])
            {
                int next = e.first;
                long long weight = e.second;
                if (!processed[next][roads] && dist[next][roads] > distance + weight)
                {
                    dist[next][roads] = distance + weight;
                    pq.push({dist[next][roads], roads, next});
                }
            }

            if (roads < D)
                for (edge e : adj_proposed[node])
                {
                    int next = e.first;
                    long long weight = e.second;
                    if (!processed[next][roads + 1] && dist[next][roads + 1] > distance + weight)
                    {
                        dist[next][roads + 1] = distance + weight;
                        pq.push({dist[next][roads + 1], roads + 1, next});
                    }
                }
        }

        long long min_distance = __LONG_LONG_MAX__;

        for (int i = 0; i <= D; i++)
        {
            min_distance = min(min_distance, dist[N - 1][i]);
        }

        if (min_distance == __LONG_LONG_MAX__)
            cout << "Case " << t + 1 << ": Impossible" << endl;
        else
            cout << "Case " << t + 1 << ": " << min_distance << endl;
    }
}