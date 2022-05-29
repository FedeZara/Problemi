// https://www.codechef.com/submit-v2/ANDSUBAR
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

        int low = floor(log2(N)), high = ceil(log2(N));

        if (N == 1)
            cout << 1 << endl;
        else
        {
            int result = 1 << (low - 1);
            if (N - result * 2 >= result)
                result += N - 3 * result + 1;

            cout << result << endl;
        }
    }
}