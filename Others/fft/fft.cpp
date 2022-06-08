// https://www.codechef.com/submit-v2/FFT
#include <bits/stdc++.h>

#define MAX_N 1000001
#define MOD 998244353

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
    vector<long long> fact(1, 1);
    vector<long long> fact_inv(1, 1);
    for (int i = 1; i < MAX_N; i++)
    {
        fact.push_back((fact[i - 1] * (long long)i) % MOD);
        fact_inv.push_back(inverse(fact[i]));
    }

    int T;
    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int N;
        cin >> N;
        set<long long> cycles_found;
        vector<long long> cycles_count(MAX_N, 0);

        for (int i = 0; i < N; i++)
        {
            long long a;
            cin >> a;
            cycles_found.insert(a);
            cycles_count[a]++;
        }

        long long result = 1;
        for (long long cycle : cycles_found)
        {
            // cout << cycle << " " << cycles_count[cycle] << endl;
            if (cycles_count[cycle] % cycle != 0)
            {
                result = 0;
                break;
            }

            result = (result * (long long)fact[cycle - 1]) % MOD;

            if (cycle != 1)
            {
                int k = cycles_count[cycle] / cycle;
                for (int i = cycle * 2; i <= cycles_count[cycle]; i += cycle)
                {
                    result = (result * fact[i]) % MOD;
                    result = (result * fact_inv[cycle]) % MOD;
                    result = (result * fact_inv[i - cycle]) % MOD;
                }
                result = (result * fact_inv[k]) % MOD;
            }
        }

        cout << result << endl;
    }
}