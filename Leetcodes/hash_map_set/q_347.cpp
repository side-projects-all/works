/*
Given an integer array nums and an integer k, return the k most frequent elements. You may return the answer in any order.

 

Example 1:

Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]

Example 2:

Input: nums = [1], k = 1
Output: [1]

 

Constraints:

    1 <= nums.length <= 10^5
    -10^4 <= nums[i] <= 10^4
    k is in the range [1, the number of unique elements in the array].
    It is guaranteed that the answer is unique.

 

Follow up: Your algorithm's time complexity must be better than O(n log n), where n is the array's size.

*/

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {


        //return my_old_solution(nums, k);
        //return using_pq(nums, k);
        return using_bucketSort(nums, k);
    }

private:
    std::vector<int> using_bucketSort(std::vector<int>& nums, int k) {
        if (nums.size() == 1 || nums.size() <= k) {
            return nums;
        }

        std::unordered_map<int, int> freq_map;

        for (auto num : nums) {
            freq_map[num] += 1;
        }

        int max = 0;
        int min = std::numeric_limits<int>::max();

        for (auto it : freq_map) {
            max = std::max(max, it.second);
            min = std::min(min, it.second);
        }

        int bucketNum = max + 1;    //plus 1 because we started from zero index
        std::vector<std::vector<int>> buckets(bucketNum, std::vector<int>());

        for (auto it : freq_map) {

            buckets[it.second].push_back(it.first);
        }

        std::vector<int> result;
        int count = 0;
        for (int i = buckets.size() - 1; i > -1 ; --i) {
            for (int p = 0; p < buckets[i].size(); ++p) {
                if (count == k) {
                    break;
                }

                result.push_back(buckets[i][p]);
                ++count;
            }
        }
        
        return result;
    }

    std::vector<int> using_pq(std::vector<int>& nums, int k) {
        if (k == nums.size()) {
            return nums;
        }

        std::unordered_map<int, int> mem;
        for (auto n : nums) {
            mem[n] += 1;
        }

        auto comp = [&mem](int n1, int n2) { return mem[n1] > mem[n2]; };
        std::priority_queue<int, std::vector<int>, decltype(comp)> heap(comp);

        for (std::pair<int, int> p : mem) {
            heap.push(p.first);

            if (heap.size() > k) {
                heap.pop();
            }
        }

        std::vector<int> result(k);
        for (int i = k - 1; i >= 0; --i ) {
            result[i] = heap.top();
            heap.pop();
        }

        return result;
    }

    std::vector<int> my_old_solution(std::vector<int>& nums, int k) {
        //my old solution 
        std::unordered_map<int, int> store;
        std::unordered_map<int, std::vector<int>> reverse;
        std::vector<int> frequency;
        std::vector<int> res;
        
        //calculate frequency
        for (auto i : nums) {
            store[i]++;
        }
        
        //use frquency as key, index as value
        //also collect all frequency
        for (auto i : store) {
            
            if (reverse.find(i.second) == reverse.end()) {
                reverse[i.second] = std::vector<int>();
            }
            reverse[i.second].push_back(i.first);
            frequency.push_back(i.second);
        }
        
        //sort the list of frequency in descended way
        std::sort(frequency.begin(), frequency.end(), std::greater<int>());
        
        int freq = 0;
        
        for (int i = 0; i < k;) {
            freq = frequency[i];
            for (auto j : reverse[freq]) {
                res.push_back(j);
                ++i;
            }
        }
        
        return res;
    }
};