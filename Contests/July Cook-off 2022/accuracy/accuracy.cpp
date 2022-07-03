// https://www.codechef.com/COOK143D/problems/ACCURACY
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int X;
        cin >> X;

        for (int i = 0; i <= 100; i++)
        {
            if ((300 - X - 4 * i) % 3 == 0)
            {
                int a = (300 - X - 4 * i) / 3;
                if (a + i <= 100)
                {
                    cout << i << endl;
                    break;
                }
            }
        }
    }
}