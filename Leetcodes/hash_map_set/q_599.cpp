/*
Given two arrays of strings list1 and list2, find the common strings with the least index sum.

A common string is a string that appeared in both list1 and list2.

A common string with the least index sum is a common string such that if it appeared at list1[i] and list2[j] then i + j should be the minimum value among all the other common strings.

Return all the common strings with the least index sum. Return the answer in any order.

 

Example 1:

Input: list1 = ["Shogun","Tapioca Express","Burger King","KFC"], list2 = ["Piatti","The Grill at Torrey Pines","Hungry Hunter Steakhouse","Shogun"]
Output: ["Shogun"]
Explanation: The only common string is "Shogun".

Example 2:

Input: list1 = ["Shogun","Tapioca Express","Burger King","KFC"], list2 = ["KFC","Shogun","Burger King"]
Output: ["Shogun"]
Explanation: The common string with the least index sum is "Shogun" with index sum = (0 + 1) = 1.

Example 3:

Input: list1 = ["happy","sad","good"], list2 = ["sad","happy","good"]
Output: ["sad","happy"]
Explanation: There are three common strings:
"happy" with index sum = (0 + 1) = 1.
"sad" with index sum = (1 + 0) = 1.
"good" with index sum = (2 + 2) = 4.
The strings with the least index sum are "sad" and "happy".

 

Constraints:

    1 <= list1.length, list2.length <= 1000
    1 <= list1[i].length, list2[i].length <= 30
    list1[i] and list2[i] consist of spaces ' ' and English letters.
    All the strings of list1 are unique.
    All the strings of list2 are unique.


*/

class Solution {
public:
    vector<string> findRestaurant(vector<string>& list1, vector<string>& list2) {
        std::unordered_map<std::string, std::size_t> my_map;
        std::vector<std::string> shorter;
        std::vector<std::string> result;
        std::size_t len;
        std::size_t min = 2001;     //because of the limit of the question
        
        //make larger one a map
        if (list1.size() > list2.size()) {
            vToM(list1, my_map);
            shorter = list2;
            len = list2.size();
        } else {
            vToM(list2, my_map);
            shorter = list1;
            len = list1.size();
        }
        
        //loop through shorter one to find common strings
        for (std::size_t i = 0; i < len; ++i) {
            
            if (my_map.find(shorter[i]) != my_map.end()) {
                if (min > my_map[shorter[i]] + i) {
                    min = my_map[shorter[i]] + i;
                    
                    result.clear();
                    
                    result.push_back(shorter[i]);
                } else if (min == my_map[shorter[i]] + i) {
                    result.push_back(shorter[i]);
                }
            }
        }
        
        
        return result;
    }
private:
    //vector to map
    void vToM(std::vector<std::string> vec, std::unordered_map<std::string, std::size_t>& map) {
        for (std::size_t i = 0; i < vec.size(); ++i) {
            map.insert(std::make_pair(vec[i], i));
        }
    }
};