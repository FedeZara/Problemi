// https://lightoj.com/problem/rooks

#include <bits/stdc++.h>

using namespace std;

long long values[31][31][30 * 30 + 1];
bool calculated[31][31][30 * 30 + 1];

long long ways(long long rows, long long columns, long long rooks)
{
    if (calculated[rows][columns][rooks])
        return values[rows][columns][rooks];

    if (rooks == 0)
    {
        values[rows][columns][rooks] = 1;
    }
    else if (rooks == 1)
    {
        values[rows][columns][rooks] = rows * columns;
    }
    else if (columns < rooks)
    {
        values[rows][columns][rooks] = 0;
    }
    else
    {
        values[rows][columns][rooks] = rows * ways(rows - 1, columns - 1, rooks - 1) + ways(rows, columns - 1, rooks);
    }

    calculated[rows][columns][rooks] = true;
    return values[rows][columns][rooks];
}

int main()
{
    int T;
    cin >> T;
    for (int t = 0; t < T; t++)
    {
        long long N, K;
        cin >> N;
        cin >> K;

        cout << "Case " << (t + 1) << ": " << ways(N, N, K) << endl;
    }
}