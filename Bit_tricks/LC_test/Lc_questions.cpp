#include "Lc_questions.h"

struct Comparator {
    bool operator() (const std::pair<int, int>& lhs, const std::pair<int, int>& rhs) const {
        if (lhs.first == rhs.first) {
            return lhs.second < rhs.second;
        }
        return lhs.first < rhs.first;
    }
};

std::vector<int> Lc_questions::q(std::vector<int>& nums, int k, int x) {
    int n = nums.size();
    std::vector<int> ans(n - k + 1);
    std::unordered_map<int, int> m;
    
    for (int i = 0; i < k; ++i) {
        ++m[nums[i]];
    }
    
    
    for (int i = 0; i < n - k + 1; ++i) {
        
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, Comparator> pq;
        if (i > 0) {
            int prev = nums[i - 1];
            --m[prev];
            if (m[prev] == 0) {
                m.erase(prev);
            }
            ++m[nums[i + k - 1]];
        }
        
        for (const auto& p : m) {
            pq.push({p.second, p.first});
        }
        
        if (pq.size() < x) {
            while (!pq.empty()) {
                ans[i] += pq.top().first * pq.top().second;
                pq.pop();
            }
            
        } else {
            while (pq.size() >= x) {
                ans[i] += pq.top().first * pq.top().second;
                pq.pop();
            }
        }
    }
    
    return ans;
}

