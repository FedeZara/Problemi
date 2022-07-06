// https://www.codechef.com/START46C/problems/SRTARR
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int N;
        string s;
        cin >> N >> s;

        int count = 0;
        for (int i = 0; i < N - 1; i++)
        {
            if (s[i] == '1' && s[i + 1] == '0')
                count++;
        }
        cout << count << "\n";
    }
}