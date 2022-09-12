// https://www.codechef.com/submit/NILXOR
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int N, X;
        cin >> N >> X;

        long long equal, less;

        if (!(N & 1) && !(X & 1))
        {
            equal = 0;
            less = 2;
        }
        else if (!(N & 1) && (X & 1))
        {
            equal = 0;
            less = 1;
        }
        else if ((N & 1) && !(X & 1))
        {
            equal = 1;
            less = 2;
        }
        else
        {
            equal = 0;
            less = 1;
        }

        for (int i = 1; i <= 30; i++)
        {
            int set = 1 << i;
            if (!(N & set) && !(X & set))
                less *= 2;
            else if ((N & set) && !(X & set))
            {
                equal += less;
                less *= 2;
            }
        }
        cout << equal << "\n";
    }
}