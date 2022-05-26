// https://lightoj.com/problem/hiding-gold
#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> point;

vector<vector<int>> first_adj;
vector<int> side;

void dfs(int node, int s = 1)
{
    if (side[node] != -1 && side[node] != s)
        cout << node << endl;
    if (side[node] != -1)
        return;
    side[node] = s;
    for (int next : first_adj[node])
        dfs(next, s == 1 ? 2 : 1);
}

void init(int golds_count)
{
    first_adj.clear();
    first_adj.resize(golds_count);
    side.clear();
    side.resize(golds_count, -1);
}

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int N, M;
        cin >> N >> M;

        vector<point> golds;
        map<point, int> gold_to_node_id;
        vector<vector<char>> matrix(N, vector<char>(M));
        for (int y = 0; y < N; y++)
        {
            string line;
            cin >> line;
            for (int x = 0; x < M; x++)
            {
                matrix[y][x] = line[x];
                if (matrix[y][x] == '*')
                {
                    golds.push_back({x, y});
                    gold_to_node_id[{x, y}] = golds.size() - 1;
                }
            }
        }

        init(golds.size());

        for (int i = 0; i < golds.size(); i++)
        {
            int x = golds[i].first, y = golds[i].second;
            if (y > 0 && matrix[y - 1][x] == '*')
                first_adj[i].push_back(gold_to_node_id[{x, y - 1}]);
            if (y < N - 1 && matrix[y + 1][x] == '*')
                first_adj[i].push_back(gold_to_node_id[{x, y + 1}]);
            if (x > 0 && matrix[y][x - 1] == '*')
                first_adj[i].push_back(gold_to_node_id[{x - 1, y}]);
            if (x < M - 1 && matrix[y][x + 1] == '*')
                first_adj[i].push_back(gold_to_node_id[{x + 1, y}]);
        }

        for (int i = 0; i < golds.size(); i++)
        {
            if (side[i] == -1)
                dfs(i);
        }

        vector<vector<int>> adj(golds.size() + 2);
        vector<vector<bool>> usable(golds.size() + 2, vector<bool>(golds.size() + 2, false));
        int source = golds.size(), sink = golds.size() + 1;

        for (int i = 0; i < golds.size(); i++)
        {
            if (side[i] == 1)
            {
                adj[source].push_back(i);
                adj[i].push_back(source);
                usable[source][i] = true;
                for (int next : first_adj[i])
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
        int matchings = 0;

        do
        {
            found_more = false;
            queue<int> q;
            vector<int> prev(golds.size() + 2, -1);
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

        cout << "Case " << t + 1 << ": " << golds.size() - matchings << endl;
    }
}