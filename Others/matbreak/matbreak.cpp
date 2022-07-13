// https://www.codechef.com/submit/MATBREAK
#include <bits/stdc++.h>

#define MOD 1000000007
#define MAX_N 100000

using namespace std;

vector<long long> m(MAX_N), k(MAX_N);

void precalc()
{
    m[0] = 1;
    m[1] = 3;
    k[0] = 1;
    k[1] = 3;

    for (long long i = 2; i < MAX_N; i++)
    {
        k[i] = ((((2 * i - 1) * k[i - 1]) % MOD) * k[i - 1]) % MOD;
        m[i] = (((2 * i - 1) * ((2 * i - 3) * k[i - 2]) % MOD) % MOD * k[i - 2]) % MOD;
    }
}

int main()
{
    int T;

    cin >> T;

    precalc();

    for (int t = 0; t < T; t++)
    {
        int N;
        long long a;
        cin >> N >> a;

        long long res = 0;

        for (int i = 0; i < N; i++)
        {
            res = (res + (m[i] * a) % MOD) % MOD;
            a = (a * a) % MOD;

            cout << a << endl;
        }

        cout << res << "\n";
    }
}