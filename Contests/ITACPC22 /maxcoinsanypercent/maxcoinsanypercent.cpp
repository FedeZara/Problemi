// https://itacpc22.kattis.com/contests/itacpc22/problems/itacpc22.maxcoinsanypercent
#include <bits/stdc++.h>

using namespace std;

vector<long long> coins;

vector<vector<int>> adj;
vector<vector<int>> adjReverse;

vector<int> dfs1List;
vector<bool> dfs1Visited;

void dfs1(int node)
{
  if (dfs1Visited[node])
    return;

  dfs1Visited[node] = true;

  for (int child : adj[node])
    dfs1(child);

  dfs1List.push_back(node);
}

vector<int> components;
void dfs2(int node, int component)
{
  if (components[node] != -1)
  {
    return;
  }

  components[node] = component;

  for (int child : adjReverse[node])
  {
    dfs2(child, component);
  }
}

void init(int N)
{
  adj.resize(N);
  adjReverse.resize(N);
  coins.resize(N);
  dfs1Visited.resize(N, false);
  components.resize(N, -1);
}

vector<long long> componentsCoins;
vector<vector<int>> componentsAdj;

vector<long long> dp;
long long calcMaxCoins(int comp)
{
  if (dp[comp] == -1)
  {
    if (comp == components.back())
    {
      dp[comp] = componentsCoins[comp];
    }
    else
    {
      long long maxi = -2;
      for (int next : componentsAdj[comp])
      {
        maxi = max(maxi, calcMaxCoins(next));
      }

      if (maxi == -2)
        dp[comp] = -2;
      else
        dp[comp] = maxi + componentsCoins[comp];
    }
  }
  return dp[comp];
}

int main()
{
  int N, M;
  cin >> N >> M;

  init(N);

  for (int i = 0; i < N; i++)
    cin >> coins[i];

  for (int i = 0; i < M; i++)
  {
    int a, b;
    cin >> a >> b;

    adj[a].push_back(b);
    adjReverse[b].push_back(a);
  }

  for (int i = 0; i < N; i++)
  {
    dfs1(i);
  }

  int componentCount = 0;
  for (int i = N - 1; i >= 0; i--)
  {
    int node = dfs1List[i];
    if (components[node] == -1)
    {
      dfs2(node, componentCount);
      componentCount++;
    }
  }

  dp.resize(componentCount, -1);
  componentsCoins.resize(componentCount);
  componentsAdj.resize(componentCount);

  for (int i = 0; i < N; i++)
  {
    componentsCoins[components[i]] += coins[i];
    for (int next : adj[i])
    {
      if (components[next] != components[i])
        componentsAdj[components[i]].push_back(components[next]);
    }
  }

  cout << calcMaxCoins(components[0]);
}