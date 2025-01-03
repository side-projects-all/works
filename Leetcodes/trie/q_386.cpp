/*
Given an integer n, return all the numbers in the range [1, n] sorted in lexicographical order.

You must write an algorithm that runs in O(n) time and uses O(1) extra space. 

 

Example 1:

Input: n = 13
Output: [1,10,11,12,13,2,3,4,5,6,7,8,9]

Example 2:

Input: n = 2
Output: [1,2]

 

Constraints:

    1 <= n <= 5 * 10^4
*/

class Solution {
private:
    vector<int> better(int n) {
        std::vector<int> ans(n);

        int num = 1;
        for(int i = 0; i < n; i++) {
            ans[i] = num;
            if(num * 10 <= n) {
                num *= 10;
            }
            else {
                while(num + 1 > n || num % 10 == 9) {
                    num /= 10;
                }
                ++num;
            }
        }

        return ans;
    }
    vector<int> naive(int n) {
        std::vector<int> ans(n);
        int k = 0;
        std::generate(ans.begin(), ans.end(), [&]() {
            return ++k;
        });

        std::sort(ans.begin(), ans.end(), [](int v1, int v2) {
            return std::to_string(v1) < std::to_string(v2);
        });

        return ans;
    }
public:
    vector<int> lexicalOrder(int n) {
        //return naive(n);
        return better(n);
    }
};


