// https://www.codechef.com/START46C/problems/M1ENROL
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int X, Y;
        cin >> X >> Y;

        if (X >= Y)
            cout << "0\n";
        else
            cout << Y - X << "\n";
    }
}