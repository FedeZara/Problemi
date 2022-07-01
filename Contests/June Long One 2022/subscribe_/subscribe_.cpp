// https://www.codechef.com/JUNE221D/problems/SUBSCRIBE_
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int n, x;
        cin >> n >> x;
        cout << (int)ceil((double)n / 6.0) * x << "\n";
    }
}