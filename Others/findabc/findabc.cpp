// https://www.codechef.com/submit/FINDABC
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

        vector<int> f(N + 1);
        for (int i = 0; i <= N; i++)
        {
            cin >> f[i];
        }

        for (int A = 0; A <= N; A++)
        {
            int B = 0, C = 0;
            bool possible = true;
            for (int k = 1; k <= N && possible; k *= 2)
            {
                int diff = (f[0] - A) - (f[k] - (A ^ k));
                if (diff == 0)
                {
                    if (B >= C)
                        C += k;
                    else
                        B += k;
                }
                else if (diff == 2 * k)
                {
                    B += k;
                    C += k;
                }
                else if (diff != -2 * k)
                {
                    possible = false;
                }

                if (B > N || C > N)
                    possible = false;
            }

            if (possible)
            {
                cout << A << " " << B << " " << C << "\n";
                break;
            }
        }
    }
}