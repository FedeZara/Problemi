// https://www.codechef.com/submit/CARRAY
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        // read the input
        long long N, k, b;
        cin >> N >> k >> b;

        vector<long long> A(N);
        for (int i = 0; i < N; i++)
            cin >> A[i];

        // sort array A
        sort(A.begin(), A.end());

        // array max_s which stores the maximum subsequence ending at index i
        vector<int> max_s(N);

        max_s[0] = 1;

        // for each element e in A at index i
        // using binary search, find index j that represents the maximum value of max_s in the subarray (0, i-1)
        // with A[i] >= k*A[j] + b

        for (int i = 1; i < N; i++)
        {
            int s = 0, e = i - 1;

            max_s[i] = 1;

            while (s <= e)
            {
                int t = (s + e) / 2;
                if (A[i] >= A[t] * k + b)
                {
                    s = t + 1;
                    max_s[i] = max(max_s[i], max_s[t] + 1);
                }
                else
                {
                    e = t - 1;
                }
            }
        }
        cout << max_s[N - 1] << "\n";
    }
}