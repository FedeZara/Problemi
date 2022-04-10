// https://lightoj.com/problem/curious-robin-hood

#include <bits/stdc++.h>

using namespace std;

vector<int> bit;

void update(int index, int value)
{
    while (index < bit.size())
    {
        bit[index] += value;
        index += index & -index;
    }
}

int query(int index)
{
    int sum = 0;
    while (index >= 1)
    {
        sum += bit[index];
        index -= index & -index;
    }
    return sum;
}

int main()
{
    int T;
    cin >> T;
    for (int t = 0; t < T; t++)
    {
        cout << "Case " << (t + 1) << ":" << endl;
        int N, Q;
        cin >> N;
        cin >> Q;

        bit.clear();
        bit.resize(N + 1);

        vector<int> array(N);

        for (int i = 0; i < N; i++)
        {
            cin >> array[i];
            update(i + 1, array[i]);
        }

        for (int q = 0; q < Q; q++)
        {
            int type;
            cin >> type;
            if (type == 1)
            {
                int i;
                cin >> i;
                cout << array[i] << endl;
                update(i + 1, -array[i]);
                array[i] = 0;
            }
            else if (type == 2)
            {
                int i, v;
                cin >> i;
                cin >> v;
                update(i + 1, v);
                array[i] += v;
            }
            else
            {
                int i, j;
                cin >> i;
                cin >> j;
                cout << query(j + 1) - query(i) << endl;
            }
        }
    }
}