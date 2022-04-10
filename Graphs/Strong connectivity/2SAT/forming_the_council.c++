// https://lightoj.com/problem/forming-the-council

#include <bits/stdc++.h>

#define MAX_M 8000

using namespace std;

vector<int> adj[2 * MAX_M];
vector<int> trav;
bool visited[2 * MAX_M];

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

vector<int> adj_rev[2 * MAX_M];

void reverse_nodes()
{
    for (int i = 0; i < 2 * MAX_M; i++)
    {
        for (int next : adj[i])
            adj_rev[next].push_back(i);
    }
}

int nodes_component[2 * MAX_M];
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

bool component_visited[2 * MAX_M];
int values[MAX_M];

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

void init()
{
    for (int i = 0; i < 2 * MAX_M; i++)
    {
        adj[i].clear();
        adj_rev[i].clear();
    }

    trav.clear();
    memset(visited, 0, sizeof(visited));
    memset(component_visited, 0, sizeof(component_visited));
    memset(values, 0, sizeof(values));

    for (int i = 0; i < 2 * MAX_M; i++)
        nodes_component[i] = -1;

    components.clear();
}

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int N, M;
        cin >> N >> M;

        init();

        for (int i = 0; i < N; i++)
        {
            char a_sign, b_sign;
            int a, b;
            scanf("\n%c%d %c%d", &a_sign, &a, &b_sign, &b);

            a--;
            b--;

            if (a_sign == '+')
            {
                if (b_sign == '+')
                {
                    adj[a * 2 + 1].push_back(b * 2);
                    adj[b * 2 + 1].push_back(a * 2);
                }
                else
                {
                    adj[a * 2 + 1].push_back(b * 2 + 1);
                    adj[b * 2].push_back(a * 2);
                }
            }
            else
            {
                if (b_sign == '+')
                {
                    adj[a * 2].push_back(b * 2);
                    adj[b * 2 + 1].push_back(a * 2 + 1);
                }
                else
                {
                    adj[a * 2].push_back(b * 2 + 1);
                    adj[b * 2].push_back(a * 2 + 1);
                }
            }
        }

        for (int i = 0; i < 2 * M; i++)
        {
            dfs1(i);
        }

        reverse_nodes();

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
        for (int i = 0; i < M && result; i++)
        {
            if (nodes_component[2 * i] == nodes_component[2 * i + 1])
                result = false;
        }

        cout << "Case " << t + 1 << ": " << (result ? "Yes" : "No") << endl;

        if (result)
        {
            for (int component = 0; component < components.size(); component++)
            {
                components_dfs(component);
            }

            vector<int> members;

            for (int i = 0; i < M; i++)
            {
                if (values[i] == 1)
                    members.push_back(i);
            }

            cout << members.size() << " ";

            for (int member : members)
                cout << (member + 1) << " ";

            cout << endl;
        }
    }
}