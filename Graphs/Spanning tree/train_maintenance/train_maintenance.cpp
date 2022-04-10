// https://lightoj.com/problem/trail-maintenance

#include <bits/stdc++.h>

using namespace std;

typedef tuple<int, int, int> edge;

vector<int> link;
vector<int> size;

int find(int a)
{
    while (link[a] != a)
        a = link[a];
    return a;
}

bool same(int a, int b)
{
    return find(a) == find(b);
}

void unite(int a, int b)
{
    a = find(a);
    b = find(b);
    if (size[a] < size[b])
        swap(a, b);

    size[a] += size[b];
    link[b] = a;
}

vector<vector<int>> matrix;
vector<vector<bool>> included;
vector<bool> visited;
pair<int, int> max_edge;

bool dfs(int node, int end, int N)
{
    if (node == end)
        return true;

    if (visited[node])
        return false;

    visited[node] = true;

    for (int i = 0; i < N; i++)
    {
        if (included[node][i])
        {
            if (dfs(i, end, N))
            {
                if (matrix[node][i] > matrix[max_edge.first][max_edge.second])
                    max_edge = {node, i};
                return true;
            }
        }
    }

    return false;
}

pair<int, int> find_max_edge_in_path(int start, int end, int N)
{
    visited.clear();
    visited.resize(N, false);

    max_edge = {start, end};
    dfs(start, end, N);
    return max_edge;
}

void init(int N)
{
    link.clear();
    link.resize(N);
    for (int i = 0; i < N; i++)
        link[i] = i;
    size.clear();
    size.resize(N, 1);
    matrix.clear();
    matrix.resize(N, vector<int>(N, INT_MAX));
    included.clear();
    included.resize(N, vector<bool>(N, false));
}

int main()
{
    int T;
    cin >> T;

    for (int t = 0; t < T; t++)
    {
        cout << "Case " << (t + 1) << ":" << endl;
        int N, W;
        cin >> N >> W;

        init(N);

        int total_weight = 0;

        for (int i = 0; i < W; i++)
        {
            int a, b, w;
            cin >> a >> b >> w;
            a--;
            b--;

            if (w < matrix[a][b])
            {
                int old_w = matrix[a][b];
                matrix[a][b] = w;
                matrix[b][a] = w;

                if (!same(a, b))
                {
                    total_weight += w;
                    unite(a, b);
                    included[a][b] = true;
                    included[b][a] = true;
                }
                else if (included[a][b])
                {
                    total_weight -= old_w;
                    total_weight += w;
                }
                else
                {
                    pair<int, int> edge = find_max_edge_in_path(a, b, N);
                    // cout << "Max edge: " << edge.first << " " << edge.second << " " << matrix[edge.first][edge.second] << endl;
                    if (matrix[edge.first][edge.second] > matrix[a][b])
                    {
                        included[edge.first][edge.second] = false;
                        included[edge.second][edge.first] = false;
                        included[a][b] = true;
                        included[b][a] = true;
                        total_weight -= matrix[edge.first][edge.second];
                        total_weight += matrix[a][b];
                    }
                }
            }

            bool connected = true;
            for (int i = 1; i < N && connected; i++)
                connected = same(0, i);

            cout << (connected ? total_weight : -1) << endl;
        }
    }
}