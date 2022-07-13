// https://www.codechef.com/START47B/problems/COPYPUSH
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

        bool possible = true;
        while (s.size() > 0 && possible)
        {
            if (s.size() % 2 == 0)
            {
                string s1 = s.substr(0, s.size() / 2), s2 = s.substr(s.size() / 2, s.size());
                if (s1 != s2)
                    possible = false;
                s = s1;
            }
            else
            {
                s = s.substr(0, s.size() - 1);
            }
        }

        if (possible)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}