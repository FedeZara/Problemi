// https://www.codechef.com/START42D/problems/MODULO3
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int a, b;
        cin >> a >> b;
        a %= 3;
        b %= 3;

        if (a == 0 || b == 0)
            cout << "0\n";
        else if (a == b)
            cout << "1\n";
        else
            cout << "2\n";
    }
}