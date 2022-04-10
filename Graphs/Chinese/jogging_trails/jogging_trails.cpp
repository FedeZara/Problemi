// https://lightoj.com/problem/jogging-trails

#include <bits/stdc++.h>

using namespace std;

#define set(x, n) (x ^ (1 << n))
#define check(x, n) (x & (1 << n))

vector<vector<int>> matrix;

int N;
vector<long long> values;

long long chinese(int bit)
{
    if (bit == 0)
        return 0;

    if (values[bit] != -1)
        return values[bit];

    int first_node;

    for (first_node = 0; first_node < N; first_node++)
    {
        if (check(bit, first_node))
            break;
    }

    long long mini = INT_MAX;
    for (int second_node = first_node + 1; second_node < N; second_node++)
    {
        if (check(bit, first_node) && check(bit, second_node))
        {
            int new_bit = bit;
            new_bit = set(new_bit, first_node);
            new_bit = set(new_bit, second_node);

            mini = min(mini, matrix[first_node][second_node] + chinese(new_bit));
        }
    }

    values[bit] = mini;
    return mini;
}

int main()
{
    int T;
    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int M;
        cin >> N >> M;

        matrix.clear();
        matrix.resize(N, vector<int>(N));

        vector<int> degree(N, 0);
        values.clear();
        values.resize(1 << N, -1);

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
                matrix[i][j] = i == j ? 0 : INT_MAX;
        }

        int weight_sum = 0;
        for (int i = 0; i < M; i++)
        {
            int a, b, w;
            cin >> a >> b >> w;

            a--;
            b--;
            matrix[a][b] = min(matrix[a][b], w);
            matrix[b][a] = min(matrix[b][a], w);
            degree[a]++;
            degree[b]++;
            weight_sum += w;
        }

        for (int k = 0; k < N; k++)
        {
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    if (matrix[i][k] != INT_MAX && matrix[k][j] != INT_MAX)
                        matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
                }
            }
        }

        int bit = 0;

        for (int i = 0; i < N; i++)
        {
            if (degree[i] % 2 != 0)
                bit = set(bit, i);
        }

        long long result = chinese(bit) + weight_sum;

        cout << "Case " << (t + 1) << ": " << result << endl;
    }
}