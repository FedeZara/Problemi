// https://www.codechef.com/START49B/problems/SPLSTR
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int N, K;
        string s;
        cin >> N >> K >> s;

        int diff = 0;
        for (int i = 0; i < N; i++)
        {
            if (s[i] == '1')
                diff++;
            else
                diff--;
        }

        diff = abs(diff);

        cout << (int)ceil((double)diff / (double)K) << "\n";
    }
}