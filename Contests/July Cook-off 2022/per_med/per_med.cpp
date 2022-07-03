// https://www.codechef.com/COOK143D/problems/PER_MED
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

        int a = 1, b = N;
        while (a < b)
        {
            cout << b << " " << a << " ";
            a++;
            b--;
        }

        if (a == b)
            cout << a;
        cout << endl;
    }
}