// https://itacpc22.kattis.com/contests/itacpc22/problems/itacpc22.gottacatchemtwice
#include <bits/stdc++.h>

using namespace std;

int main()
{
  int N;
  cin >> N;

  set<string> types;
  for (int i = 0; i < N; i++)
  {
    string s;
    cin >> s;
    types.insert(s);
  }

  cout << types.size() + 1;
}