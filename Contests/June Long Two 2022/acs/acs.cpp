// https://www.codechef.com/JUNE222D/problems/ACS
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int P;
        cin >> P;
        int res = P % 100;
        res += P / 100;

        if (res > 10)
            cout << -1 << "\n";
        else
            cout << res << "\n";
    }
}