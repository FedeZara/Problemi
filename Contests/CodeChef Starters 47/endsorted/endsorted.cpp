// https://www.codechef.com/START47B/problems/ENDSORTED
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

        int first_pos = -1, second_pos = -1;
        bool second_before_pos = false;
        for (int i = 0; i < N; i++)
        {
            int a;
            cin >> a;
            if (a == 1)
                first_pos = i;
            else if (a == N)
            {
                second_pos = i;
                if (first_pos == -1)
                    second_before_pos = true;
            }
        }

        int result = first_pos + (N - second_pos - 1);
        if (second_before_pos)
            result--;
        cout << result << "\n";
    }
}