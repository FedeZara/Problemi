// https://www.codechef.com/submit/STACKS
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

        vector<int> arr;

        for (int i = 0; i < N; i++)
        {
            int a;
            cin >> a;

            auto it = upper_bound(arr.begin(), arr.end(), a);
            if (it == arr.end())
            {
                arr.push_back(a);
            }
            else
            {
                arr[it - arr.begin()] = a;
            }
        }

        cout << arr.size() << " ";
        for (int i = 0; i < arr.size(); i++)
            cout << arr[i] << " ";

        cout << endl;
    }
}