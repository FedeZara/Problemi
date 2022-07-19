// https://www.codechef.com/submit/STRINGXOR
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int N;
        string A, B;
        cin >> N >> A >> B;

        bool A_has_one = A[0] == '1';
        bool alternating = true;
        for (int i = 1; i < N; i++)
        {
            A_has_one = A_has_one || A[i] == '1';
            if (B[i] == B[i - 1])
                alternating = false;
        }

        bool possible;
        if (!A_has_one)
            possible = false;
        else
            possible = !alternating;

        if (A == B)
            possible = true;

        if (possible)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}