// https://www.codechef.com/submit/XORFOLD
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

        bool result = false;
        for (int i = 0; i < N; i++)
        {
            string s;
            cin >> s;
            for (int j = 0; j < M; j++)
            {
                if (s[j] == '1')
                    result = !result;
            }
        }

        if (result)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}