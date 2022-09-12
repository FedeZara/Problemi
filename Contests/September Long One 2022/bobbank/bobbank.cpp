// https://www.codechef.com/SEP221D/problems/BOBBANK
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int W, X, Y, Z;
        cin >> W >> X >> Y >> Z;

        cout << W + (X - Y) * Z << "\n";
    }
}