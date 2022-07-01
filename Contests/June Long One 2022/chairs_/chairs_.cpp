// https://www.codechef.com/JUNE221D/problems/CHAIRS_
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int x, y;
        cin >> x >> y;
        cout << max(0, x - y) << "\n";
    }
}