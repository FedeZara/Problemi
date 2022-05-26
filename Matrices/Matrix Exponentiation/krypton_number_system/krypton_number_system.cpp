// https://lightoj.com/problem/krypton-number-system
#include <bits/stdc++.h>

using namespace std;

typedef vector<vector<unsigned>> matrix;

matrix identity(int n)
{
    matrix m(n, vector<unsigned>(n));
    for (int i = 0; i < n; i++)
        m[i][i] = 1;
    return m;
}

matrix matrix_multiply(matrix m1, matrix m2)
{
    matrix res(m1.size(), vector<unsigned>(m2[0].size()));

    for (int i = 0; i < m1.size(); i++)
    {
        for (int j = 0; j < m2[0].size(); j++)
        {
            for (int k = 0; k < m2.size(); k++)
            {
                res[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }

    return res;
}

int get_max_diff(int base) { return (base - 1) * (base - 1); }

int get_m_dim(int base) { return base * get_max_diff(base); }

vector<matrix> ms(7);
vector<vector<matrix>> precalculated_powers(7, vector<matrix>(35));

void init()
{
    for (int base = 2; base <= 6; base++)
    {
        int max_diff = get_max_diff(base);
        int m_dim = get_m_dim(base);

        matrix m(m_dim, vector<unsigned>(m_dim));

        for (int i = 0; i < base; i++)
        {
            for (int diff = 1; diff <= max_diff; diff++)
            {
                for (int j = 0; j < base; j++)
                {
                    if (pow(i - j, 2) == diff)
                        m[(diff - 1) * base + j][i] = 1;
                }
            }
        }

        for (int i = 0; i < m_dim - base; i++)
        {
            m[i][i + base] = 1;
        }

        precalculated_powers[base][0] = identity(m_dim);
        precalculated_powers[base][1] = ms[base] = m;

        for (int i = 2; i < 35; i++)
        {
            precalculated_powers[base][i] = matrix_multiply(precalculated_powers[base][i - 1], precalculated_powers[base][i - 1]);
        }
    }
}

matrix matrix_power(int base, int power)
{
    matrix res = identity(get_m_dim(base));

    int counter = 1;

    while (power > 0)
    {
        if (power % 2 == 1)
            res = matrix_multiply(res, precalculated_powers[base][counter]);

        counter++;

        power /= 2;
    }

    return res;
}

int main()
{
    int T;
    cin >> T;

    init();

    for (int t = 0; t < T; t++)
    {
        int base, goal;

        cin >> base >> goal;

        int max_diff = get_max_diff(base);
        int m_dim = get_m_dim(base);

        matrix start(1, vector<unsigned>(m_dim));

        for (int i = 0; i < base; i++)
        {
            start[0][(max_diff - 1) * base + i] = 1;
        }

        for (int i = 1; i < max_diff; i++)
        {
            for (int j = 0; j < base; j++)
            {
                for (int k = 0; k < base; k++)
                {
                    int diff = pow(j - k, 2);
                    if (j != k && diff <= i)
                    {
                        start[0][(max_diff - i - 1) * base + j] += start[0][(max_diff - i + diff - 1) * base + k];
                    }
                }
            }
        }

        unsigned sum = 0;
        if (goal - max_diff >= 0)
        {
            matrix res = matrix_multiply(start, matrix_power(base, goal - max_diff + 1));

            for (int i = 1; i < base; i++)
            {
                sum += res[0][i];
            }
        }
        else
        {
            for (int i = 1; i < base; i++)
            {
                sum += start[0][(max_diff - goal - 1) * base + i];
            }
        }

        cout << "Case " << t + 1 << ": " << sum << endl;
    }
}