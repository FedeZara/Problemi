// https://lightoj.com/problem/all-possible-inc-subseq

#include <bits/stdc++.h>

using namespace std;

vector<int> bit;

int query(int index)
{
    int sum = 0;
    while (index >= 1)
    {
        sum += bit[index];
        sum %= 1000000007;
        index -= index & -index;
    }
    return sum;
}

void update(int index, int value)
{
    while (index < bit.size())
    {
        bit[index] += value;
        bit[index] %= 1000000007;
        index += index & -index;
    }
}

int main()
{
    int T;
    cin >> T;
    for (int t = 0; t < T; t++)
    {
        int N;
        cin >> N;

        vector<int> array(N);

        for (int i = 0; i < N; i++)
            cin >> array[i];

        bit.clear();
        bit.resize(N + 1);

        vector<int> sorted_array(array.begin(), array.end());

        sort(sorted_array.begin(), sorted_array.end());

        map<int, int> number_to_index;

        int index = 0;
        for (int i = 0; i < sorted_array.size(); i++)
        {
            if (number_to_index.count(sorted_array[i]) == 0)
            {
                number_to_index[sorted_array[i]] = index;
                index++;
            }
        }

        int answer = 0;
        for (int i = 0; i < array.size(); i++)
        {
            int result = query(number_to_index[array[i]]) + 1;
            answer = (answer + result) % 1000000007;
            update(number_to_index[array[i]] + 1, result);
        }

        cout << "Case " << (t + 1) << ": " << answer << endl;
    }
}