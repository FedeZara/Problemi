// https://lightoj.com/problem/country-roads

#include <bits/stdc++.h>

#define MAX_N 500

using namespace std;

typedef pair<int, int> edge;
typedef pair<int, int> node;

int main()
{
    int T;
    cin >> T;

    for (int t = 0; t < T; t++)
    {
        cout << "Case " << t + 1 << ":" << endl;

        int N, M;

        cin >> N >> M;

        vector<edge> adj[N];

        for (int i = 0; i < M; i++)
        {
            int a, b, w;
            cin >> a >> b >> w;

            adj[a].push_back({b, w});
            adj[b].push_back({a, w});
        }

        int start;
        cin >> start;

        vector<bool> processed(N, false);
        vector<int> distance(N, INT_MAX);
        priority_queue<node, vector<node>, greater_equal<node>> pq;

        distance[start] = 0;
        pq.push({0, start});

        while (!pq.empty())
        {
            node n = pq.top();
            pq.pop();

            if (processed[n.second])
                continue;

            processed[n.second] = true;

            for (edge e : adj[n.second])
            {
                int dist = max(e.second, n.first);
                if (dist < distance[e.first])
                {
                    distance[e.first] = dist;
                    pq.push({dist, e.first});
                }
            }
        }

        for (int i = 0; i < N; i++)
        {
            if (distance[i] == INT_MAX)
                cout << "Impossible" << endl;
            else
                cout << distance[i] << endl;
        }
    }
}