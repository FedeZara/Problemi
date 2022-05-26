// https://training.olinfo.it/#/task/itoi_tasks

#include <bits/stdc++.h>

using namespace std;

vector<int> value;
vector<vector<int>> adj;
vector<vector<long long>> dp;

void init(int N, int C)
{
    value.resize(N);

    adj.clear();
    adj.resize(N);

    dp.clear();
    dp.resize(N, vector<long long>(C + 1));
}

void dfs(int node)
{
    vector<long long> candidates;

    for (int next : adj[node])
    {
        dfs(next);
        candidates.insert(candidates.end(), dp[next].begin(), dp[next].end());
    }

    sort(candidates.begin(), candidates.end(), greater<long long>());

    if (candidates.size() < dp[node].size())
        candidates.resize(dp[node].size(), 0);

    dp[node][0] = candidates[0] + value[node];

    for (int i = 1; i < dp[node].size(); i++)
    {
        dp[node][i] = min(candidates[i - 1], candidates[i] + value[node]);
    }
}

int main()
{
    int N, C;
    cin >> N >> C;

    init(N, C);

    int root;

    for (int i = 0; i < N; i++)
    {
        int p;
        cin >> p;
        if (p != -1)
            adj[p].push_back(i);
        else
            root = i;
        cin >> value[i];
    }

    dfs(root);

    cout << dp[root][C] << endl;
}