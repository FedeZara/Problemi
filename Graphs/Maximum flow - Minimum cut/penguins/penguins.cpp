// https://lightoj.com/problem/penguins
#include <bits/stdc++.h>

using namespace std;

struct piece
{
    int x, y, n, m;
};

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int N;
        double D;
        cin >> N >> D;

        vector<piece> pieces(N);
        int total_penguins = 0;

        for (int i = 0; i < N; i++)
        {
            cin >> pieces[i].x >> pieces[i].y >> pieces[i].n >> pieces[i].m;
            total_penguins += pieces[i].n;
        }

        vector<vector<int>> adj(N);

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (i == j)
                    continue;
                if (pow(pieces[i].x - pieces[j].x, 2) + pow(pieces[i].y - pieces[j].y, 2) <= D * D)
                {
                    adj[i].push_back(j);
                }
            }
        }

        cout << "Case " << t + 1 << ": ";

        bool found_one = false;

        for (int p = 0; p < N; p++)
        {
            vector<vector<int>> c(2 * N, vector<int>(2 * N, 0));
            vector<vector<int>> second_adj(2 * N);
            int source = 2 * p + 1, sink = 2 * p;

            for (int i = 0; i < N; i++)
            {
                if (p == i)
                    continue;

                second_adj[source].push_back(2 * i);
                second_adj[2 * i].push_back(source);
                c[source][2 * i] = pieces[i].n;

                second_adj[2 * i].push_back(2 * i + 1);
                second_adj[2 * i + 1].push_back(2 * i);
                c[2 * i][2 * i + 1] = pieces[i].m;

                for (int next : adj[i])
                {
                    second_adj[2 * i + 1].push_back(2 * next);
                    second_adj[2 * next].push_back(2 * i + 1);
                    c[2 * i + 1][2 * next] = INT_MAX;
                }
            }

            int new_flow = 0, result = 0;

            do
            {
                queue<pair<int, int>> q;
                vector<int> prev(2 * N, -1);

                q.push({source, INT_MAX});
                prev[source] = source;

                new_flow = 0;

                while (!q.empty() && new_flow == 0)
                {
                    int node = q.front().first, flow = q.front().second;
                    q.pop();

                    if (node == sink)
                    {
                        new_flow = flow;
                        break;
                    }

                    for (int next : second_adj[node])
                    {
                        if (prev[next] == -1 && c[node][next] > 0)
                        {
                            prev[next] = node;
                            q.push({next, min(c[node][next], flow)});
                        }
                    }
                }

                if (new_flow > 0)
                {
                    int node = sink;
                    while (node != source)
                    {
                        int p = prev[node];
                        c[p][node] -= new_flow;
                        c[node][p] += new_flow;
                        node = p;
                    }

                    result += new_flow;
                }
            } while (new_flow > 0);

            if (result == total_penguins - pieces[p].n)
            {
                cout << p << " ";
                found_one = true;
            }
        }

        if (!found_one)
            cout << "-1";

        cout << endl;
    }
}