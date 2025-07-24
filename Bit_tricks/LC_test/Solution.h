#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

class Solution {
private:
public:
    Solution() {}
    ~Solution() {}

    bool checkDivisibility(int n) {
        int sum = 0;
        int prod = 1;
        int tmp = n;
        while (tmp > 0) {
            int v = tmp % 10;
            sum += v;
            prod *= v;
            tmp /= 10;
        }

        return n % (sum + prod);
    }
    
};