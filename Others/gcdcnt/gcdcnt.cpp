// https://www.codechef.com/submit-v2/GCDCNT
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define MAX 100000

using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

vector<int> prs[MAX + 1];
vector<int> divs[MAX + 1];

vector<int> primes(int n)
{
    int n_copy = n;
    if (prs[n].empty())
    {

        for (int i = 2; i * i <= n; i++)
        {
            if (n % i == 0)
            {
                prs[n_copy].push_back(i);
                while (n % i == 0)
                    n /= i;
            }
        }

        if (n != 1)
            prs[n_copy].push_back(n);
    }

    return prs[n_copy];
}

vector<int> divisors(int n)
{
    if (divs[n].empty())
    {
        // cout << n << " divisors: ";

        vector<int> p = primes(n);

        for (long long j = 1; j < (1 << p.size()); j++)
        {
            int divisor = 1;
            for (int k = 0; k < p.size(); k++)
            {
                if ((j & (1 << k)) != 0)
                {
                    divisor *= p[k];
                }
            }

            divs[n].push_back(divisor);
        }

        /*for (int i = 0; i < d.size(); i++)
        {
            cout << d[i] << " ";
        }
        cout << endl;*/
    }

    return divs[n];
}

int main()
{
    int N;
    cin >> N;
    vector<ordered_set> sets(MAX + 1);

    vector<int> a;

    for (int i = 0; i < N; i++)
    {
        int n;
        cin >> n;

        a.push_back(n);

        vector<int> d = divisors(n);
        for (int j = 0; j < d.size(); j++)
            sets[d[j]].insert(i);
    }

    /*for (int i = 2; i < 15; i++)
    {
        cout << i << ": ";
        vector<int> cop(sets[i].begin(), sets[i].end());
        for (int j = 0; j < cop.size(); j++)
        {
            cout << cop[j] << " ";
        }
        cout << endl;
    }*/

    int Q;
    cin >> Q;

    for (int q = 0; q < Q; q++)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            int x, y;
            cin >> x >> y;
            x--;

            vector<int> old_d = divisors(a[x]);
            for (int i = 0; i < old_d.size(); i++)
            {
                sets[old_d[i]].erase(x);
            }

            a[x] = y;
            vector<int> new_d = divisors(a[x]);
            for (int i = 0; i < new_d.size(); i++)
            {
                sets[new_d[i]].insert(x);
            }
        }
        else
        {
            int l, r, g;
            cin >> l >> r >> g;
            l--;
            r--;
            // cout << "Query" << endl;
            vector<int> p = primes(g);
            int sum = 0;

            for (long long j = 1; j < (1 << p.size()); j++)
            {
                int bits = 0, divisor = 1;
                for (int k = 0; k < p.size(); k++)
                {
                    if ((j & (1 << k)) != 0)
                    {
                        bits++;
                        divisor *= p[k];
                    }
                }

                int r_count = sets[divisor].order_of_key(r + 1);
                int l_count = 0;
                if (l > 0)
                    l_count = sets[divisor].order_of_key(l);
                int count = r_count - l_count;

                /*cout << "Divisor " << divisor << endl;
                cout << "Bits " << bits << endl;
                cout << "r_count " << r_count << endl;
                cout << "l_count " << l_count << endl;*/

                if (bits % 2 == 0)
                    sum -= count;
                else
                    sum += count;
            }

            cout << r - l - sum + 1 << endl;
        }
    }
}