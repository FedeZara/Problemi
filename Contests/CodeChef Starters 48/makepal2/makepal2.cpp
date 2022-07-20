// https://www.codechef.com/START48B/problems/MAKEPAL2
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int N;
        string s;
        cin >> N >> s;

        int ones_count = 0;
        for (int i = 0; i < N; i++)
        {
            if (s[i] == '1')
                ones_count++;
        }

        if (ones_count <= N / 2)
        {
            for (int i = 0; i < N - ones_count; i++)
                cout << '0';
        }
        else
        {
            for (int i = 0; i < ones_count; i++)
                cout << '1';
        }

        cout << "\n";
    }
}