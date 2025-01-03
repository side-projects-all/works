/*
You are given an integer array arr. Sort the integers in the array in ascending order by the number of 1's in their binary representation and in case of two or more integers have the same number of 1's you have to sort them in ascending order.

Return the array after sorting it.

 

Example 1:

Input: arr = [0,1,2,3,4,5,6,7,8]
Output: [0,1,2,4,8,3,5,6,7]
Explantion: [0] is the only integer with 0 bits.
[1,2,4,8] all have 1 bit.
[3,5,6] have 2 bits.
[7] has 3 bits.
The sorted array by bits is [0,1,2,4,8,3,5,6,7]

Example 2:

Input: arr = [1024,512,256,128,64,32,16,8,4,2,1]
Output: [1,2,4,8,16,32,64,128,256,512,1024]
Explantion: All integers have 1 bit in the binary representation, you should just sort them in ascending order.

 

Constraints:

    1 <= arr.length <= 500
    0 <= arr[i] <= 10^4


*/

class Solution {
private:
    static bool p_compare(const int& a, const int& b) {
        int c1 = __builtin_popcount(a);
        int c2 = __builtin_popcount(b);

        if (c1 == c2) {
            return a < b;
        }

        return c1 < c2;
    }
    /*
    int count_1s(int num) {
        int count = 0;
        int and_r = 0;
        while (num > 0) {
            and_r = num & 1;
            if (and_r == 1) {
                count += 1;
            }

            num = num >> 1;
        }

        return count;
    }*/
public:
    vector<int> sortByBits(vector<int>& arr) {

        //another way using __builtin_popcount !!!!
        std::sort(arr.begin(), arr.end(), p_compare);

        return arr;
        /*
        std::unordered_map<int, std::vector<int>> c;
        std::vector<int> result;
        int nums = 0;

        for (auto i : arr) {
            nums = count_1s(i);

            if (c.find(nums) != c.end()) {
                c[nums].push_back(i);
            } else {
                c.insert(std::make_pair(nums, std::vector<int>()));
                c[nums].push_back(i);
            }
        }

        std::vector<int> keys;
        for (auto p : c) {
            keys.push_back(p.first);
        }
        std::sort(keys.begin(), keys.end());

        int len = keys.size();
        int key = 0;
        for (int m = 0; m < len; ++m) {
            key = keys[m];
            std::sort(c[key].begin(), c[key].end());

            for (int k = 0; k < c[key].size(); ++k) {
                result.push_back(c[key][k]);
            }
        }
        
        return result;
        */

    }
};