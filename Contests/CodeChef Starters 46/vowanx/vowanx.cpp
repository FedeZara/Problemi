// https://www.codechef.com/START46C/problems/VOWANX
#include <bits/stdc++.h>

using namespace std;

bool is_vowel(char c)
{
    switch (c)
    {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
        return true;
    }
    return false;
}

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int N;
        string s;

        cin >> N >> s;

        string curr;
        vector<string> pieces;
        for (int i = 0; i < N; i++)
        {
            if (is_vowel(s[i]) && curr.size() > 0)
            {
                pieces.push_back(curr);
                curr = "";
            }

            curr += s[i];
        }

        string res = "";

        for (int i = pieces.size() - 1; i >= 0; i -= 2)
        {
            reverse(pieces[i].begin(), pieces[i].end());
            res += pieces[i];
        }

        for (int i = pieces.size() % 2 == 1 ? 1 : 0; i < pieces.size(); i += 2)
        {
            res += pieces[i];
        }

        res += curr;

        cout << res << "\n";
    }
}