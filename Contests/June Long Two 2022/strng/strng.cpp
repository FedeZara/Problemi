// https://www.codechef.com/JUNE222D/problems/STRNG
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

        vector<int> values(N);

        for (int i = 0; i < N; i++)
            cin >> values[i];

        vector<int> prefix_gcd(N, values[0]);
        vector<int> suffix_gcd(N, values[N - 1]);

        for (int i = 1; i < N; i++)
        {
            prefix_gcd[i] = gcd(prefix_gcd[i - 1], values[i]);
            suffix_gcd[N - i - 1] = gcd(suffix_gcd[N - i], values[N - i - 1]);
        }

        int count = 0;
        for (int i = 0; i < N; i++)
        {
            int gcd_without_el;
            if (i == 0)
                gcd_without_el = suffix_gcd[1];
            else if (i == N - 1)
                gcd_without_el = prefix_gcd[N - 2];
            else
                gcd_without_el = gcd(prefix_gcd[i - 1], suffix_gcd[i + 1]);

            if (gcd_without_el > 1)
                count++;
        }

        cout << count << endl;
    }
}