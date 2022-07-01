// https://www.codechef.com/JUNE221D/problems/RED0
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;
    cin >> T;

    for (int t = 0; t < T; t++)
    {
        long long x, y;
        cin >> x >> y;

        if (x == y)
            cout << x << "\n";
        else if (x == 0 || y == 0)
            cout << -1 << "\n";
        else
        {
            long long mini = min(x, y), maxi = max(x, y);
            long long result = 0;
            while (2 * mini < maxi)
            {
                result++;
                mini *= 2;
            }

            result = result + maxi + 1;

            cout << result << "\n";
        }
    }
}