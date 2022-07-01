// https://www.codechef.com/JUNE222D/problems/DNASTRAND
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

        string res = "";
        for (int i = 0; i < N; i++)
        {
            if (s[i] == 'A')
                res += 'T';
            if (s[i] == 'T')
                res += 'A';
            if (s[i] == 'G')
                res += 'C';
            if (s[i] == 'C')
                res += 'G';
        }

        cout << res << endl;
    }
}