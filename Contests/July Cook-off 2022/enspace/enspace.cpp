// https://www.codechef.com/COOK143D/problems/ENSPACE
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int N, X, Y;
        cin >> N >> X >> Y;

        if (X + 2 * Y <= N)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}