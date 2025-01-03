/*

*/

struct greaterPair {
    template <class T1>
    bool operator() (const std::pair<T1, T1> p1, const std::pair<T1, T1> p2) const { 
        if (p1.first == p2.first) {
            return p1.second < p2.second;
        } else {
            return p1.first < p2.first; 
        }
    }
};

class Solution {
public:
    vector<int> kWeakestRows(vector<vector<int>>& mat, int k) {
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, greaterPair> pq;

        for (int i = 0; i < mat.size(); ++i) {
            int soldiers = binarySearch(mat[i]);
            pq.push(std::make_pair(soldiers, i));

            if (pq.size() > k) {
                pq.pop();
            }

        }

        std::vector<int> result;
        while (pq.size() > 0) {
            result.push_back(pq.top().second);
            pq.pop();
        }

        std::reverse(result.begin(), result.end());
        return result;
    }

private:

    int binarySearch(std::vector<int>& row) {
        int low = 0;
        int high = row.size();

        while (low < high) {
            int mid = low + (high - low) / 2;

            if (row[mid] == 1) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }

        return low;
    }


};