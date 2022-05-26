// https://lightoj.com/problem/factors-and-multiples
#include <bits/stdc++.h>

using namespace std;

int source, sink;
vector<vector<int>> adj;
vector<vector<bool>> usable;

vector<bool> visited;
bool ford_fulkerson(int node)
{
    visited[node] = true;

    if (node == sink)
        return true;

    for (int next : adj[node])
    {
        if (!visited[next] && usable[node][next])
        {
            if (ford_fulkerson(next))
            {
                usable[node][next] = false;
                usable[next][node] = true;
                return true;
            }
        }
    }

    return false;
}

void init(int nodes_count)
{
    adj.clear();
    adj.resize(nodes_count + 2);
    usable.clear();
    usable.resize(nodes_count + 2, vector<bool>(nodes_count + 2, false));
    source = nodes_count;
    sink = nodes_count + 1;
}

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int N, M;
        cin >> N;
        vector<int> starting_values(N);
        for (int i = 0; i < N; i++)
        {
            cin >> starting_values[i];
        }

        cin >> M;

        init(N + M);
        for (int j = 0; j < M; j++)
        {
            int v;
            cin >> v;
            for (int i = 0; i < N; i++)
            {
                if (v % starting_values[i] == 0)
                {
                    adj[i].push_back(j + N);
                    adj[j + N].push_back(i);
                    usable[i][j + N] = true;
                }
            }
        }

        for (int i = 0; i < N; i++)
        {
            adj[source].push_back(i);
            adj[i].push_back(source);
            usable[source][i] = true;
        }

        for (int j = 0; j < M; j++)
        {
            adj[j + N].push_back(sink);
            adj[sink].push_back(j + N);
            usable[j + N][sink] = true;
        }

        bool has_more = false;
        int result = 0;

        do
        {
            visited.clear();
            visited.resize(N + M + 2, false);
            has_more = ford_fulkerson(source);
            if (has_more)
                result++;
        } while (has_more);

        cout << "Case " << t + 1 << ": " << result << endl;
    }
}