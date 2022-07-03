// https://www.codechef.com/COOK143D/problems/TEA
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int X, Y, Z;
        cin >> X >> Y >> Z;

        cout << ceil((double)X / Y) * Z << endl;
    }
}