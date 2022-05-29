// https://www.codechef.com/submit-v2/PIBRO
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int N, K;
        cin >> N >> K;

        string days;
        cin >> days;

        int a = 0, b = N;
        int result = 0;
        while (a <= b)
        {
            int k = (a + b) / 2;

            list<int> zeros;

            bool found = false;

            for (int i = 0; i < N && !found; i++)
            {
                if (days[i] == '0')
                    zeros.push_back(i);

                if (!zeros.empty() && zeros.front() < i - k + 1)
                    zeros.pop_front();

                if (i >= k - 1)
                {
                    if (zeros.empty())
                        found = true;
                    else
                    {
                        int diff = zeros.back() - zeros.front();
                        if (K > diff)
                            found = true;
                    }
                }
            }

            if (found)
            {
                result = max(result, k);
                a = k + 1;
            }
            else
            {
                b = k - 1;
            }
        }

        cout << result << endl;
    }
}