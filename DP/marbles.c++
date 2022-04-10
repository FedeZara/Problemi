// https://lightoj.com/problem/marbles

#include <bits/stdc++.h>

using namespace std;

bool calculated[501][501];
double values[501][501];

double calc(int r, int b)
{
    if (!calculated[r][b])
    {
        if (r == 0)
        {
            values[r][b] = 1.;
        }
        else if (b < 2)
        {
            values[r][b] = 0.;
        }
        else
        {
            double res1 = calc(r - 1, b - 1);
            double res2 = calc(r, b - 2);

            values[r][b] = (double(r) * res1 + double(b) * res2) / double(r + b);
        }
        calculated[r][b] = true;
    }

    return values[r][b];
}

int main()
{
    int T;
    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int R, B;
        cin >> R;
        cin >> B;

        cout << "Case " << (t + 1) << ": " << calc(R, B) << endl;
    }
}