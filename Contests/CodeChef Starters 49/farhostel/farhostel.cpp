// https://www.codechef.com/START49B/problems/FARHOSTEL
#include <bits/stdc++.h>

using namespace std;

vector<vector<long long>> a;
vector<vector<long long>> b;
vector<vector<long long>> a_ps;
vector<vector<long long>> b_ps;

vector<vector<long long>> dp;

void init(int N, int M)
{
    a.clear();
    b.clear();
    a_ps.clear();
    b_ps.clear();
    dp.clear();
    a.resize(N, vector<long long>(M));
    b.resize(N, vector<long long>(M));
    a_ps.resize(N, vector<long long>(M));
    b_ps.resize(N, vector<long long>(M));
    dp.resize(N, vector<long long>(M, -1));
}

long long calc(int x, int y)
{
    if (x == -1 || y == -1)
        return 0;

    if (dp[x][y] == -1)
    {
        dp[x][y] = max(calc(x, y - 1) + b_ps[x][y], calc(x - 1, y) + a_ps[x][y]);
    }

    return dp[x][y];
}

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int N, M;
        cin >> N >> M;

        init(N, M);

        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                cin >> a[i][j];

        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                cin >> b[i][j];

        for (int i = 0; i < N; i++)
        {
            a_ps[i][0] = a[i][0];
            for (int j = 1; j < M; j++)
                a_ps[i][j] = a_ps[i][j - 1] + a[i][j];
        }

        for (int j = 0; j < M; j++)
        {
            b_ps[0][j] = b[0][j];
            for (int i = 1; i < N; i++)
                b_ps[i][j] = b_ps[i - 1][j] + b[i][j];
        }

        cout << calc(N - 1, M - 1) << "\n";
    }
}