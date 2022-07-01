// https://www.codechef.com/JUNE221D/problems/DIVBYI
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

        int low = 1, high = N;
        vector<int> perm;
        for (int i = 0; i < N; i++)
        {
            if (i % 2 == 0)
                perm.push_back(high--);
            else
                perm.push_back(low++);
        }

        for (int i = N - 1; i >= 0; i--)
            cout << perm[i] << " ";
        cout << "\n";
    }
}