// https://www.codechef.com/submit-v2/SECPASS
#include <bits/stdc++.h>

using namespace std;

int find_times(string word, string prefix)
{
    int times = 0;
    size_t pos = 0;
    do
    {
        pos = word.find(prefix, pos);
        if (pos != string::npos)
        {
            times++;
            pos++;
        }
    } while (pos != string::npos && pos < word.size());
    return times;
}

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int N;
        cin >> N;
        string word;
        cin >> word;
        int times_goal = find_times(word, word.substr(0, 1)), max_length = 1;

        int a = 1, b = N;

        while (a <= b)
        {
            int k = (a + b) / 2;

            string prefix = word.substr(0, k);
            int times = find_times(word, prefix);
            /*cout << "Prefix: " << prefix << endl;
            cout << times << endl;*/

            if (times == times_goal && k >= max_length)
            {
                max_length = k;
                a = k + 1;
            }
            else
            {
                b = k - 1;
            }
        }

        cout << word.substr(0, max_length) << "\n";
    }
}