// https://lightoj.com/problem/digit-dancing

#include <bits/stdc++.h>

using namespace std;

int fac[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320};

int get_node_id(string node)
{
    int val = 0;
    for (int i = 0; i < 8; i++)
    {
        int count = 0;
        for (int j = 0; j < i; j++)
            if (node.at(j) > node.at(i))
                count++;
        val += count * fac[i];
    }
    return val;
}

int main()
{
    int T;

    cin >> T;

    bool is_prime[16];
    for (int i = 0; i < 16; i++)
    {
        is_prime[i] = false;
    }

    is_prime[2] = true;
    is_prime[3] = true;
    is_prime[5] = true;
    is_prime[7] = true;
    is_prime[11] = true;
    is_prime[13] = true;

    for (int t = 0; t < T; t++)
    {
        string numbers;
        bool is_female[8];

        for (int i = 0; i < 8; i++)
        {
            int n;
            cin >> n;
            if (n < 0)
            {
                n *= -1;
                is_female[n - 1] = true;
            }
            else
            {
                is_female[n - 1] = false;
            }
            numbers.push_back((char)n + '0');
        }

        string goal = "12345678";

        vector<bool> added(400000, false);
        vector<int> dist(400000, -1);

        queue<pair<string, int>> q;
        q.push({numbers, 0});

        dist[get_node_id(numbers)] = 0;
        added[get_node_id(numbers)] = true;

        while (!q.empty())
        {
            auto e = q.front();
            q.pop();

            string node = e.first;
            int distance = e.second;

            if (node == goal)
                break;

            for (int i = 0; i < 8; i++)
            {
                int val = node.at(i) - '0';
                string base = node.substr(0, i);
                if (i != 7)
                    base += node.substr(i + 1);

                for (int j = 0; j < 7; j++)
                {
                    int val2 = base.at(j) - '0';

                    if ((is_female[val - 1] != is_female[val2 - 1]) && is_prime[val + val2])
                    {
                        string left = base, right = base;
                        left.insert(left.begin() + j, node.at(i));

                        int left_id = get_node_id(left);
                        if (!added[left_id])
                        {
                            added[left_id] = true;
                            dist[left_id] = distance + 1;
                            q.push({left, dist[left_id]});
                        }

                        if (j == 6)
                            right.push_back(node.at(i));
                        else
                            right.insert(right.begin() + j + 1, node.at(i));

                        int right_id = get_node_id(right);
                        if (!added[right_id])
                        {
                            added[right_id] = true;
                            dist[right_id] = distance + 1;
                            q.push({right, dist[right_id]});
                        }
                    }
                }
            }
        }

        cout << "Case " << t + 1 << ": " << dist[get_node_id(goal)] << endl;
    }
}