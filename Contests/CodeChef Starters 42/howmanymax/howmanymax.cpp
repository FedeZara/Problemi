// https://www.codechef.com/START42D/problems/HOWMANYMAX
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
        cin >> N;
        cin >> s;

        int res = 1;

        for (int i = 1; i < N - 1; i++)
        {
            if (s[i - 1] == '1' && s[i] == '0')
                res++;
        }
        cout << res << "\n";
    }
}