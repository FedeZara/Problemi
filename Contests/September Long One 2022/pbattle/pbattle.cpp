// https://www.codechef.com/SEP221D/problems/PBATTLE
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int N;
        cin >> N;

        vector<pair<int, int>> values(N);
        for (int i = 0; i < N; i++)
        {
            cin >> values[i].first;
        }
        for (int i = 0; i < N; i++)
        {
            cin >> values[i].second;
        }

        sort(values.begin(), values.end(), less<pair<int, int>>());

        int max_strength = 0, count = 0;

        ordered_set aux;

        for (int i = 0; i < N; i++)
        {
            int strength = N - i - 1;
            int pos = aux.order_of_key(values[i].second);
            strength += pos;

            aux.insert(values[i].second);

            if (strength == max_strength)
                count++;
            else
            {
                count = 1;
                max_strength = strength;
            }
        }

        cout << count << "\n";
    }
}