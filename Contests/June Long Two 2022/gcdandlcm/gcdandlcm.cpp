// https://www.codechef.com/submit/GCDANDLCM
#include <bits/stdc++.h>

using namespace std;

long long gcd(long long a, long long b)
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
        long long N;
        cin >> N;

        int count = 0;
        for (long long i = 1; i * i < N; i++)
        {
            if (N % (i * i) == 0)
            {
                long long rem = N / (i * i);
                for (long long j = 1; j * j <= rem; j++)
                {
                    if (rem % (j * j + 1) == 0)
                    {
                        long long rem2 = rem / (j * j + 1) - 1;
                        if (rem2 >= 1)
                        {
                            long long rem3 = sqrt(rem2);
                            if (rem3 * rem3 == rem2 && gcd(j, rem3) == 1)
                            {
                                count++;
                            }
                        }
                    }
                }
            }
        }
        cout << count << "\n";
    }
}