// https://itacpc22.kattis.com/contests/wdqnr2/problems/calculatingdartscores
#include <bits/stdc++.h>

using namespace std;

bool dp[181][4];
string text[181][4];
int p[181][4];
bool calculated[181][4];

bool calc(int n, int moves)
{
  if (n == 0 && moves == 0)
    return true;

  if (n == 0 || moves == 0)
    return false;

  if (!calculated[n][moves])
  {
    dp[n][moves] = false;
    for (int i = 1; i <= 20 && !dp[n][moves]; i++)
    {
      for (int j = 1; j <= 3 && !dp[n][moves]; j++)
      {
        if (n - i * j >= 0 && calc(n - i * j, moves - 1))
        {
          dp[n][moves] = true;

          switch (j)
          {
          case 1:
            text[n][moves] = "single ";
            break;
          case 2:
            text[n][moves] = "double ";
            break;
          case 3:
            text[n][moves] = "triple ";
            break;
          }
          text[n][moves] += to_string(i);
          p[n][moves] = n - i * j;
        }
      }
    }
    calculated[n][moves] = true;
  }

  return dp[n][moves];
}

int main()
{
  int N;
  cin >> N;

  for (int i = 1; i <= 180; i++)
  {
    for (int j = 1; j <= 3; j++)
    {
      calculated[i][j] = false;
      p[i][j] = -1;
    }
  }

  int movesPossible = -1;
  for (int i = 1; i <= 3; i++)
  {
    if (calc(N, i))
    {
      movesPossible = i;
      break;
    }
  }

  if (movesPossible == -1)
    cout << "impossible" << endl;
  else
  {
    for (int i = movesPossible; i > 0; i--)
    {
      cout << text[N][i] << endl;
      N = p[N][i];
    }
  }
}