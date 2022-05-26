// https://training.olinfo.it/#/task/ois_police7/statement
#include <bits/stdc++.h>

using namespace std;

int size;
vector<pair<long long, int>> tree;

void init(int N)
{
    size = 1 << int(ceil(log2(N)));

    tree.clear();
    tree.resize(2 * size, {0, -1});
}

void update(int index, long long value)
{
    index += size;
    tree[index] = {value, index - size};

    for (index /= 2; index >= 1; index /= 2)
    {
        tree[index] = max(tree[2 * index], tree[2 * index + 1]);
    }
}

pair<long long, int> query(int a, int b)
{
    a += size;
    b += size;

    pair<long long, int> res = {0, -1};
    while (a <= b)
    {
        if (a % 2 == 1)
            res = max(res, tree[a++]);
        if (b % 2 == 0)
            res = max(res, tree[b--]);
        a /= 2;
        b /= 2;
    }

    return res;
}

void print_tree()
{
    for (int i = 1; i < tree.size(); i++)
    {
        if ((1 << int(log2(i))) == i)
            cout << endl;
        cout << "(" << tree[i].first << " " << tree[i].second << ") ";
    }
    cout << endl;
}

int main()
{
    int N, Q;
    cin >> N >> Q;

    init(N);

    for (int i = 0; i < N; i++)
    {
        int num;
        cin >> num;
        update(i, num);
    }

    // print_tree();

    for (int i = 0; i < Q; i++)
    {
        int p, s;
        cin >> p >> s;

        update(p, s);

        // print_tree();

        long long sum = 0;
        int start = -1;
        while (start < N - 1)
        {
            pair<long long, int> maxi = query(start + 1, N - 1);
            sum += maxi.first;
            start = maxi.second;
        }

        cout << sum << endl;
    }
}