// https://www.codechef.com/COOK143D/problems/SEGFAULT
#include <bits/stdc++.h>

using namespace std;

vector<int> bit;

void init(int N)
{
    bit.clear();
    bit.resize(N + 1, 0);
}

void update(int a, int diff)
{
    a++;
    while (a < bit.size())
    {
        bit[a] += diff;
        a += a & (-a);
    }
}

int query(int a)
{
    a++;
    int sum = 0;

    while (a > 0)
    {
        sum += bit[a];
        a -= a & (-a);
    }

    return sum;
}

void updateRange(int a, int b, int val)
{
    update(a, val);
    if (b < bit.size() - 2)
        update(b + 1, -val);
}

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int N;
        cin >> N;

        init(N);

        vector<pair<int, int>> ranges;
        for (int i = 0; i < N; i++)
        {
            int a, b;
            cin >> a >> b;
            a--;
            b--;
            ranges.push_back({a, b});
            updateRange(a, b, 1);
        }

        vector<int> thieves;
        for (int i = 0; i < N; i++)
        {
            if (ranges[i].first > i || ranges[i].second < i)
            {
                updateRange(ranges[i].first, ranges[i].second, -1);
                if (query(i) == N - 1)
                    thieves.push_back(i);
                updateRange(ranges[i].first, ranges[i].second, 1);
            }
        }

        cout << thieves.size() << endl;
        for (int t : thieves)
        {
            cout << t + 1 << endl;
        }
    }
}