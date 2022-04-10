// https://lightoj.com/problem/aladdin-and-the-return-journe

#include <bits/stdc++.h>

#define MAXN 30000

using namespace std;

vector<int> adj[MAXN];

int n;
int tim;
long long weights[MAXN];
int in[MAXN];
int out[MAXN];
int level[MAXN];
long long bit[MAXN + 1];

vector<int> trav;
int index_in_trav[MAXN];

void dfs(int node, int p, int l)
{
    tim++;

    level[node] = l;
    in[node] = tim;

    trav.push_back(node);
    index_in_trav[node] = trav.size() - 1;

    for (int child : adj[node])
    {
        if (child == p)
            continue;

        dfs(child, node, l + 1);
        trav.push_back(node);
    }

    out[node] = tim;
}

vector<vector<int>> table;

void preprocess_lca()
{
    int size = (int)floor(log2(trav.size())) + 1;

    table.clear();

    table.push_back(trav);

    for (int i = 1; i < size; i++)
    {
        int power = 1 << i;

        vector<int> row;
        for (int j = 0; j < trav.size() - power + 1; j++)
        {
            int a = table[i - 1][j], b = table[i - 1][j + power / 2], min = a;
            if (level[b] < level[min])
                min = b;

            row.push_back(min);
        }

        table.push_back(row);
    }
}

int lca(int i, int j)
{
    int i_index = index_in_trav[i], j_index = index_in_trav[j];

    if (j_index < i_index)
        swap(i_index, j_index);

    int power = log2(j_index - i_index + 1);
    int k = 1 << power;
    int a = table[power][i_index], b = table[power][j_index - k + 1], min = a;
    if (level[b] < level[min])
        min = b;

    return min;
}

void update(int index, long long val)
{

    for (; index <= (n + 1); index += index & -index)
    {
        bit[index] += val;
    }
}

long long query(int index)
{

    long long sum = 0;
    for (; index >= 1; index -= index & -index)
    {
        sum += bit[index];
    }

    return sum;
}

void init()
{
    memset(weights, 0, n * sizeof(long long));
    memset(bit, 0, (n + 1) * sizeof(long long));
    memset(in, 0, n * sizeof(int));
    memset(out, 0, n * sizeof(int));
    memset(level, 0, n * sizeof(int));
    memset(index_in_trav, 0, n * sizeof(int));
    trav.clear();

    for (int i = 0; i < n; i++)
        adj[i].clear();

    tim = 0;
}

int main()
{
    int T;
    cin >> T;

    for (int t = 0; t < T; t++)
    {
        cout << "Case " << (t + 1) << ":" << endl;

        cin >> n;

        init();

        for (int i = 0; i < n; i++)
        {
            cin >> weights[i];
        }

        for (int i = 0; i < n - 1; i++)
        {
            int a, b;
            cin >> a >> b;

            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        dfs(0, -1, 0);
        preprocess_lca();

        for (int i = 0; i < n; i++)
        {
            update(in[i], weights[i]);
            update(out[i] + 1, -weights[i]);
        }

        int q;
        cin >> q;
        while (q--)
        {
            int type;
            cin >> type;
            if (type == 0)
            {
                int i, j;
                cin >> i >> j;

                int l = lca(i, j);

                cout << query(in[i]) + query(in[j]) - 2 * query(in[l]) + weights[l] << endl;
            }
            else
            {
                int i;
                long long v;
                cin >> i >> v;

                long long diff = v - weights[i];
                weights[i] = v;

                update(in[i], diff);
                update(out[i] + 1, -diff);
            }
        }
    }
}