// https://lightoj.com/problem/ghosts
#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> point;

int point_to_node_id(point p, int N)
{
    return p.second * N + p.first;
}

point node_id_to_point(int node_id, int N)
{
    return {node_id % N, node_id / N};
}

int main()
{
    int T;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int N;
        cin >> N;

        char matrix[N][N];

        for (int y = 0; y < N; y++)
        {
            string line;
            cin >> line;
            for (int x = 0; x < N; x++)
                matrix[y][x] = line[x];
        }

        vector<point> ghosts;
        vector<point> humans;

        vector<vector<int>> matrix_adj(N * N);

        // calculate matrix_adj based on matrix
        for (int y = 0; y < N; y++)
        {
            for (int x = 0; x < N; x++)
            {

                if (matrix[y][x] == 'G')
                    ghosts.push_back({x, y});
                else if (matrix[y][x] == 'H')
                    humans.push_back({x, y});

                if (matrix[y][x] != '#')
                {
                    int node_id = point_to_node_id({x, y}, N);
                    if (y > 0 && matrix[y - 1][x] != '#')
                        matrix_adj[node_id].push_back(point_to_node_id({x, y - 1}, N));
                    if (y < N - 1 && matrix[y + 1][x] != '#')
                        matrix_adj[node_id].push_back(point_to_node_id({x, y + 1}, N));
                    if (x > 0 && matrix[y][x - 1] != '#')
                        matrix_adj[node_id].push_back(point_to_node_id({x - 1, y}, N));
                    if (x < N - 1 && matrix[y][x + 1] != '#')
                        matrix_adj[node_id].push_back(point_to_node_id({x + 1, y}, N));
                }
            }
        }

        int bg_nodes_count = ghosts.size() + humans.size() + 2;

        int source = bg_nodes_count - 2;
        int sink = bg_nodes_count - 1;

        vector<vector<int>> bg_adj(bg_nodes_count);
        vector<vector<bool>> usable(bg_nodes_count, vector<bool>(bg_nodes_count, false));
        vector<vector<int>> costs(bg_nodes_count, vector<int>(bg_nodes_count, 0));

        for (int i = 0; i < ghosts.size(); i++)
        {
            bg_adj[source].push_back(i);
            bg_adj[i].push_back(source);
            usable[source][i] = true;
        }

        for (int i = 0; i < humans.size(); i++)
        {
            int human = i + ghosts.size();
            bg_adj[human].push_back(sink);
            bg_adj[sink].push_back(human);
            usable[human][sink] = true;
        }

        set<int> all_costs_set;

        // for each ghost, calculate the distance to all humans
        for (int i = 0; i < ghosts.size(); i++)
        {
            point ghost = ghosts[i];
            queue<int> q;
            vector<int> dist(N * N, INT_MAX);
            int ghost_node_id = point_to_node_id(ghost, N);
            q.push(ghost_node_id);
            dist[ghost_node_id] = 0;

            while (!q.empty())
            {
                int node_id = q.front();
                q.pop();

                for (int next_id : matrix_adj[node_id])
                {
                    if (dist[next_id] > dist[node_id] + 1)
                    {
                        dist[next_id] = dist[node_id] + 1;
                        q.push(next_id);
                    }
                }
            }

            for (int j = 0; j < humans.size(); j++)
            {
                point human = humans[j];
                int human_node_id = point_to_node_id(human, N);
                if (dist[human_node_id] < INT_MAX)
                {
                    int h = j + ghosts.size();
                    bg_adj[i].push_back(h);
                    bg_adj[h].push_back(i);
                    usable[i][h] = true;
                    all_costs_set.insert(dist[human_node_id]);
                    costs[i][h] = dist[human_node_id];
                    costs[h][i] = dist[human_node_id];
                }
            }
        }

        vector<int> all_costs(all_costs_set.begin(), all_costs_set.end());

        sort(all_costs.begin(), all_costs.end());

        int min_threshold = INT_MAX;
        int a = 0, b = all_costs.size() - 1;
        vector<vector<bool>> usable_base(usable.begin(), usable.end());

        // binary search through all possible costs (bottleneck matchin)
        while (a <= b)
        {
            usable.assign(usable_base.begin(), usable_base.end());
            int k = (a + b) / 2;
            int threshold = all_costs[k];
            int matchings_found = 0;
            bool found_more = false;
            do
            {
                found_more = false;

                queue<int> q;
                vector<int> prev(bg_nodes_count, -1);

                q.push(source);

                while (!q.empty())
                {
                    int node = q.front();
                    q.pop();

                    if (node == sink)
                        break;

                    for (int next : bg_adj[node])
                    {
                        if (usable[node][next] && prev[next] == -1 && costs[node][next] <= threshold)
                        {
                            q.push(next);
                            prev[next] = node;
                        }
                    }
                }

                if (prev[sink] != -1)
                {
                    int node = sink;
                    while (node != source)
                    {
                        int p = prev[node];
                        usable[p][node] = false;
                        usable[node][p] = true;
                        node = p;
                    }
                    matchings_found++;
                    found_more = true;
                }

            } while (found_more);

            if (matchings_found == humans.size())
            {
                b = k - 1;
                min_threshold = min(threshold, min_threshold);
            }
            else
                a = k + 1;
        }

        if (min_threshold == INT_MAX)
            cout << "Case " << t + 1 << ": Vuter Dol Kupokat" << endl;
        else
            cout << "Case " << t + 1 << ": " << min_threshold * 2 + 2 << endl;
    }
}