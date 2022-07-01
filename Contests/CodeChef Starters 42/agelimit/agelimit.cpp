// https://www.codechef.com/START42D/problems/AGELIMIT
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int x, y, a;
        cin >> x >> y >> a;
        cout << (a >= x && a < y ? "YES" : "NO") << "\n";
    }
}