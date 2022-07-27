// https://www.codechef.com/START49B/problems/GOODINDICES
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int N;
        cin >> N;

        vector<int> count(1001);

        for (int i = 0; i < N; i++)
        {
            int a;
            cin >> a;
            count[a]++;
        }

        int already_equal = 0;
        for (int i = 1; i < 1001; i++)
            if (count[i] > 1)
                already_equal += count[i];

        int maxi = 0;

        for (int diff = 1; diff <= 999; diff++)
        {
            int val = 0;
            vector<bool> set(1001);
            vector<bool> set_mult(1001);
            for (int i = 1; i <= 1000 - diff; i++)
            {
                if (count[i] == 1 && count[i + diff] == 1)
                {
                    if (set_mult[i])
                    {
                        val++;
                        set_mult[i + diff] = true;
                    }
                    else if (!set[i])
                    {
                        val += 2;
                        set[i + diff] = true;
                    }
                }
                else if (count[i] == 1 && count[i + diff] >= 2 && !set[i] && !set_mult[i])
                    val++;
                else if (count[i] >= 2 && count[i + diff] == 1)
                {
                    set_mult[i + diff] = true;
                    val++;
                }
            }

            maxi = max(maxi, val);
        }

        cout << already_equal + maxi << "\n";
    }
}