/*
Winter is coming! During the contest, your first job is to design a standard heater with a fixed warm radius to warm all the houses.

Every house can be warmed, as long as the house is within the heater's warm radius range. 

Given the positions of houses and heaters on a horizontal line, return the minimum radius standard of heaters so that those heaters could cover all houses.

Notice that all the heaters follow your radius standard, and the warm radius will the same.

 

Example 1:

Input: houses = [1,2,3], heaters = [2]
Output: 1
Explanation: The only heater was placed in the position 2, and if we use the radius 1 standard, then all the houses can be warmed.

Example 2:

Input: houses = [1,2,3,4], heaters = [1,4]
Output: 1
Explanation: The two heaters were placed at positions 1 and 4. We need to use a radius 1 standard, then all the houses can be warmed.

Example 3:

Input: houses = [1,5], heaters = [2]
Output: 3

 

Constraints:

    1 <= houses.length, heaters.length <= 3 * 10^4
    1 <= houses[i], heaters[i] <= 10^9


*/

class Solution {
public:
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        std::sort(houses.begin(), houses.end());
        std::sort(heaters.begin(), heaters.end());
        
        int min_r = 0;
        
        //find the closest heater for each house
        for (int h : houses) {
            // Find the closest heater using binary search
            int i = std::lower_bound(heaters.begin(), heaters.end(), h) - heaters.begin();
            
            // Calculate distance to the nearest left heater
            int left_heater_dist = (i == 0) ? INT_MAX : std::abs(h - heaters[i - 1]);
            
            // Calculate distance to the nearest right heater
            int right_heater_dist = (i == heaters.size()) ? INT_MAX : std::abs(h - heaters[i]);
            
            // Find the minimum distance for this house
            int min_dis = std::min(left_heater_dist, right_heater_dist);
            
            // Update the radius to cover the farthest house
            min_r = std::max(min_r, min_dis);
        }
        
        return min_r;
    }
};