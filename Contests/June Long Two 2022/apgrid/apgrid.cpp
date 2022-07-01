// https://www.codechef.com/JUNE222D/problems/APGRID
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int N, M;
        cin >> N >> M;

        bool swapped = false;
        if (N > M)
        {
            swap(N, M);
            swapped = true;
        }

        vector<vector<int>> matrix(N, vector<int>(M));

        int curr = 1;
        int diff = 1;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                matrix[i][j] = curr + j * diff;
            }
            diff++;
            curr += N + 1;
        }

        if (swapped)
        {
            for (int i = 0; i < M; i++)
            {
                for (int j = 0; j < N; j++)
                    cout << matrix[j][i] << " ";
                cout << endl;
            }
        }
        else
        {
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < M; j++)
                    cout << matrix[i][j] << " ";
                cout << endl;
            }
        }
    }
}