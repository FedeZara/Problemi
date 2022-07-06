// https://www.codechef.com/START46C/problems/GRPASSN
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
        for (int i = 0; i < N; i++)
        {
            int p;
            cin >> p;
            times[p]++;
        }

        bool possible = true;

        for (int i = 2; i <= N && possible; i++)
        {
            if (times[i] % i != 0)
                possible = false;
        }

        if (possible)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}