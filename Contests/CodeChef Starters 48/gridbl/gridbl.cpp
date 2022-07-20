// https://www.codechef.com/START48B/problems/GRIDBL
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int N, M;
        cin >> N >> M;

        if (N % 2 == 0 && M % 2 == 0)
            cout << 0 << "\n";
        else if (N % 2 != 0 && M % 2 == 0)
        {
            cout << M << "\n";
        }
        else if (N % 2 == 0 && M % 2 != 0)
        {
            cout << N << "\n";
        }
        else
        {
            cout << N + M - 1 << "\n";
        }
    }
}