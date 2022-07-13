// https://www.codechef.com/START47B/problems/HEIGHTS
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int N;
        set<int> values;
        map<int, int> count;
        cin >> N;

        for (int i = 0; i < N; i++)
        {
            int a;
            cin >> a;

            values.insert(a);

            if (count.find(a) == count.end())
            {
                count[a] = 1;
            }
            else
            {
                count[a]++;
            }
        }

        int res = 0;
        int first_num_alone = -1;
        bool has_more_after = false;
        bool found_more_than_two = false;
        for (int a : values)
        {
            if (first_num_alone != -1)
                has_more_after = true;

            if (count[a] == 1)
            {
                res++;
                if (first_num_alone == -1)
                    first_num_alone = a;
            }
            else if (count[a] > 2)
            {
                found_more_than_two = true;
            }
        }

        if (res == 1 && !has_more_after)
        {
            if (found_more_than_two)
                cout << 1 << "\n";
            else
                cout << 2 << "\n";
        }
        else
        {

            cout << (res + 1) / 2 << "\n";
        }
    }
}