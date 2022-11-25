// https://itacpc22.kattis.com/contests/wdqnr2/problems/glitchbot
#include <bits/stdc++.h>

using namespace std;

bool getsToDestination(int tx, int ty, vector<string> &instructions)
{
  int dx[] = {0, -1, 0, 1};
  int dy[] = {1, 0, -1, 0};
  int currentDirection = 0;

  int x = 0, y = 0;

  for (int i = 0; i < instructions.size(); i++)
  {
    if (instructions[i] == "Left")
      currentDirection = (currentDirection + 1) % 4;
    else if (instructions[i] == "Right")
      currentDirection = (currentDirection + 3) % 4;
    else
    {
      x += dx[currentDirection];
      y += dy[currentDirection];
    }
  }

  return x == tx && y == ty;
}

int main()
{
  int x, y, n;
  cin >> x >> y >> n;

  vector<string> instructions(n);
  for (int i = 0; i < n; i++)
    cin >> instructions[i];

  for (int i = 0; i < n; i++)
  {
    string originalInstruction = instructions[i];

    if (originalInstruction != "Left")
    {
      instructions[i] = "Left";
      if (getsToDestination(x, y, instructions))
      {
        cout << i + 1 << " Left" << endl;
        return 0;
      }
    }

    if (originalInstruction != "Right")
    {
      instructions[i] = "Right";
      if (getsToDestination(x, y, instructions))
      {
        cout << i + 1 << " Right" << endl;
        return 0;
      }
    }

    if (originalInstruction != "Forward")
    {
      instructions[i] = "Forward";
      if (getsToDestination(x, y, instructions))
      {
        cout << i + 1 << " Forward" << endl;
        return 0;
      }
    }

    instructions[i] = originalInstruction;
  }
}