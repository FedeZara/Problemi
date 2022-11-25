// https://itacpc22.kattis.com/contests/wdqnr2/problems/plot
#include <bits/stdc++.h>

using namespace std;

int calcRes(int x, vector<int> &coeff)
{
  int res = 0;
  int xelevated = 1;
  for (int i = 0; i < coeff.size(); i++)
  {
    res += xelevated * coeff[i];
    xelevated *= x;
  }

  return res;
}

int main()
{
  int N;
  cin >> N;
  vector<int> coeff(N + 1);

  int sum = 0;
  for (int i = N; i >= 0; i--)
  {
    cin >> coeff[i];
    sum += coeff[i];
  }

  int t[7][7];
  vector<int> c(N + 1);
  c[0] = coeff[0];
  t[1][1] = c[1] = sum - c[0];

  for (int i = 2; i <= N; i++)
  {
    t[1][i] = calcRes(i, coeff) - calcRes(i - 1, coeff);

    t[i][1] = t[1][i];
    for (int j = 1; j < i; j++)
    {
      t[i][1] -= t[j][i - j];
    }

    for (int j = 2; j < i; j++)
    {
      t[i + 1 - j][j] = t[i + 1 - j][j - 1] + t[i + 2 - j][j - 1];
    }

    c[i] = t[i][1];
  }

  for (int i = 0; i <= N; i++)
    cout << c[i] << " ";
}