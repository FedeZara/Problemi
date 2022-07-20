// https://www.codechef.com/START48B/problems/TREEXOR
#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> adj;
vector<int> values;
vector<int> xor_values;

void init(int N)
{
    adj.clear();
    adj.resize(N);

    values.clear();
    values.resize(N, -1);

    xor_values.clear();
    xor_values.resize(N, -1);
}

int dfs(int node, int K)
{
    int max_k = 0;
    xor_values[node] = 0;
    for (int next : adj[node])
    {
        max_k += dfs(next, K - max_k);
        xor_values[node] ^= xor_values[next];
    }

    if (max_k < K)
    {
        max_k++;
        if (xor_values[node] == 1)
            values[node] = 0;
        else
        {
            values[node] = 1;
            xor_values[node] = 1;
        }
    }
    else
    {
        if (xor_values[node] == 0)
            values[node] = 0;
        else
        {
            values[node] = 1;
            xor_values[node] = 0;
        }
    }

    // cout << node << " " << K << ": " << max_k << endl;

    return max_k;
}

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int N, K;
        cin >> N >> K;

        init(N);

        for (int i = 0; i < N - 1; i++)
        {
            int p;
            cin >> p;
            p--;

            adj[p].push_back(i + 1);
        }

        dfs(0, K);

        for (int i = 0; i < N; i++)
            cout << values[i];

        cout << endl;
    }
}