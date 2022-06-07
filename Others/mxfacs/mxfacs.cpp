// https://www.codechef.com/submit-v2/MXFACS
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int N;
        cin >> N;

        int result = -1, max = 0;
        for (int i = 2; i * i <= N; i++)
        {
            int times = 0;
            while (N % i == 0)
            {
                times++;
                N /= i;
            }
            if (times > max)
            {
                max = times;
                result = i;
            }
        }

        if (N > 1 && max < 1)
        {
            max = 1;
            result = N;
        }

        cout << result << "\n";
    }
}