// https://www.codechef.com/COOK143D/problems/XORPERM
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

        if (N == 3)
            cout << -1 << endl;
        else if (N == 6)
            cout << "6 1 2 4 3 5" << endl;
        else
        {
            for (int i = 1; i <= N; i++)
            {
                if (i == 3)
                    cout << 4 << " ";
                else if (i == 4)
                    cout << 3 << " ";
                else if (i == 6)
                    cout << 7 << " ";
                else if (i == 7)
                    cout << 6 << " ";
                else
                    cout << i << " ";
            }
            cout << endl;
        }
    }
}