// https://www.codechef.com/SEP221D/problems/yac
// DOESN'T WORK, BUT DON'T HAVE TIME TO FIND THE PROBLEM
#include <bits/stdc++.h>

#define MOD 1000000007

using namespace std;

vector<long long> pow10(1001);
vector<long long> f(1001);
vector<vector<long long>> f2(1001, vector<long long>(10));
vector<vector<long long>> c(1001, vector<long long>(4000));
vector<vector<vector<long long>>> c2(1001, vector<vector<long long>>(10, vector<long long>(4000, 0)));

long long get_c(int n, int k)
{
    return c[n][k + 3000];
}

void set_c(int n, int k, long long val)
{
    c[n][k + 3000] = val;
}

long long get_c2(int n, int c, int k)
{
    return c2[n][c][k + 3000];
}

void set_c2(int n, int c, int k, long long val)
{
    c2[n][c][k + 3000] = val;
}

void init()
{
    pow10[0] = 1;
    for (int i = 1; i <= 1000; i++)
        pow10[i] = (pow10[i - 1] * 10) % MOD;

    f[1] = 0;
    f[2] = 17;

    for (int k = 1; k <= 9; k++)
        f2[1][k] = 0;

    f2[2][1] = f2[2][3] = f2[2][7] = f2[2][9] = 1;
    f2[2][2] = f2[2][6] = f2[2][4] = f2[2][8] = 2;
    f2[2][5] = 5;

    set_c(1, 0, 4);
    set_c(1, 1, 1);
    set_c(1, -1, 2);
    set_c(1, -2, 1);
    set_c(1, -3, 1);
    set_c2(1, 1, 0, 1);
    set_c2(1, 3, 0, 1);
    set_c2(1, 7, 0, 1);
    set_c2(1, 9, 0, 1);
    set_c2(1, 5, 1, 1);
    set_c2(1, 2, -1, 1);
    set_c2(1, 6, -1, 1);
    set_c2(1, 4, -2, 1);
    set_c2(1, 8, -3, 1);

    for (int n = 2; n <= 1000; n++)
    {
        for (int k = -3 * n; k <= n; k++)
        {
            set_c2(n, 1, k, get_c(n - 1, k));
            set_c2(n, 3, k, get_c(n - 1, k));
            set_c2(n, 7, k, get_c(n - 1, k));
            set_c2(n, 9, k, get_c(n - 1, k));
            set_c2(n, 5, k, get_c(n - 1, k - 1));
            set_c2(n, 2, k, get_c(n - 1, k + 1));
            set_c2(n, 6, k, get_c(n - 1, k + 1));
            set_c2(n, 4, k, get_c(n - 1, k + 2));
            set_c2(n, 8, k, get_c(n - 1, k + 3));

            long long val = 0;
            for (int c = 1; c <= 9; c++)
            {
                val = (val + get_c2(n, c, k)) % MOD;
            }

            set_c(n, k, val);
        }

        if (n > 2)
        {
            long long sum_f2_n_1 = 0;
            for (int i = 1; i <= 9; i++)
            {
                sum_f2_n_1 = (sum_f2_n_1 + f2[n - 1][i]) % MOD;
            }

            for (int i = 1; i <= 9; i++)
            {
                f2[n][i] = (pow10[n - 2] + sum_f2_n_1) % MOD;
            }

            long long sum_c_n_1 = 0;
            for (int i = 1; i <= n - 1; i++)
            {
                sum_c_n_1 = (sum_c_n_1 + get_c(n - 1, i)) % MOD;
            }

            f2[n][2] = f2[n][4] = f2[n][6] = f2[n][8] = (f2[n][2] + sum_c_n_1) % MOD;

            sum_c_n_1 = (sum_c_n_1 + (MOD - get_c(n - 1, 1))) % MOD;
            f2[n][4] = f2[n][8] = (f2[n][4] + sum_c_n_1) % MOD;

            if (n >= 3)
            {
                sum_c_n_1 = (sum_c_n_1 + (MOD - get_c(n - 1, 2))) % MOD;
                f2[n][8] = (f2[n][8] + sum_c_n_1) % MOD;
            }

            sum_c_n_1 = 0;
            for (int i = 1; i <= 3 * (n - 1); i++)
            {
                sum_c_n_1 = (sum_c_n_1 + get_c(n - 1, -i)) % MOD;
            }

            f2[n][5] = (f2[n][5] + sum_c_n_1) % MOD;

            long long sum_f2_n = 0;
            for (int i = 1; i <= 9; i++)
            {
                sum_f2_n = (sum_f2_n + f2[n][i]) % MOD;
            }

            f[n] = (f[n - 1] + sum_f2_n) % MOD;
        }
    }
}

long long calc_res(string num)
{
    long long g = 0, new_g = 0;
    vector<long long> c1(4000, 0), new_c1(4000, 0);

    int initial_d = num[num.length() - 1] - '0';

    if (initial_d == 1)
        c1[0 + 3000]++;
    if (initial_d == 2)
        c1[2999]++;
    if (initial_d == 3)
        c1[3000]++;
    if (initial_d == 4)
        c1[2998]++;
    if (initial_d == 5)
        c1[3001]++;
    if (initial_d == 6)
        c1[2999]++;
    if (initial_d == 7)
        c1[3000]++;
    if (initial_d == 8)
        c1[2997]++;
    if (initial_d == 9)
        c1[3000]++;

    /*cout << "k=0 " << c1[3000] << endl;
    cout << "k=1 " << c1[3001] << endl;
    cout << "k=-1 " << c1[2999] << endl;
    cout << "k=-2 " << c1[2998] << endl;
    cout << "k=-3 " << c1[2997] << endl
         << endl;*/

    for (int d_pos = num.length() - 2; d_pos >= 0; d_pos--)
    {
        int d = num[d_pos] - '0';
        int d_after = num[d_pos + 1] - '0';
        int n = num.length() - d_pos;
        // cout << "n: " << n << endl;

        new_g = (g + f[n - 1]) % MOD;

        // cout << new_g << endl;

        for (int i = 1; i < d; i++)
            new_g = (new_g + f2[n][i]) % MOD;

        // cout << new_g << endl;

        new_g = (new_g + pow10[n - 2]) % MOD;

        // cout << new_g << endl;

        if (d == 2 || d == 4 || d == 6 || d == 8)
        {
            for (int i = 1; i <= n - 1; i++)
            {
                new_g = (new_g + c1[i + 3000]) % MOD;
                for (int j = 1; j < d_after; j++)
                    new_g = (new_g + get_c2(n - 1, j, i)) % MOD;
            }
            // cout << "2-4-6-8: " << new_g << endl;
        }

        if (d == 4 || d == 8)
        {
            for (int i = 2; i <= n - 1; i++)
            {
                new_g = (new_g + c1[i + 3000]) % MOD;
                for (int j = 1; j < d_after; j++)
                    new_g = (new_g + get_c2(n - 1, j, i)) % MOD;
            }
            // cout << "4-8: " << new_g << endl;
        }

        if (d == 8)
        {
            for (int i = 3; i <= n - 1; i++)
            {
                new_g = (new_g + c1[i + 3000]) % MOD;
                for (int j = 1; j < d_after; j++)
                    new_g = (new_g + get_c2(n - 1, j, i)) % MOD;
            }
            // cout << "8: " << new_g << endl;
        }

        if (d == 5)
        {
            for (int i = 1; i <= 3 * (n - 1); i++)
            {
                new_g = (new_g + c1[-i + 3000]) % MOD;
                for (int j = 1; j < d_after; j++)
                    new_g = (new_g + get_c2(n - 1, j, -i)) % MOD;
            }
            // cout << "5: " << new_g << endl;
        }

        g = new_g;

        new_c1.clear();
        new_c1.resize(4000, 0);

        int delta = 0;
        if (d == 2 || d == 6)
            delta = 1;
        else if (d == 5)
            delta = -1;
        else if (d == 4)
            delta = 2;
        else if (d == 8)
            delta = 3;

        // cout << endl;

        for (int k = -(3 * n); k <= n; k++)
        {
            new_c1[k + 3000] = c1[k + 3000 + delta];
            for (int i = 1; i < d_after; i++)
            {
                new_c1[k + 3000] = (new_c1[k + 3000] + get_c2(n - 1, i, k + delta)) % MOD;
                // cout << "k=" << k << " i=" << i << " " << new_c1[k + 3000] << endl;
            }

            // cout << "k=" << k << " " << new_c1[k + 3000] << endl;
        }

        c1 = new_c1;

        /*cout << endl
             << endl
             << endl;*/
    }

    return g;
}

int main()
{
    init();
    string a, b;
    cin >> a >> b;

    // cout << calc_res(b) << endl;

    cout << (calc_res(b) + (MOD - calc_res(a))) % MOD << "\n";
}