// https://lightoj.com/problem/explosion

#include <bits/stdc++.h>

#define MAX_N 1000

using namespace std;

struct council_pref
{
    int x, y, z, type;
};

vector<vector<int>> adj;
vector<int> trav;
bool visited[2 * MAX_N];

int negate_val(int i)
{
    return i % 2 == 0 ? i + 1 : i - 1;
}

void add_nodes(int i, int j)
{
    adj[negate_val(i)].push_back(j);
    adj[negate_val(j)].push_back(i);
}

void dfs1(int node)
{
    if (visited[node])
        return;

    visited[node] = true;

    for (int next : adj[node])
    {
        dfs1(next);
    }

    trav.push_back(node);
}

vector<vector<int>> adj_rev;

void reverse_nodes(int N)
{
    for (int i = 0; i < 2 * N; i++)
    {
        for (int next : adj[i])
            adj_rev[next].push_back(i);
    }
}

int nodes_component[2 * MAX_N];
vector<vector<int>> components;

void dfs2(int node, int component)
{
    if (nodes_component[node] != -1)
        return;

    nodes_component[node] = component;
    components[component].push_back(node);

    for (int next : adj_rev[node])
        dfs2(next, component);
}

bool component_visited[2 * MAX_N];
int values[MAX_N];

void components_dfs(int component)
{
    if (component_visited[component])
        return;

    component_visited[component] = true;

    for (int node : components[component])
    {
        for (int next : adj[node])
            components_dfs(nodes_component[next]);
    }

    for (int node : components[component])
    {
        if (values[node / 2] == 0)
            values[node / 2] = node % 2 == 0 ? 1 : -1;
    }
}

bool calc_solution(int N)
{
    for (int i = 0; i < 2 * N; i++)
    {
        dfs1(i);
    }

    reverse_nodes(N);

    for (int i = trav.size() - 1; i >= 0; i--)
    {
        int node = trav[i];
        if (nodes_component[node] == -1)
        {
            components.emplace_back(vector<int>());
            dfs2(node, components.size() - 1);
        }
    }

    bool result = true;
    for (int i = 0; i < N && result; i++)
    {
        if (nodes_component[2 * i] == nodes_component[2 * i + 1])
            result = false;
    }

    if (result)
    {
        for (int component = 0; component < components.size(); component++)
        {
            components_dfs(component);
        }
    }

    return result;
}

void init(int N)
{
    adj.clear();
    adj.resize(2 * N);
    adj_rev.clear();
    adj_rev.resize(2 * N);

    trav.clear();
    memset(visited, 0, sizeof(visited));
    memset(component_visited, 0, sizeof(component_visited));
    memset(values, 0, sizeof(values));

    for (int i = 0; i < 2 * MAX_N; i++)
        nodes_component[i] = -1;

    components.clear();
}

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int N, M, K;

        cin >> N >> M >> K;

        init(N);

        council_pref prefs[K];

        for (int i = 0; i < M; i++)
        {
            int type, x, y;
            cin >> type >> x >> y;

            x--;
            y--;

            switch (type)
            {
            case 1:
                add_nodes(2 * x, 2 * y);
                break;
            case 2:
                add_nodes(2 * x, negate_val(2 * y));
                break;
            case 3:
                add_nodes(negate_val(2 * x), negate_val(2 * y));
                break;
            case 4:
                add_nodes(2 * x, 2 * y);
                add_nodes(negate_val(2 * x), negate_val(2 * y));
                break;
            }
        }

        for (int i = 0; i < K; i++)
        {
            cin >> prefs[i].type >> prefs[i].x >> prefs[i].y >> prefs[i].z;

            prefs[i].x--;
            prefs[i].y--;
            prefs[i].z--;
        }

        vector<vector<int>> original_adj(adj.begin(), adj.end());

        bool found = false;

        bool var_inserted[N];
        vector<int> vars;

        memset(var_inserted, 0, N);

        for (int i = 0; i < K; i++)
        {
            if (!var_inserted[prefs[i].x])
            {
                var_inserted[prefs[i].x] = true;
                vars.push_back(prefs[i].x);
            }
        }

        for (int k = 0; k < (1 << vars.size()) && !found; k++)
        {
            init(N);
            adj.assign(original_adj.begin(), original_adj.end());

            for (int i = 0; i < vars.size(); i++)
            {
                int var = vars[i];

                bool present = (1 << i) & k;

                add_nodes(2 * var + (present ? 0 : 1), 2 * var + (present ? 0 : 1));

                for (int p = 0; p < K; p++)
                {
                    auto pref = prefs[p];

                    if (pref.x != var)
                        continue;

                    if (!present && pref.type == 1)
                    {
                        add_nodes(2 * pref.y, 2 * pref.z);
                    }
                    else if (present && pref.type == 2)
                    {
                        add_nodes(2 * pref.y + 1, 2 * pref.z + 1);
                    }
                }
            }

            found = calc_solution(N);
        }

        cout << "Case " << (t + 1) << ": ";
        if (!found)
            cout << "Impossible." << endl;
        else
        {
            vector<int> members;

            for (int i = 0; i < N; i++)
            {
                if (values[i] == 1)
                    members.push_back(i);
            }

            cout << "Possible " << members.size();
            for (int member : members)
                cout << " " << (member + 1);

            cout << "." << endl;
        }
    }
}