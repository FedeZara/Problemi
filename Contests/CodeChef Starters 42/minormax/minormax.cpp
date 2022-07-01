// https://www.codechef.com/START42D/problems/MINORMAX
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

        vector<int> arr(N);
        for (int i = 0; i < N; i++)
            cin >> arr[i];

        int maxi = -1000001, mini = 1000001;
        bool possible = true;
        for (int i = 0; i < N; i++)
        {

            if (arr[i] > maxi)
                maxi = arr[i];
            if (arr[i] < mini)
                mini = arr[i];

            if (arr[i] != maxi && arr[i] != mini)
            {
                possible = false;
                break;
            }
        }

        if (possible)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}