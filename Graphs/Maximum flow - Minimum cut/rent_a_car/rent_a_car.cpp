// https://lightoj.com/problem/rent-a-car
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int N, C, R;
        cin >> N >> C >> R;

        vector<int> car_required(N);
        vector<int> car_per_company(C);
        vector<int> car_cost_company(C);
        vector<pair<int, int>> services(R);

        int flow_goal = 0;

        for (int i = 0; i < N; i++)
        {
            cin >> car_required[i];
            flow_goal += car_required[i];
        }

        for (int i = 0; i < C; i++)
        {
            cin >> car_per_company[i];
            cin >> car_cost_company[i];
        }

        for (int i = 0; i < R; i++)
        {
            int days, cost;
            cin >> days >> cost;
            services[i].first = cost;
            services[i].second = days;
        }

        sort(services.begin(), services.end());

        int nodes_count = N + C + N + 2;
        int source = nodes_count - 2, sink = nodes_count - 1;

        vector<vector<int>> adj(nodes_count);
        vector<vector<int>> capacity(nodes_count, vector<int>(nodes_count, 0));
        vector<vector<int>> cost(nodes_count, vector<int>(nodes_count, 0));

        for (int i = 0; i < N; i++)
        {
            adj[i].push_back(sink);
            adj[sink].push_back(i);
            capacity[i][sink] = car_required[i];
        }

        for (int i = 0; i < C; i++)
        {
            adj[source].push_back(i + N);
            adj[i + N].push_back(source);
            capacity[source][i + N] = car_per_company[i];

            for (int j = 0; j < N; j++)
            {
                adj[i + N].push_back(j);
                adj[j].push_back(i + N);
                capacity[i + N][j] = INT_MAX;
                cost[i + N][j] = car_cost_company[i];
                cost[j][i + N] = -car_cost_company[i];
            }
        }

        for (int i = 0; i < N; i++)
        {
            adj[source].push_back(i + N + C);
            adj[i + N + C].push_back(source);
            capacity[source][i + N + C] = car_required[i];

            for (int j = 0; j < N; j++)
            {
                int c = -1;
                for (pair<int, int> service : services)
                {
                    if (j - i > service.second)
                    {
                        c = service.first;
                        break;
                    }
                }

                if (c != -1)
                {
                    adj[i + N + C].push_back(j);
                    adj[j].push_back(i + N + C);
                    capacity[i + N + C][j] = INT_MAX;
                    cost[i + N + C][j] = c;
                    cost[j][i + N + C] = -c;
                }
            }
        }

        /*for (int i = 0; i < nodes_count; i++)
        {
            cout << i << ": ";
            for (int next : adj[i])
                if (capacity[i][next] > 0)
                    cout << next << " ";
            cout << endl;
        }*/

        int flow = 0;
        int new_flow = 0;
        int total_cost = 0;

        do
        {
            new_flow = 0;

            queue<int> q;
            vector<bool> in_queue(nodes_count, false);
            vector<int> prev(nodes_count, -1);
            vector<int> dist(nodes_count, INT_MAX);

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
                new_flow = flow_goal - flow;
                int node = sink;
                while (node != source)
                {
                    int p = prev[node];
                    new_flow = min(new_flow, capacity[p][node]);
                    node = p;
                }

                total_cost += new_flow * dist[sink];
                flow += new_flow;

                node = sink;
                while (node != source)
                {
                    int p = prev[node];
                    capacity[p][node] -= new_flow;
                    capacity[node][p] += new_flow;
                    node = p;
                }
            }

        } while (new_flow > 0 && flow < flow_goal);

        if (flow < flow_goal)
            cout << "Case " << t + 1 << ": impossible" << endl;
        else
            cout << "Case " << t + 1 << ": " << total_cost << endl;
    }
}