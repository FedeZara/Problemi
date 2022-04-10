// https://lightoj.com/problem/extended-traffic

#include <bits/stdc++.h>

using namespace std;

typedef tuple<int, int, int> edge;

int main()
{
    int T;
    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int N;
        cin >> N;

        vector<int> weights(N);

        for (int i = 0; i < N; i++)
            cin >> weights[i];

        vector<edge> edges;

        int M;
        cin >> M;
        for (int i = 0; i < M; i++)
        {
            int a, b;
            cin >> a >> b;
            a--;
            b--;

            int diff = pow(weights[b] - weights[a], 3);
            edges.push_back({diff, a, b});
        }

        vector<int> distance(N, INT_MAX);
        distance[0] = 0;

        vector<bool> negative_cycle(N, false);
        for (int i = 0; i < 2 * N; i++)
        {
            for (edge e : edges)
            {
                int from = get<1>(e), to = get<2>(e), weight = get<0>(e);
                if (distance[from] != INT_MAX && distance[to] > distance[from] + weight)
                {
                    distance[to] = distance[from] + weight;
                    if (i >= N - 1)
                        negative_cycle[to] = true;
                }
            }
        }

        cout << "Case " << (t + 1) << ":" << endl;

        int Q;
        cin >> Q;
        for (int i = 0; i < Q; i++)
        {
            int dest;
            cin >> dest;
            dest--;

            if (negative_cycle[dest] || distance[dest] < 3 || distance[dest] == INT_MAX)
                cout << "?" << endl;
            else
                cout << distance[dest] << endl;
        }
    }
}