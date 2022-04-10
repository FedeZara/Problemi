// https://lightoj.com/problem/binary-simulation

#include <bits/stdc++.h>

using namespace std;

void update(int index, bool value, vector<bool> &bit)
{
    while (index < bit.size())
    {
        bit[index] = bit[index] ^ value;
        index += index & -index;
    }
}

bool query(int index, vector<bool> &bit)
{
    bool value = false;
    while (index >= 1)
    {
        value ^= bit[index];
        index -= index & -index;
    }
    return value;
}

int main()
{
    int T;
    cin >> T;
    for (int t = 0; t < T; t++)
    {
        cout << "Case " << (t + 1) << ":" << endl;

        string number;
        cin >> number;

        vector<bool> differenceArray(number.length());
        differenceArray[0] = number[0] == '1';

        for (int i = 1; i < number.length(); i++)
        {
            differenceArray[i] = (number[i - 1] == '1') ^ (number[i] == '1');
        }

        vector<bool> bit(differenceArray.size() + 1);
        for (int i = 0; i < differenceArray.size(); i++)
        {
            update(i + 1, differenceArray[i], bit);
        }

        int Q;
        cin >> Q;
        for (int q = 0; q < Q; q++)
        {
            char I;
            cin >> I;
            if (I == 'I')
            {
                int start, end;
                cin >> start;
                cin >> end;
                update(start, true, bit);
                update(end + 1, true, bit);
            }
            else
            {
                int index;
                cin >> index;
                bool value = query(index, bit);

                cout << (value ? 1 : 0) << endl;
            }
        }
    }
}