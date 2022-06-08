// https://www.codechef.com/submit-v2/BDGFT
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        string s;
        cin >> s;

        int result = 0;

        vector<int> ones_prefix, zeros_prefix;
        int ones_count = 0, zeros_count = 0;
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == '1')
                ones_count++;
            else
                zeros_count++;

            ones_prefix.push_back(ones_count);
            zeros_prefix.push_back(zeros_count);
        }

        for (int c = 1; c * c + c <= s.size(); c++)
        {
            int length = c * c + c;
            int zeros = zeros_prefix[length - 1], ones = ones_prefix[length - 1];
            if (ones == c && zeros == c * c)
                result++;
            for (int i = length; i < s.size(); i++)
            {
                if (s[i] == '0')
                    zeros++;
                else
                    ones++;

                if (s[i - length] == '0')
                    zeros--;
                else
                    ones--;

                if (ones == c && zeros == c * c)
                    result++;
            }
        }

        cout << result << "\n";
    }
}