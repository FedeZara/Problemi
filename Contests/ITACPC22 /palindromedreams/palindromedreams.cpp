// https://itacpc22.kattis.com/contests/itacpc22/problems/itacpc22.palindromedreams
#include <bits/stdc++.h>

using namespace std;

vector<int> fun;

int palindromeCountAux(string a, int start, int end, bool includeZero = true)
{
  int res = (a[start] - '0' - (includeZero ? 0 : 1)) * pow(10, (end - start) / 2);
  if (start == end || start == end - 1)
  {
    if (a[start] <= a[end])
      res++;
  }
  else if (start < end)
  {
    if (a[start] > a[end])
      a[end - 1]--;

    res += palindromeCountAux(a, start + 1, end - 1);
  }
  // cout << a << " " << start << " " << end << " " << res << endl;
  return res;
}

int palindromeCount(int a)
{
  string aString = to_string(a);
  return palindromeCountAux(aString, 0, aString.length() - 1, false) + fun[aString.length() - 1];
}

int main()
{
  fun.push_back(0);
  for (int i = 1; i <= 8; i++)
  {
    fun.push_back(fun[i - 1] + 9 * pow(10, (i - 1) / 2));
  }

  int T;
  cin >> T;

  for (int t = 0; t < T; t++)
  {
    int a, b;
    cin >> a >> b;

    int res = palindromeCount(b);
    if (a > 1)
      res -= palindromeCount(a - 1);

    // int res = palindromeCount(a - 1);

    cout << res << endl;
  }
}