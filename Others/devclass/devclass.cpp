// https://www.codechef.com/submit-v2/DEVCLASS
// NOTES: THIS SOLUTION IS NOT FULLY CORRECT
// CASE WHERE TYPE == 2 DOESN'T WORK
#include <bits/stdc++.h>

using namespace std;

int min_moves(string s, int type, char first)
{
    queue<int> q1, q2;
    int moves = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (i % 2 == 0 && s[i] != first)
        {
            if (q2.empty())
                q1.push(i);
            else
            {
                int pos = q2.front();
                q2.pop();
                moves += pow(abs(i - pos), type);
            }
        }
        else if (i % 2 == 1 && s[i] == first)
        {
            if (q1.empty())
                q2.push(i);
            else
            {
                int pos = q1.front();
                q1.pop();
                moves += pow(abs(i - pos), type);
            }
        }
    }
    return moves;
}

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int type;
        string s;
        cin >> type >> s;

        int b_count = 0;
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == 'B')
                b_count++;
        }

        int result = -1;
        if (s.size() % 2 == 0 && b_count == s.size() / 2)
        {
            result = min(min_moves(s, type, 'B'), min_moves(s, type, 'G'));
        }
        else if (s.size() % 2 == 1)
        {
            if (b_count - s.size() / 2 == 0)
                result = min_moves(s, type, 'G');
            else if (b_count - s.size() / 2 == 1)
                result = min_moves(s, type, 'B');
        }

        cout << result << "\n";
    }
}