// https://www.codechef.com/submit/PERMXORSUM
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        long long N;
        cin >> N;

        long long res = 0;
        while (N > 1)
        {
            long long k = log2l(N);
            long long N_pow = pow(2, k);
            if (N == 2 * N_pow - 1)
                N--;
            long long diff = N - N_pow;
            res += 2 * (diff + 1) * (2 * N_pow - 1);
            N -= 2 * (diff + 1);
        }
        cout << res << "\n";
    }
}