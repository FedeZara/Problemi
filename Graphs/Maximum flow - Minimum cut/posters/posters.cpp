// https://www.codechef.com/submit-v2/POSTERS
#include <bits/stdc++.h>

using namespace std;

struct poster
{
    int x0, x1, y0, y1;
};

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int N;
        cin >> N;

        vector<poster> posters(N);

        for (int i = 0; i < N; i++)
        {
            cin >> posters[i].x0 >> posters[i].x1 >> posters[i].y0 >> posters[i].y1;
        }

        int nodes_count = 2 * N + 2;
        int source = nodes_count - 2, sink = nodes_count - 1;
        vector<vector<int>> adj(nodes_count);
        vector<vector<bool>> usable(nodes_count, vector<bool>(nodes_count, false));

        for (int i = 0; i < N; i++)
        {
            adj[source].push_back(i);
            adj[i].push_back(source);
            usable[source][i] = true;

            adj[i + N].push_back(sink);
            adj[sink].push_back(i + N);
            usable[i + N][sink] = true;
        }

        for (int i = 0; i < N; i++)
        {
            poster p1 = posters[i];
            int width1 = p1.x1 - p1.x0;
            for (int j = 0; j < N; j++)
            {
                if (i == j)
                    continue;

                poster p2 = posters[j];
                int width2 = p2.x1 - p2.x0;
                if (width1 < width2 && p1.x0 > p2.x0 && p1.x1 < p2.x1 && p1.y0 < p2.y0 && p1.y1 > p2.y1)
                {
                    adj[i].push_back(j + N);
                    adj[j + N].push_back(i);
                    usable[i][j + N] = true;
                }
            }
        }

        int matchings = 0;
        bool found_more = false;

        do
        {
            found_more = false;
            queue<int> q;
            vector<int> prev(nodes_count, -1);
            q.push(source);
            prev[source] = source;

            while (!q.empty())
            {
                int node = q.front();
                q.pop();

                if (node == sink)
                    break;

                for (int next : adj[node])
                {
                    if (usable[node][next] && prev[next] == -1)
                    {
                        prev[next] = node;
                        q.push(next);
                    }
                }
            }

            if (prev[sink] != -1)
            {
                found_more = true;
                matchings++;

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

        cout << N - matchings << endl;
    }
}