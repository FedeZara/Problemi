// https://www.codechef.com/START49B/problems/VALIDMIN
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        vector<int> val(3);
        cin >> val[0] >> val[1] >> val[2];

        sort(val.begin(), val.end());

        if (val[0] == val[1] && val[2] >= val[1])
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}