// https://itacpc22.kattis.com/contests/wdqnr2/problems/goldbach2
#include <bits/stdc++.h>

using namespace std;

int main()
{
  vector<bool> isPrime(32001, true);
  for (int i = 2; i <= 32000; i++)
  {
    if (isPrime[i])
    {
      for (int j = 2 * i; j <= 32000; j += i)
        isPrime[j] = false;
    }
  }

  int T;

  cin >> T;

  for (int t = 0; t < T; t++)
  {
    int n;
    cin >> n;

    vector<int> sols;

    for (int i = 2; i <= n / 2; i++)
    {
      if (isPrime[i] && isPrime[n - i])
        sols.push_back(i);
    }

    cout << n << " has " << sols.size() << " representation(s)" << endl;
    for (int i = 0; i < sols.size(); i++)
    {
      cout << sols[i] << "+" << n - sols[i] << endl;
    }

    cout << "\n";
  }
}