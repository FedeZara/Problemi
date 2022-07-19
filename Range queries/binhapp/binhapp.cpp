// https://www.codechef.com/submit/BINHAPP
#include <bits/stdc++.h>

using namespace std;

struct max_table_el
{
    int max_1, max_2, max_1_index, max_2_index;
};

max_table_el find_max(max_table_el e1, max_table_el e2)
{
    priority_queue<pair<int, int>> pq;
    pq.push({e1.max_1, e1.max_1_index});
    pq.push({e1.max_2, e1.max_2_index});
    pq.push({e2.max_1, e2.max_1_index});
    pq.push({e2.max_2, e2.max_2_index});

    max_table_el e;
    e.max_1 = pq.top().first;
    e.max_1_index = pq.top().second;
    while (pq.top().second == e.max_1_index)
        pq.pop();

    e.max_2 = pq.top().first;
    e.max_2_index = pq.top().second;
    return e;
}

void calc_max_table(const vector<int> &array, vector<vector<max_table_el>> &max_table)
{
    max_table.resize(((int)log2(array.size())) + 1);

    max_table[0].resize(array.size());

    for (int i = 0; i < array.size(); i++)
    {
        max_table[0][i].max_1 = array[i];
        max_table[0][i].max_1_index = i;
        max_table[0][i].max_2 = 0;
        max_table[0][i].max_2_index = -1;
    }

    for (int i = 1; i < max_table.size(); i++)
    {
        int range_length = pow(2, i);
        max_table[i].resize(array.size() - range_length + 1);
        for (int j = 0; j < array.size() - range_length + 1; j++)
        {
            max_table[i][j] = find_max(max_table[i - 1][j], max_table[i - 1][j + range_length / 2]);
        }
    }
}

max_table_el query_max_table(int L, int R, vector<vector<max_table_el>> &max_table)
{
    int row_index = (int)log2(R - L + 1);
    int k = pow(2, row_index);

    return find_max(max_table[row_index][L], max_table[row_index][R - k + 1]);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N, Q;
    cin >> N >> Q;

    vector<int> whole(N), prefix_diff(N), suffix_diff(N), substring(N);

    for (int i = 0; i < N; i++)
    {
        int l;
        string s;
        cin >> l >> s;

        int prefix = 0;
        whole[i] = 0;
        int val = 0;

        for (char c : s)
        {
            if (c == '0')
            {
                whole[i]--;
                val = max(val - 1, 0);
            }
            else
            {
                whole[i]++;
                val++;
                if (prefix < whole[i])
                    prefix = whole[i];
                if (substring[i] < val)
                    substring[i] = val;
            }
        }

        int suffix = 0;
        val = 0;
        for (int j = s.size() - 1; j >= 0; j--)
        {
            if (s[j] == '0')
                val--;
            else
            {
                val++;
                if (suffix < val)
                    suffix = val;
            }
        }

        prefix = max(prefix, 0);
        suffix = max(suffix, 0);
        whole[i] = max(whole[i], 0);

        prefix_diff[i] = prefix - whole[i];
        suffix_diff[i] = suffix - whole[i];
    }

    /*for (int i = 0; i < N; i++)
        cout << whole[i] << " " << prefix_diff[i] << " " << suffix_diff[i] << " " << substring[i] << endl;*/

    vector<int> whole_ps;
    whole_ps.push_back(whole[0]);
    for (int i = 1; i < whole.size(); i++)
    {
        whole_ps.push_back(whole_ps[i - 1] + whole[i]);
    }

    vector<vector<max_table_el>> prefix_diff_mt, suffix_diff_mt, substring_mt;

    calc_max_table(prefix_diff, prefix_diff_mt);
    calc_max_table(suffix_diff, suffix_diff_mt);
    calc_max_table(substring, substring_mt);

    for (int i = 0; i < Q; i++)
    {
        int L, R;
        cin >> L >> R;

        L--;
        R--;

        auto el = query_max_table(L, R, substring_mt);

        if (R > L)
        {
            int res = whole_ps[R];
            if (L >= 1)
                res -= whole_ps[L - 1];

            auto max_prefix_el = query_max_table(L, R, prefix_diff_mt), max_suffix_el = query_max_table(L, R, suffix_diff_mt);

            if (max_prefix_el.max_1_index != max_suffix_el.max_1_index)
            {
                res += max_prefix_el.max_1;
                res += max_suffix_el.max_1;
            }
            else
            {
                res += max(max_prefix_el.max_1 + max_suffix_el.max_2, max_prefix_el.max_2 + max_suffix_el.max_1);
            }

            cout << max(res, el.max_1) << endl;
        }
        else
        {
            cout << el.max_1 << endl;
        }
    }
}