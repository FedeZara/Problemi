// https://lightoj.com/problem/a-perfect-murder

#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> temp_adj;
// 0 -> not determined, 1 -> left, 2 -> right
vector<int> side;

void dfs(int node, int s)
{
    if (side[node] != 0)
        return;
    side[node] = s;
    for (int next : temp_adj[node])
        dfs(next, s == 1 ? 2 : 1);
}

void init(int N)
{
    temp_adj.clear();
    temp_adj.resize(N);
    side.clear();
    side.resize(N);
}

int main()
{
    int T;
    cin >> T;

    for (int t = 0; t < T; t++)
    {

        int N, M;
        cin >> N;
        cin >> M;

        init(N);

        for (int i = 0; i < M; i++)
        {
            int a, b;
            cin >> a >> b;

            a--;
            b--;

            temp_adj[a].push_back(b);
            temp_adj[b].push_back(a);
        }

        for (int i = 0; i < N; i++)
            dfs(i, 1);

        vector<vector<int>> adj(N + 2);
        vector<vector<bool>> usable(N + 2, vector<bool>(N + 2, false));
        int source = N, sink = N + 1;

        for (int i = 0; i < N; i++)
        {
            if (side[i] == 1)
            {
                adj[source].push_back(i);
                adj[i].push_back(source);
                usable[source][i] = true;
                for (int next : temp_adj[i])
                {
                    adj[i].push_back(next);
                    adj[next].push_back(i);
                    usable[i][next] = true;
                }
            }
            else
            {
                adj[i].push_back(sink);
                adj[sink].push_back(i);
                usable[i][sink] = true;
            }
        }

        bool found_more = false;
        int result = 0;

        do
        {
            queue<int> q;
            q.push(source);

            vector<bool> visited(N + 2, false);
            vector<int> prev(N + 2, -1);
            visited[source] = true;

            while (!q.empty())
            {
                int node = q.front();
                q.pop();

                if (node == sink)
                    break;

                for (int next : adj[node])
                {
                    if (usable[node][next] && !visited[next])
                    {
                        visited[next] = true;
                        prev[next] = node;
                        q.push(next);
                    }
                }
            }

            found_more = prev[sink] != -1;
            if (found_more)
            {
                result++;
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

        cout << "Case " << (t + 1) << ": " << N - result << endl;
    }
}