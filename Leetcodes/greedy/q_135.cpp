/*
There are n children standing in a line. Each child is assigned a rating value given in the integer array ratings.

You are giving candies to these children subjected to the following requirements:

    Each child must have at least one candy.
    Children with a higher rating get more candies than their neighbors.

Return the minimum number of candies you need to have to distribute the candies to the children.

 

Example 1:

Input: ratings = [1,0,2]
Output: 5
Explanation: You can allocate to the first, second and third child with 2, 1, 2 candies respectively.

Example 2:

Input: ratings = [1,2,2]
Output: 4
Explanation: You can allocate to the first, second and third child with 1, 2, 1 candies respectively.
The third child gets 1 candy because it satisfies the above two conditions.

 

Constraints:

    n == ratings.length
    1 <= n <= 2 * 10^4
    0 <= ratings[i] <= 2 * 10^4


*/

class Solution {
private:
    int by_greedy_one_array(vector<int>& ratings) {
        int n = ratings.size();
        if (n == 1) {
            return 1;
        }

        std::vector<int> candies(n, 1);
        int sum = 0;

        //left to right
        for (int i = 1; i < n; ++i) {

            if (ratings[i] > ratings[i - 1]) {
                candies[i] = candies[i - 1] + 1;
            }
        }

        sum += candies[n - 1];
        //right to left 
        for (int i = n - 2; i >= 0; --i) {
            if (ratings[i] > ratings[i + 1]) {
                candies[i] = std::max(candies[i], candies[i + 1] + 1);
            }

            sum += candies[i];
        }

        return sum;
    }
    int by_greedy_two_array(vector<int>& ratings) {
        int n = ratings.size();
        if (n == 1) {
            return 1;
        }

        std::vector<int> left_to_right(n, 1);
        std::vector<int> right_to_left(n, 1);

        //left to right
        for (int i = 1; i < n; ++i) {

            if (ratings[i] > ratings[i - 1]) {
                left_to_right[i] = left_to_right[i - 1] + 1;
            }
        }
        //right to left 
        for (int i = n - 2; i >= 0; --i) {
            if (ratings[i] > ratings[i + 1]) {
                right_to_left[i] = right_to_left[i + 1] + 1;
            }
        }

        int sum = 0;
        //get max
        for (int i = 0; i < n; ++i) {
            sum += std::max(left_to_right[i], right_to_left[i]);
        }

        return sum;
    }
public:
    int candy(vector<int>& ratings) {
        //return by_greedy_two_array(ratings);
        return by_greedy_one_array(ratings);
    }
};