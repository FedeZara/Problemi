// https://www.codechef.com/START42D/problems/EQUALDIST
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
        cout << ((a + b) % 2 == 0 ? "YES" : "NO") << "\n";
    }
}