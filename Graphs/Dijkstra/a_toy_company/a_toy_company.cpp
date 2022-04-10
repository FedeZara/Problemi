// https://lightoj.com/problem/a-toy-company

#include <bits/stdc++.h>

#define N 26 * 26 * 26

using namespace std;

typedef pair<int, int> qe;

int string_to_node(string s)
{
    return (s[0] - 'a') * 26 * 26 + (s[1] - 'a') * 26 + (s[2] - 'a');
}

string node_to_string(int node)
{
    char c3 = node % 26 + 'a';
    node /= 26;
    char c2 = node % 26 + 'a';
    node /= 26;
    char c1 = node + 'a';

    string s = "";

    s += c1;
    s += c2;
    s += c3;

    return s;
}

int main()
{
    int T;
    cin >> T;

    for (int t = 0; t < T; t++)
    {
        string start, end;

        cin >> start >> end;

        int start_node = string_to_node(start), end_node = string_to_node(end);

        int M;

        cin >> M;

        vector<bool> forbidden(N, false);

        for (int i = 0; i < M; i++)
        {
            string s1, s2, s3;
            cin >> s1 >> s2 >> s3;

            for (char c1 : s1)
            {
                for (char c2 : s2)
                {
                    for (char c3 : s3)
                    {
                        string s = "";
                        s += c1;
                        s += c2;
                        s += c3;
                        forbidden[string_to_node(s)] = true;
                    }
                }
            }
        }

        if (forbidden[start_node] || forbidden[end_node])
            cout << "Case " << t + 1 << ": -1" << endl;
        else
        {
            vector<bool> added(N, false);
            vector<int> dist(N, INT_MAX);
            priority_queue<qe, vector<qe>, greater<qe>> pq;

            dist[start_node] = 0;
            pq.push({0, start_node});

            while (!pq.empty())
            {
                qe e = pq.top();
                pq.pop();

                int node = e.second, distance = e.first;
                string node_string = node_to_string(node);

                if (node == end_node)
                    break;

                for (int i = 0; i < 3; i++)
                {
                    for (int d = -1; d <= 1; d++)
                    {
                        if (d == 0)
                            continue;

                        string next_string = "" + node_string;

                        int val = (next_string[i] - 'a' + d) % 26;
                        if (val == -1)
                            val = 25;

                        next_string[i] = val + 'a';

                        int next = string_to_node(next_string);
                        if (!forbidden[next] && !added[next] && dist[next] > dist[node] + 1)
                        {
                            added[next] = true;
                            dist[next] = dist[node] + 1;
                            pq.push({dist[next], next});
                        }
                    }
                }
            }

            cout << "Case " << t + 1 << ": " << (dist[end_node] == INT_MAX ? -1 : dist[end_node]) << endl;
        }
    }
}