// https://itacpc22.kattis.com/contests/itacpc22/problems/itacpc22.inequalityparadox
#include <bits/stdc++.h>

using namespace std;

bool findCycle(int node, vector<vector<int>> &adj, vector<int> &color)
{
  color[node] = 1;
  for (int next : adj[node])
  {
    if (color[next] == 0)
    {
      if (findCycle(next, adj, color))
        return true;
    }
    else if (color[next] == 1)
    {
      return true;
    }
  }
  color[node] = 2;
  return false;
}

int main()
{
  int N;
  cin >> N;

  unordered_map<char, int> charToIdx;
  vector<vector<int>> adj;

  for (int i = 0; i < N; i++)
  {
    char a, b, sign;
    cin >> a >> sign >> b;

    if (charToIdx.find(a) == charToIdx.end())
    {
      charToIdx[a] = adj.size();
      adj.push_back(vector<int>());
    }

    if (charToIdx.find(b) == charToIdx.end())
    {
      charToIdx[b] = adj.size();
      adj.push_back(vector<int>());
    }

    int aIdx = charToIdx[a], bIdx = charToIdx[b];

    if (sign == '>')
      swap(aIdx, bIdx);

    adj[aIdx].push_back(bIdx);
  }

  vector<int> color(adj.size(), 0);
  bool correct = true;
  for (int i = 0; i < adj.size(); i++)
  {
    if (color[i] == 0 && findCycle(i, adj, color))
    {
      correct = false;
      break;
    }
  }

  if (!correct)
    cout << ":(";
  else
    cout << ":)";
}