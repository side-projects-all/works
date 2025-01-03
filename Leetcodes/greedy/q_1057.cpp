/*
On a campus represented on the X-Y plane, there are n workers and m bikes, with n <= m.

You are given an array workers of length n where workers[i] = [xi, yi] is the position of the ith worker. You are also given an array bikes of length m where bikes[j] = [xj, yj] is the position of the jth bike. All the given positions are unique.

Assign a bike to each worker. Among the available bikes and workers, we choose the (workeri, bikej) pair with the shortest Manhattan distance between each other and assign the bike to that worker.

If there are multiple (workeri, bikej) pairs with the same shortest Manhattan distance, we choose the pair with the smallest worker index. If there are multiple ways to do that, we choose the pair with the smallest bike index. Repeat this process until there are no available workers.

Return an array answer of length n, where answer[i] is the index (0-indexed) of the bike that the ith worker is assigned to.

The Manhattan distance between two points p1 and p2 is Manhattan(p1, p2) = |p1.x - p2.x| + |p1.y - p2.y|.

 

Example 1:

Input: workers = [[0,0],[2,1]], bikes = [[1,2],[3,3]]
Output: [1,0]
Explanation: Worker 1 grabs Bike 0 as they are closest (without ties), and Worker 0 is assigned Bike 1. So the output is [1, 0].

Example 2:

Input: workers = [[0,0],[1,1],[2,0]], bikes = [[1,0],[2,2],[2,1]]
Output: [0,2,1]
Explanation: Worker 0 grabs Bike 0 at first. Worker 1 and Worker 2 share the same distance to Bike 2, thus Worker 1 is assigned to Bike 2, and Worker 2 will take Bike 1. So the output is [0,2,1].

 

Constraints:

    n == workers.length
    m == bikes.length
    1 <= n <= m <= 1000
    workers[i].length == bikes[j].length == 2
    0 <= xi, yi < 1000
    0 <= xj, yj < 1000
    All worker and bike locations are unique.


*/

class Solution {
private:
    std::vector<int> byPriorityQueue(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
        std::vector<std::vector<std::tuple<int, int, int>>> workerToBikesList;
        std::priority_queue<std::tuple<int, int, int>, 
                            std::vector<std::tuple<int, int, int>>, 
                            std::greater<std::tuple<int, int, int>>> pq;

        for (int w = 0; w < workers.size(); ++w) {

            std::vector<std::tuple<int, int, int>> currWorkerTuple;
            for (int b = 0; b < bikes.size(); ++b) {
            
                int distance = manhattanDistance(workers[w][0], workers[w][1], bikes[b][0], bikes[b][1]);
                currWorkerTuple.push_back({distance, w, b});
            }

            std::sort(currWorkerTuple.begin(), 
                        currWorkerTuple.end(), 
                        std::greater<std::tuple<int, int, int>>());

            pq.push(currWorkerTuple.back());
            currWorkerTuple.pop_back();

            workerToBikesList.push_back(currWorkerTuple);
        }

        std::vector<bool> bikeStatus(bikes.size(), false);
        std::vector<int> workerStatus(workers.size(), -1);
        int cnt = 0;

        while (!pq.empty()) {
            auto[dist, worker, bike] = pq.top();
            pq.pop();

            if (!bikeStatus[bike]) {
                bikeStatus[bike] = true;
                workerStatus[worker] = bike;
            } else {
                pq.push(workerToBikesList[worker].back());
                workerToBikesList[worker].pop_back();
            }
        }
            
        return workerStatus;
    }
    std::vector<int> byBucketSort(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
        //2d array for every distance as bucket, with [][0]: worker, [][1]: bike index 
        //based on the constraint of this question
        int minDis = INT_MAX;
        std::vector<std::pair<int, int>> distanceToPair[1999];
        
        for (int w = 0; w < workers.size(); ++w) {
            for (int b = 0; b < bikes.size(); ++b) {
                int distance = manhattanDistance(workers[w][0], workers[w][1], bikes[b][0], bikes[b][1]);
                distanceToPair[distance].push_back({ w, b });
                minDis = std::min(minDis, distance);
            }
        }

        int currDistance = minDis;
        std::vector<bool> bikeStatus(bikes.size(), false);
        std::vector<int> workerStatus(workers.size(), -1);
        int cnt = 0;

        while (cnt != workers.size()) {
            for (auto[worker, bike] : distanceToPair[currDistance]) {
                if (workerStatus[worker] == -1 && !bikeStatus[bike]) {
                    bikeStatus[bike] = true;
                    workerStatus[worker] = bike;
                    ++cnt;
                }
            }

            ++currDistance;
        }

        return workerStatus;
    }

    int manhattanDistance(int x1, int y1, int x2, int y2) {
        return std::abs(x1 - x2) + std::abs(y1 - y2);
    }

    std::vector<int> naive(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
        //2d array, with [][0]: distance, [][1]: worker index for every bike, [][2]: bike index 
        std::vector<std::vector<int>> threeVal;
        

        for (int w = 0; w < workers.size(); ++w) {
            for (int b = 0; b < bikes.size(); ++b) {
                int distance = manhattanDistance(workers[w][0], workers[w][1], bikes[b][0], bikes[b][1]);
                threeVal.push_back({distance, w, b});
            }
        }

        std::sort(threeVal.begin(), threeVal.end());

        std::vector<bool> bikeStatus(bikes.size(), false);
        std::vector<int> workerStatus(workers.size(), -1);
        
        int cnt = 0;
        for (int i = 0; i < threeVal.size(); ++i) {
            int dist = threeVal[i][0];
            int worker = threeVal[i][1];
            int bike = threeVal[i][2];

            if (workerStatus[worker] == -1 && !bikeStatus[bike]) {
                bikeStatus[bike] = true;
                workerStatus[worker] = bike;
                ++cnt;

                if (cnt == workers.size()) {
                    return workerStatus;
                }
            }
        }
        
        return workerStatus;
    }
public:
    vector<int> assignBikes(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
        //return naive(workers, bikes);

        //if we could expect fixed small range, using bucket sort has better performance!
        return byBucketSort(workers, bikes);
        //return byPriorityQueue(workers, bikes);
    }
};