// https://lightoj.com/problem/gone-fishing
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;
    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int N, H;
        cin >> N;
        cin >> H;

        vector<int> fishingInLake(N);
        vector<int> deltaFishingInLake(N);
        vector<int> timeToTravel(N - 1);

        for (int i = 0; i < N; i++)
        {
            cin >> fishingInLake[i];
        }

        for (int i = 0; i < N; i++)
        {
            cin >> deltaFishingInLake[i];
        }

        for (int i = 0; i < N - 1; i++)
        {
            cin >> timeToTravel[i];
        }

        vector<vector<int>> fishingPerTime(N);

        for (int i = 0; i < N; i++)
        {
            fishingPerTime[i].push_back(0);
            for (int time = 1, currentFishing = fishingInLake[i]; time <= H * 12; time++, currentFishing -= deltaFishingInLake[i])
            {
                fishingPerTime[i].push_back(fishingPerTime[i][time - 1] + max(currentFishing, 0));
            }
        }

        vector<vector<pair<int, int>>> results(N);

        for (int h = 0; h <= H * 12; h++)
        {
            results[N - 1].push_back({fishingPerTime[N - 1][h], h});
        }

        for (int n = N - 2; n >= 0; n--)
        {
            for (int h = 0; h <= H * 12; h++)
            {
                pair<int, int> max = {fishingPerTime[n][h], h};
                for (int t = h - timeToTravel[n]; t >= 0; t--)
                {
                    pair<int, int> val = {fishingPerTime[n][t] + results[n + 1][h - t - timeToTravel[n]].first, t};
                    if (val > max)
                        max = val;
                }
                results[n].push_back(max);
            }
        }

        cout << "Case " << (t + 1) << ":" << endl;

        int remainingTime = H * 12;
        for (int i = 0; i < N - 1; i++)
        {
            if (remainingTime == 0)
            {
                cout << "0, ";
            }
            else
            {
                cout << results[i][remainingTime].second * 5 << ", ";
                remainingTime -= results[i][remainingTime].second;
                if (remainingTime > 0)
                    remainingTime -= timeToTravel[i];
            }
        }

        cout << remainingTime * 5 << endl;

        cout << "Number of fish expected: " << results[0][H * 12].first << endl;
    }
}