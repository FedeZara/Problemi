// https://lightoj.com/problem/going-together

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> coord;
typedef tuple<coord, coord, coord> node_triplet;
typedef pair<int, int> qe;

int node_from_coord(int x, int y, int N)
{
    return y * N + x;
}

pair<int, int> coord_from_node(int node, int N)
{
    int x = node % N;
    int y = node / N;
    return {x, y};
}

bool first_lower(const coord &a, const coord &b)
{
    if (a.first < b.first)
        return true;
    if (a.first == b.first)
        return a.second < b.second;
    return false;
}

bool first_greater(const coord &a, const coord &b)
{
    if (a.first > b.first)
        return true;
    if (a.first == b.first)
        return a.second > b.second;
    return false;
}

bool second_lower(const coord &a, const coord &b)
{
    return first_lower({a.second, a.first}, {b.second, b.first});
}

bool second_greater(const coord &a, const coord &b)
{
    return first_greater({a.second, a.first}, {b.second, b.first});
}

node_triplet move(node_triplet node, int dx, int dy, int N, bool (*compare)(const coord &, const coord &), vector<vector<char>> &matrix)
{
    vector<coord> node_pos{get<0>(node), get<1>(node), get<2>(node)};
    sort(node_pos.begin(), node_pos.end(), compare);
    for (int i = 0; i < 3; i++)
    {
        coord pos = node_pos[i];
        pos.first += dx;
        pos.second += dy;

        bool occupied = false;
        for (int j = 0; j < i && !occupied; j++)
            if (node_pos[j] == pos)
                occupied = true;

        if (pos.first < 0 || pos.first >= N | pos.second < 0 || pos.second >= N || matrix[pos.first][pos.second] == '#' || occupied)
        {
            pos.first -= dx;
            pos.second -= dy;
        }
        node_pos[i] = pos;
    }

    sort(node_pos.begin(), node_pos.end());
    return {node_pos[0], node_pos[1], node_pos[2]};
}

void print_node(node_triplet node)
{
    cout << "first: " << get<0>(node).first << " " << get<0>(node).second << endl;
    cout << "second: " << get<1>(node).first << " " << get<1>(node).second << endl;
    cout << "third: " << get<2>(node).first << " " << get<2>(node).second << endl;
}

int main()
{
    int T;
    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int N;
        cin >> N;

        vector<coord> start_pos;
        vector<coord> end_pos;
        vector<vector<char>> matrix(N, vector<char>(N));
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                cin >> matrix[i][j];
                if (matrix[i][j] == 'X')
                {
                    end_pos.push_back({i, j});
                    matrix[i][j] = '.';
                }
                else if (matrix[i][j] == 'A' || matrix[i][j] == 'B' || matrix[i][j] == 'C')
                {
                    start_pos.push_back({i, j});
                    matrix[i][j] = '.';
                }
            }
        }

        sort(start_pos.begin(), start_pos.end());
        sort(end_pos.begin(), end_pos.end());

        node_triplet start = {start_pos[0], start_pos[1], start_pos[2]};
        node_triplet end = {end_pos[0], end_pos[1], end_pos[2]};

        map<node_triplet, int> triplet_to_id;
        vector<node_triplet> id_to_triplet;

        triplet_to_id[start] = 0;
        triplet_to_id[end] = 1;
        id_to_triplet.push_back(start);
        id_to_triplet.push_back(end);

        vector<int> dist{0, INT_MAX};
        vector<bool> processed{false, false};

        priority_queue<qe, vector<qe>, greater<qe>> pq;
        pq.push({0, 0});
        while (!pq.empty())
        {
            qe e = pq.top();
            pq.pop();

            int distance = e.first;
            int node_id = e.second;

            if (node_id == triplet_to_id[end])
                break;

            if (processed[node_id])
                continue;

            processed[node_id] = true;

            node_triplet node = id_to_triplet[node_id];

            // print_node(node);

            node_triplet destinations[] = {
                move(node, -1, 0, N, &first_lower, matrix),
                move(node, +1, 0, N, &first_greater, matrix),
                move(node, 0, -1, N, &second_lower, matrix),
                move(node, 0, +1, N, &second_greater, matrix),
            };

            /*cout << "NORTH:" << endl;
            print_node(destinations[0]);
            cout << "SOUTH:" << endl;
            print_node(destinations[1]);
            cout << "WEST:" << endl;
            print_node(destinations[2]);
            cout << "EAST:" << endl;
            print_node(destinations[3]);*/

            for (node_triplet dest : destinations)
            {
                if (triplet_to_id.find(dest) == triplet_to_id.end())
                {
                    id_to_triplet.push_back(dest);
                    triplet_to_id[dest] = id_to_triplet.size() - 1;
                    dist.push_back(INT_MAX);
                    processed.push_back(false);
                }

                int dest_id = triplet_to_id[dest];
                if (dist[dest_id] > distance + 1)
                {
                    dist[dest_id] = distance + 1;
                    pq.push({dist[dest_id], dest_id});
                }
            }
        }

        if (dist[triplet_to_id[end]] == INT_MAX)
            cout << "Case " << t + 1 << ": trapped" << endl;
        else
            cout << "Case " << t + 1 << ": " << dist[triplet_to_id[end]] << endl;
    }
}