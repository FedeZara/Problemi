// https://www.codechef.com/SEP221D/problems/CWIREFRAME
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int N, M, X;
        cin >> N >> M >> X;

        cout << 2 * (N + M) * X << "\n";
    }
}