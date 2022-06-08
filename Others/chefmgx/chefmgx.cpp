// https://www.codechef.com/submit-v2/CHEFMGX
#include <bits/stdc++.h>

#define MAX 10000000

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    vector<bool> is_prime(MAX + 1, true);
    vector<int> primes_before(MAX + 1);

    int count = 0;
    for (int i = 2; i <= MAX; i++)
    {
        if (is_prime[i])
        {
            count++;
            for (int j = i * 2; j <= MAX; j += i)
                is_prime[j] = false;
        }

        primes_before[i] = count;
    }

    is_prime[2] = false;

    int T;
    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int X, Y;
        cin >> X >> Y;

        int result = Y - X - primes_before[Y] + primes_before[X + 1];

        cout << result << endl;
    }
}