// https://www.codechef.com/submit/TAAPLUSB
#include <bits/stdc++.h>

#define MAX_N 100001

using namespace std;

vector<double> e1(MAX_N), e2(MAX_N), e(MAX_N);

void calc()
{
    e1[1] = 0;
    e2[1] = 1;
    e[1] = 0.45;
    for (int i = 2; i < MAX_N; i++)
    {
        e1[i] = e[i - 1];
        e2[i] = 0.45 * (1 + e1[i - 1]) + 0.55 * (1 + e2[i - 1]);
        e[i] = 0.55 * e1[i] + 0.45 * e2[i];
    }
}

int main()
{
    cout.precision(15);

    int T;

    cin >> T;

    calc();

    for (int t = 0; t < T; t++)
    {
        int N;
        cin >> N;
        cout << e[N] << endl;
    }
}