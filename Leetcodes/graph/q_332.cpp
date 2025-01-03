/*
You are given a list of airline tickets where tickets[i] = [fromi, toi] represent the departure and the arrival airports of one flight. Reconstruct the itinerary in order and return it.

All of the tickets belong to a man who departs from "JFK", thus, the itinerary must begin with "JFK". If there are multiple valid itineraries, you should return the itinerary that has the smallest lexical order when read as a single string.

    For example, the itinerary ["JFK", "LGA"] has a smaller lexical order than ["JFK", "LGB"].

You may assume all tickets form at least one valid itinerary. You must use all the tickets once and only once.

 

Example 1:

Input: tickets = [["MUC","LHR"],["JFK","MUC"],["SFO","SJC"],["LHR","SFO"]]
Output: ["JFK","MUC","LHR","SFO","SJC"]

Example 2:

Input: tickets = [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
Output: ["JFK","ATL","JFK","SFO","ATL","SFO"]
Explanation: Another possible reconstruction is ["JFK","SFO","ATL","JFK","ATL","SFO"] but it is larger in lexical order.

 

Constraints:

    1 <= tickets.length <= 300
    tickets[i].length == 2
    fromi.length == 3
    toi.length == 3
    fromi and toi consist of uppercase English letters.
    fromi != toi


*/


class Solution {
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        //flight_size = 0;


        //build the graph, and make it sorted
        for (auto entry : tickets) {
            std::string origin = entry[0];
            std::string dest = entry[1];

            if (flights.find(origin) != flights.end()) {
                flights[origin].push_back(dest);
                //sort here
                std::sort(flights[origin].begin(), flights[origin].end());

            } else {
                std::vector<std::string> destList = std::vector<std::string>();
                destList.push_back(dest);
                flights[origin] = destList;
            }
        }
        

        applyHierholzerAlgorithm("JFK");
        
        
        
        
        //initialize the visited
        /*
        for (auto entry : flights) {
            std::size_t len = entry.second.size();
            std::string key = entry.first;
            visited.insert(std::make_pair(key, std::vector<bool>(len, false)));
        }
        flight_size = tickets.size();
        std::vector<std::string> route;
        route.push_back("JFK");

        backtracking("JFK", route);
        */
        
        return result;

    }

private:
    
    std::unordered_map<std::string, std::vector<std::string>> flights;
    std::vector<std::string> result;
    
    void applyHierholzerAlgorithm(std::string origin) {

        if (flights.find(origin) != flights.end()) {
          

          while(!flights[origin].empty()) {
            std::string nextTo = flights[origin][0];
            flights[origin].erase(flights[origin].begin());

            applyHierholzerAlgorithm(nextTo);
          }
        }

        result.insert(result.begin(), origin);
    }
    

    /*
    std::unordered_map<std::string, std::vector<bool>> visited;
    std::size_t flight_size;
    
    bool backtracking(std::string origin, std::vector<std::string> route) {
        if (route.size() == flight_size + 1) {
            result = route;
            return true;
        }

        if (flights.find(origin) == flights.end()) {
            return false;
        }

        std::vector<std::string> destinations = flights[origin];
        for (int i = 0; i < destinations.size(); ++i) {

            if (!visited[origin][i]) {

                visited[origin][i] = true;
                std::string startFrom = destinations[i];
                route.push_back(startFrom);

                bool rtnResult = backtracking(startFrom, route);
                route.pop_back();
                visited[origin][i] = false;

                if (rtnResult)
                    return true;

            }
        }

        return false;
    }
    */

};