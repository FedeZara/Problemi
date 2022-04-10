// https://lightoj.com/problem/points-in-rectangle

#include <bits/stdc++.h>

using namespace std;

bool has_point[1001][1001];
int bit[1002][1002];

void update(int x, int y)
{
    if (has_point[x][y])
        return;

    has_point[x][y] = true;

    x = x + 1;
    y = y + 1;

    for (; x < 1002; x += x & -x)
    {
        for (int y1 = y; y1 < 1002; y1 += y1 & -y1)
        {
            bit[x][y1]++;
        }
    }
}

int query(int x, int y)
{
    int sum = 0;

    x = x + 1;
    y = y + 1;

    for (; x >= 1; x -= x & -x)
    {
        for (int y1 = y; y1 >= 1; y1 -= y1 & -y1)
        {
            sum += bit[x][y1];
        }
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
        int Q;
        cin >> Q;

        for (int i = 0; i < 1001; i++)
        {
            for (int j = 0; j < 1001; j++)
            {
                has_point[i][j] = false;
                bit[i + 1][j + 1] = 0;
            }
        }

        for (int q = 0; q < Q; q++)
        {
            int type;
            cin >> type;
            if (type == 0)
            {
                int x, y;
                cin >> x >> y;
                update(x, y);
            }
            else
            {
                int x1, y1, x2, y2;
                cin >> x1 >> y1 >> x2 >> y2;

                int sum = query(x2, y2) - query(x2, y1 - 1) - query(x1 - 1, y2) + query(x1 - 1, y1 - 1);
                cout << sum << endl;
            }
        }
    }
}