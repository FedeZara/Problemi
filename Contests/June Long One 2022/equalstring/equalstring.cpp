// https://www.codechef.com/JUNE221D/problems/EQUALSTRING
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int N;
        string a, b;
        cin >> N >> a >> b;

        int result = 0;
        vector<bool> included(26, false);
        for (int i = 0; i < N; i++)
        {
            if (a[i] != b[i] && !included[b[i] - 'a'])
            {
                included[b[i] - 'a'] = true;
                result++;
            }
        }

        cout << result << "\n";
    }
}