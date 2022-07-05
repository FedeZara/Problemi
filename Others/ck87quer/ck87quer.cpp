// https://www.codechef.com/submit/CK87QUER
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        long long Y;
        cin >> Y;

        long long res = 0;
        for (long long b = 1; b <= 700 && Y - b > 0; b++)
        {
            res += (long long)sqrt(Y - b);
        }
        cout << res << endl;
    }
}