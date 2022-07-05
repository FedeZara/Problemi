// https://www.codechef.com/submit/EQUALMEX
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

        vector<int> times(N + 1);
        for (int i = 0; i < 2 * N; i++)
        {
            int a;
            cin >> a;
            times[a]++;
        }

        bool possible = true;
        for (int i = 0; i <= N; i++)
        {
            if (times[i] == 0)
                break;
            else if (times[i] == 1)
            {
                possible = false;
                break;
            }
        }

        if (possible)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}