// https://lightoj.com/problem/donation

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> qe;

int main()
{
    int T;
    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int N;
        cin >> N;

        int weight_sum = 0;
        int matrix[N][N];

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                cin >> matrix[i][j];
                weight_sum += matrix[i][j];
            }
        }

        priority_queue<qe, vector<qe>, greater<qe>> pq;
        vector<bool> processed(N, false);
        int processed_count = 1;

        for (int i = 0; i < N; i++)
        {
            if (matrix[0][i] > 0)
                pq.push({matrix[0][i], i});
            if (i != 0 && matrix[i][0] > 0)
                pq.push({matrix[i][0], i});
        }

        processed[0] = true;

        int total_sum = 0;

        while (!pq.empty())
        {
            qe e = pq.top();
            pq.pop();

            int weight = e.first, node = e.second;

            if (processed[node])
                continue;

            processed[node] = true;
            processed_count++;

            total_sum += weight;

            for (int i = 0; i < N; i++)
            {
                if (matrix[node][i] > 0)
                    pq.push({matrix[node][i], i});
                if (i != node && matrix[i][node] > 0)
                    pq.push({matrix[i][node], i});
            }
        }

        cout << "Case " << t + 1 << ": " << (processed_count < N ? -1 : (weight_sum - total_sum)) << endl;
    }
}