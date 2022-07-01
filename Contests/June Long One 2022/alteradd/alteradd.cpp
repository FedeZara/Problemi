// https://www.codechef.com/JUNE221D/problems/ALTERADD
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int a, b;
        cin >> a >> b;
        int remainder = (b - a) % 3;
        cout << ((remainder == 0 || remainder == 1) ? "YES" : "NO") << "\n";
    }
}