// https://www.codechef.com/SEP221D/problems/SPEEDTEST
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        double A, X, B, Y;

        cin >> A >> X >> B >> Y;
        double a_speed = A / X;
        double b_speed = B / Y;

        if (a_speed == b_speed)
            cout << "Equal\n";
        else if (a_speed > b_speed)
            cout << "Alice\n";
        else
            cout << "Bob\n";
    }
}