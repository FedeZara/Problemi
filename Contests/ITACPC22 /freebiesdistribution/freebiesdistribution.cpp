// https://itacpc22.kattis.com/contests/itacpc22/problems/itacpc22.freebiesdistribution
#include <bits/stdc++.h>

using namespace std;

int main()
{
  int M;

  cin >> M;

  vector<int> booths(M);
  for (int i = 0; i < M; i++)
  {
    cin >> booths[i];
  }

  sort(booths.begin(), booths.end());

  int x, y;
  cin >> y >> x;

  vector<int> distanceFromBooth(M);
  for (int i = 0; i < M; i++)
  {
    distanceFromBooth[i] = y + abs(x - booths[i]);
  }

  int N;
  cin >> N;

  vector<int> playersBefore(M);
  for (int i = 0; i < N; i++)
  {
    int xp, yp;
    cin >> yp >> xp;

    int idx = lower_bound(booths.begin(), booths.end(), xp) - booths.begin();

    int booth;
    if (idx == M)
    {
      booth = M - 1;
    }
    else if (idx == 0)
    {
      booth = 0;
    }
    else
    {
      if (booths[idx] - xp < xp - booths[idx - 1])
      {
        booth = idx;
      }
      else
      {
        booth = idx - 1;
      }
    }

    if (yp + abs(xp - booths[booth]) <= distanceFromBooth[booth])
    {
      playersBefore[booth]++;
    }
  }

  int mini = INT_MAX;
  for (int i = 0; i < M; i++)
  {
    if (playersBefore[i] < mini)
    {
      mini = playersBefore[i];
    }
  }

  cout << mini;
}