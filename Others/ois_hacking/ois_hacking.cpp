// https://training.olinfo.it/#/task/ois_hacking
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N;
    cin >> N;

    vector<vector<int>> req(2 * N);

    int counter = 0;
    bool correct = true;
    for (int i = 0; i < N; i++)
    {
        int num;
        cin >> num;

        if (req[num + N].empty())
        {
            if (num > 0)
            {
                correct = false;
                break;
            }
            else
            {
                counter++;
                if (num < 0)
                {
                    auto it = lower_bound(req[num + 2 + N].begin(), req[num + 2 + N].end(), num, greater<int>());
                    req[num + 2 + N].insert(it, num);
                }
            }
        }
        else
        {
            int num2 = req[num + N].back();
            req[num + N].pop_back();

            if (-num2 > num)
            {
                auto it = lower_bound(req[num + 2 + N].begin(), req[num + 2 + N].end(), num2, greater<int>());
                req[num + 2 + N].insert(it, num2);
            }
        }
    }

    for (int i = 0; i < req.size(); i++)
    {
        if (!req[i].empty())
            correct = false;
    }

    if (!correct)
        cout << "0";
    else
        cout << counter;
}