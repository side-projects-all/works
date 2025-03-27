/*
You have information about n different recipes. You are given a string array recipes and a 2D string array ingredients. The ith recipe has the name recipes[i], and you can create it if you have all the needed ingredients from ingredients[i]. A recipe can also be an ingredient for other recipes, i.e., ingredients[i] may contain a string that is in recipes.

You are also given a string array supplies containing all the ingredients that you initially have, and you have an infinite supply of all of them.

Return a list of all the recipes that you can create. You may return the answer in any order.

Note that two recipes may contain each other in their ingredients.

 

Example 1:

Input: recipes = ["bread"], ingredients = [["yeast","flour"]], supplies = ["yeast","flour","corn"]
Output: ["bread"]
Explanation:
We can create "bread" since we have the ingredients "yeast" and "flour".

Example 2:

Input: recipes = ["bread","sandwich"], ingredients = [["yeast","flour"],["bread","meat"]], supplies = ["yeast","flour","meat"]
Output: ["bread","sandwich"]
Explanation:
We can create "bread" since we have the ingredients "yeast" and "flour".
We can create "sandwich" since we have the ingredient "meat" and can create the ingredient "bread".

Example 3:

Input: recipes = ["bread","sandwich","burger"], ingredients = [["yeast","flour"],["bread","meat"],["sandwich","meat","bread"]], supplies = ["yeast","flour","meat"]
Output: ["bread","sandwich","burger"]
Explanation:
We can create "bread" since we have the ingredients "yeast" and "flour".
We can create "sandwich" since we have the ingredient "meat" and can create the ingredient "bread".
We can create "burger" since we have the ingredient "meat" and can create the ingredients "bread" and "sandwich".

 

Constraints:

    n == recipes.length == ingredients.length
    1 <= n <= 100
    1 <= ingredients[i].length, supplies.length <= 100
    1 <= recipes[i].length, ingredients[i][j].length, supplies[k].length <= 10
    recipes[i], ingredients[i][j], and supplies[k] consist only of lowercase English letters.
    All the values of recipes and supplies combined are unique.
    Each ingredients[i] does not contain any duplicate values.


*/

class Solution {
private:
    vector<string> by_topological_sort(vector<string>& recipes, vector<vector<string>>& ingredients, vector<string>& supplies) {
        int rn = recipes.size();
        std::unordered_set<std::string> supplies_set{supplies.begin(), supplies.end()};

        std::unordered_map<std::string, int> rcp_i;
        //ingredient to recipes that need it
        std::unordered_map<std::string, std::vector<std::string>> ingr_to_rcp;

        //recipe to index mapping
        for (int i = 0; i < rn; ++i) {
            rcp_i[recipes[i]] = i;
        }

        //count of non-supply ingredients needed for each recipe
        vector<int> in_degree(rn);

        //build dependency graph
        for (int i = 0; i < rn; i++) {
            for (std::string& ingr : ingredients[i]) {

                if (supplies_set.find(ingr) == supplies_set.end()) {
                    //edge: ingredient -> recipe
                    ingr_to_rcp[ingr].push_back(recipes[i]);
                    ++in_degree[i];
                }
            }
        }

        //start with recipes that only need supplies
        std::queue<int> q;
        for (int i = 0; i < rn; ++i) {
            if (in_degree[i] == 0) {
                q.push(i);
            }
        }

        //process recipes in topological order
        std::vector<std::string> ans;
        while (!q.empty()) {

            int i = q.front();
            q.pop();
            std::string recipe = recipes[i];
            ans.push_back(recipe);

            //skip if no other recipes depend on curr recipe
            if (ingr_to_rcp.find(recipe) == ingr_to_rcp.end()) {
                continue;
            }

            //update recipes that depend on current recipe
            for (std::string& rcp : ingr_to_rcp[recipe]) {

                --in_degree[rcp_i[rcp]];
                if (in_degree[rcp_i[rcp]] == 0) {

                    q.push(rcp_i[rcp]);
                }
            }
        }

        return ans;
    }
public:
    vector<string> findAllRecipes(vector<string>& recipes, vector<vector<string>>& ingredients, vector<string>& supplies) {
        return by_topological_sort(recipes, ingredients, supplies);
    }
};