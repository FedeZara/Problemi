// https://www.codechef.com/submit/GDSUB
#include <bits/stdc++.h>

#define MOD 1000000007

using namespace std;

vector<long long> counts;
vector<vector<long long>> dp;
vector<int> primes;

long long calc(int num_index, int length)
{
    if (num_index >= primes.size() || length == 0)
        return 1;

    if (dp[num_index][length] == -1)
    {
        dp[num_index][length] = calc(num_index + 1, length);
        if (counts[primes[num_index]] > 0)
            dp[num_index][length] = (dp[num_index][length] + counts[primes[num_index]] * calc(num_index + 1, length - 1)) % MOD;
    }

    return dp[num_index][length];
}

int main()
{
    vector<bool> is_prime(8001, true);
    for (int i = 2; i < 8001; i++)
    {
        if (is_prime[i])
        {
            for (int j = i + i; j < 8001; j += i)
                is_prime[j] = false;
        }
    }

    for (int i = 2; i < is_prime.size(); i++)
    {
        if (is_prime[i])
        {
            primes.push_back(i);
        }
    }

    counts.resize(8001, 0);
    dp.resize(primes.size(), vector<long long>(primes.size() + 1, -1));

    int N, K;
    cin >> N >> K;

    for (int i = 0; i < N; i++)
    {
        int a;
        cin >> a;
        counts[a]++;
    }

    cout << calc(0, min(K, (int)primes.size()));
}