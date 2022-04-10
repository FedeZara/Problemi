// https://lightoj.com/problem/marriage-ceremonies

#include <bits/stdc++.h>

using namespace std;

int N;
vector<vector<int>> values;

vector<int> memo;
vector<bool> calculated;

int calc(int pickedRows)
{
    int step = __builtin_popcount(pickedRows);
    if (step == N)
        return 0;

    if (!calculated[pickedRows])
    {
        int max = INT_MIN;
        for (int i = 0; i < N; i++)
        {
            if (!(pickedRows & (1 << i)))
            {
                int val = calc(pickedRows | (1 << i)) + values[step][i];
                if (val > max)
                    max = val;
            }
        }
        memo[pickedRows] = max;
        calculated[pickedRows] = true;
    }

    return memo[pickedRows];
}

int main()
{
    int T;
    cin >> T;
    for (int t = 0; t < T; t++)
    {
        cin >> N;

        values.resize(N);
        for (int i = 0; i < N; i++)
        {
            values[i].resize(N);
            for (int j = 0; j < N; j++)
                cin >> values[i][j];
        }

        calculated.clear();
        memo.clear();
        calculated.resize(1 << N);
        memo.resize(1 << N);

        cout << "Case " << (t + 1) << ": " << calc(0) << endl;
    }
}