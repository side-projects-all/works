/*

*/

class Solution {
private:
    /*
    int minDis = 100001;
    int visited[10];    //this means bike used
    */
    int distance(std::vector<int>& worker, std::vector<int>& bike) {
        return std::abs(worker[0] - bike[0]) + std::abs(worker[1] - bike[1]);
    }

    int countOnes(int mask) {
        int cnt = 0;
        while (mask != 0) {
            mask &= (mask - 1);
            ++cnt;
        }

        return cnt;
    }
    int iterative(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
        int mem[1024];
        for (int i = 0; i < 1024; ++i) {
            mem[i] = 100001;
        }
        
        mem[0] = 0;

        int minDis = 100001;
        int w_len = workers.size();
        int b_len = bikes.size();

        for (int mask = 0; mask < (1 << b_len); ++mask) {
            int nextWorker = countOnes(mask);

            if (nextWorker >= w_len) {
                minDis = std::min(minDis, mem[mask]);
                continue;
            }

            for (int b = 0; b < b_len; ++b) {

                if ((mask & (1 << b)) == 0) {
                    int nextMask = (mask | (1 << b));

                    mem[nextMask] = std::min(mem[nextMask], mem[mask] + 
                                                distance(workers[nextWorker], bikes[b]));
                }
            }
        }

        return minDis;
    }
    /*
    int mem[1024] = { -1 };
    int recursive(vector<vector<int>>& workers, vector<vector<int>>& bikes, int worker, int mask) {
        if (worker >= workers.size()) {
            return 0;
        }

        if (mem[mask] != -1) {
            return mem[mask];
        }

        int miniDis = 100001;
        for (int b = 0; b < bikes.size(); ++b) {

            // 1 << b means which bike!! we have 10 bikes at most
            if ((mask & (1 << b)) == 0) {

                int dis = distance(workers[worker], bikes[b]);
                int nextMask = (mask | (1 << b));
                miniDis = std::min(miniDis, dis + recursive(workers, bikes, worker + 1, nextMask));
            }
        }

        return mem[mask] = miniDis;
    }
    
    void backtracking(vector<vector<int>>& workers, vector<vector<int>>& bikes, int worker, int currDisSum) {
        if (worker >= workers.size()) {
            minDis = std::min(minDis, currDisSum);
            return;
        }

        //this part save time for more backtracking
        if (currDisSum >= minDis) {
            return;
        }

        for (int b = 0; b < bikes.size(); ++b) {
            if (!visited[b]) {
                visited[b] = true;  //this makes backtracking works!!

                int workerBikeDis = distance(workers[worker], bikes[b]);
                backtracking(workers, bikes, worker + 1, currDisSum + workerBikeDis);

                visited[b] = false;
            }
        }
    }
    */
public:
    int assignBikes(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
        
        //backtracking(workers, bikes, 0, 0);
        //return minDis;

        //memset(mem, -1, sizeof(mem));
        //return recursive(workers, bikes, 0, 0);

        return iterative(workers, bikes);
    }
};