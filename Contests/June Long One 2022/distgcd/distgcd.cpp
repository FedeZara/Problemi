// https://www.codechef.com/JUNE221D/problems/DISTGCD
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int a, b;
        cin >> a >> b;

        int diff = abs(b - a);
        int result = 1;

        for (int i = 2; i * i <= diff; i++)
        {
            int count = 0;
            while (diff % i == 0)
            {
                diff /= i;
                count++;
            }
            result *= (count + 1);
        }

        if (diff != 1)
            result *= 2;

        cout << result << "\n";
    }
}