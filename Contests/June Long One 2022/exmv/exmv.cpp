// https://www.codechef.com/JUNE221D/problems/EXMV
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        long long x, n;
        cin >> x >> n;
        cout << (x - 1) * (2 * n - x) << "\n";
    }
}