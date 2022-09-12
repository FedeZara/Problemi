// https://www.codechef.com/SEP221D/problems/DISTNUMS
#include <bits/stdc++.h>

#define MAX_K 100000
#define MOD 1000000007

using namespace std;

long long gcd_extended(long long a, long long b, long long *x, long long *y)
{
    if (a == 0)
    {
        *x = 0, *y = 1;
        return b;
    }

    long long x1, y1;
    long long gcd = gcd_extended(b % a, a, &x1, &y1);

    *x = y1 - (b / a) * x1;
    *y = x1;

    return gcd;
}

long long inverse(long long n)
{
    long long x, y;
    gcd_extended(n, MOD, &x, &y);
    return (x % MOD + MOD) % MOD;
}

int main()
{
    int T;

    cin >> T;

    vector<long long> memo(MAX_K + 1);
    memo[0] = 1;

    for (int i = 1; i <= MAX_K; i++)
    {
        memo[i] = (2 * memo[i - 1]) % (MOD - 1);
    }

    for (int t = 0; t < T; t++)
    {
        long long N, K;
        cin >> N >> K;

        long long original_N = N;

        vector<long long> divs;
        map<long long, long long> divs_count;
        for (long long i = 2; i * i <= N; i++)
        {
            if (N % i == 0)
            {
                divs.push_back(i);
                divs_count[i] = 0;
                while (N % i == 0)
                {
                    N /= i;
                    divs_count[i]++;
                }
            }
        }

        if (N != 1)
        {
            divs.push_back(N);
            divs_count[N] = 1;
        }

        long long res = original_N;
        for (long long div : divs)
        {

            long long exp = ((memo[K] - 1) * divs_count[div] + 1) % (MOD - 1);

            long long powers_needed = (long long)ceil(log2((double)exp));
            vector<long long> powers(powers_needed + 1);
            powers[0] = div;

            for (int i = 1; i <= powers_needed; i++)
            {
                powers[i] = (powers[i - 1] * powers[i - 1]) % MOD;
            }

            long long pow_result = 1;
            for (int i = 0; i <= powers_needed; i++)
            {
                if (exp & (1 << i))
                {
                    pow_result = (pow_result * powers[i]) % MOD;
                }
            }
            long long factor = ((pow_result - 1) * inverse(div - 1)) % MOD;
            res = (res * factor) % MOD;
        }
        cout << res << "\n";
    }
}