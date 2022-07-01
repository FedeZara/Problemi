// https://www.codechef.com/START42D/problems/MINFLIPS
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int N;
        cin >> N;

        int pos_count = 0;
        for (int i = 0; i < N; i++)
        {
            int v;
            cin >> v;
            if (v == 1)
                pos_count++;
        }
        if (N % 2 == 1)
            cout << -1 << "\n";
        else
            cout << abs(N - 2 * pos_count) / 2 << "\n";
    }
}