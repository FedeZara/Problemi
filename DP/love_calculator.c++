// https://lightoj.com/problem/love-calculator

#include <bits/stdc++.h>

using namespace std;

string a, b;

bool calculated[31][31];
pair<int, long long> values[31][31];

pair<int, long long> calc(int aIndex, int bIndex)
{
    if (!calculated[aIndex][bIndex])
    {
        if (aIndex >= a.length())
            values[aIndex][bIndex] = {b.length() - bIndex, 1};
        else if (bIndex >= b.length())
            values[aIndex][bIndex] = {a.length() - aIndex, 1};
        else if (a[aIndex] == b[bIndex])
        {
            auto next = calc(aIndex + 1, bIndex + 1);
            values[aIndex][bIndex] = {next.first + 1, next.second};
        }
        else
        {
            auto nextA = calc(aIndex + 1, bIndex);
            auto nextB = calc(aIndex, bIndex + 1);
            if (nextA.first == nextB.first)
                values[aIndex][bIndex] = {nextA.first + 1, nextA.second + nextB.second};
            else if (nextA.first < nextB.first)
                values[aIndex][bIndex] = {nextA.first + 1, nextA.second};
            else
                values[aIndex][bIndex] = {nextB.first + 1, nextB.second};
        }
        calculated[aIndex][bIndex] = true;
    }

    return values[aIndex][bIndex];
}

int main()
{
    int T;
    cin >> T;
    for (int t = 0; t < T; t++)
    {
        cin >> a;
        cin >> b;

        for (int i = 0; i < 31; i++)
        {
            for (int j = 0; j < 31; j++)
            {
                calculated[i][j] = false;
            }
        }

        auto result = calc(0, 0);

        cout << "Case " << (t + 1) << ": " << result.first << " " << result.second << endl;
    }
}