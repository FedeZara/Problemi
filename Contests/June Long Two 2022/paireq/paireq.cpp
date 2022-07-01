// https://www.codechef.com/JUNE222D/problems/PAIREQ
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

        int max = 0;
        map<int, int> count_per_number;

        for (int i = 0; i < N; i++)
        {
            int num;
            cin >> num;
            if (count_per_number.find(num) == count_per_number.end())
                count_per_number[num] = 1;
            else
                count_per_number[num]++;

            if (count_per_number[num] > max)
                max = count_per_number[num];
        }

        cout << N - max << "\n";
    }
}