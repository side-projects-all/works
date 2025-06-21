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
private:
    void dfs(const std::string& b, std::unordered_map<std::string, std::deque<std::string>>& adj, std::vector<std::string>& ans) {

        while (!adj[b].empty()) {
            std::string e = adj[b].front();
            adj[b].pop_front();

            dfs(e, adj, ans);
        }

        ans.push_back(b);
    }
    vector<string> by_dfs(vector<vector<string>>& tickets) {

        std::unordered_map<std::string, std::deque<std::string>> adj;
        for (const std::vector<std::string>& t : tickets) {
            adj[t[0]].push_back(t[1]);
        }

        for (auto& [src, dest] : adj) {
            std::sort(dest.begin(), dest.end());
        }

        std::vector<std::string> ans;
        dfs("JFK", adj, ans);
        std::reverse(ans.begin(), ans.end());

        return ans;
    }
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        return by_dfs(tickets);
    }
};