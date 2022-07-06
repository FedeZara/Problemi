// https://www.codechef.com/START46C/problems/ARRSORT
#include <bits/stdc++.h>

using namespace std;

int gcd(int a, int b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int N;
        cin >> N;

        int result = 0;
        int p;
        for (int i = 0; i < N; i++)
        {
            cin >> p;

            result = gcd(result, abs(p - i - 1));
        }

        cout << result << endl;
    }
}