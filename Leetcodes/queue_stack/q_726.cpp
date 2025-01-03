/*
Given a string formula representing a chemical formula, return the count of each atom.

The atomic element always starts with an uppercase character, then zero or more lowercase letters, representing the name.

One or more digits representing that element's count may follow if the count is greater than 1. If the count is 1, no digits will follow.

    For example, "H2O" and "H2O2" are possible, but "H1O2" is impossible.

Two formulas are concatenated together to produce another formula.

    For example, "H2O2He3Mg4" is also a formula.

A formula placed in parentheses, and a count (optionally added) is also a formula.

    For example, "(H2O2)" and "(H2O2)3" are formulas.

Return the count of all elements as a string in the following form: the first name (in sorted order), followed by its count (if that count is more than 1), followed by the second name (in sorted order), followed by its count (if that count is more than 1), and so on.

The test cases are generated so that all the values in the output fit in a 32-bit integer.

 

Example 1:

Input: formula = "H2O"
Output: "H2O"
Explanation: The count of elements are {'H': 2, 'O': 1}.

Example 2:

Input: formula = "Mg(OH)2"
Output: "H2MgO2"
Explanation: The count of elements are {'H': 2, 'Mg': 1, 'O': 2}.

Example 3:

Input: formula = "K4(ON(SO3)2)2"
Output: "K4N2O14S4"
Explanation: The count of elements are {'K': 4, 'N': 2, 'O': 14, 'S': 4}.

 

Constraints:

    1 <= formula.length <= 1000
    formula consists of English letters, digits, '(', and ')'.
    formula is always valid.


*/

class Solution {
private:
    int index = 0;

    unordered_map<std::string, int> parse_formula(std::string& formula) {
        std::unordered_map<std::string, int> curr_map;
        std::string curr_atom;
        std::string curr_count;

        while (index < formula.size()) {

            if (std::isupper(formula[index])) {
                //UPPER CASE

                if (!curr_atom.empty()) {
                    if (curr_count.empty()) {
                        curr_map[curr_atom] += 1;

                    } else {
                        curr_map[curr_atom] += std::stoi(curr_count);
                    }
                }    
                
                curr_atom = formula[index];
                curr_count = "";
                ++index;

            } else if (std::islower(formula[index])) {
                //LOWER CASE
                curr_atom += formula[index];
                ++index;

            } else if (std::isdigit(formula[index])) {
                //digit
                curr_count += formula[index];
                ++index;

            } else if (formula[index] == '(') {
                //left parenthesis
                ++index;
                unordered_map<std::string, int> inner_map = parse_formula(formula);
                for (auto& [atom, cnt] : inner_map) {
                    curr_map[atom] += cnt;
                }

            } else if (formula[index] == ')') {
                //right parenthesis
                if (!curr_atom.empty()) {

                    if (curr_count.empty()) {
                        curr_map[curr_atom] += 1;

                    } else {
                        curr_map[curr_atom] += std::stoi(curr_count);
                    }
                }

                ++index;
                std::string times;
                while (index < formula.size() && std::isdigit(formula[index])) {
                    times += formula[index];
                    ++index;
                }

                if (!times.empty()) {
                    int multi = std::stoi(times);

                    for (auto& [atom, cnt] : curr_map) {
                        curr_map[atom] = cnt * multi;
                    }
                }

                return curr_map;
            }
        }

        if (!curr_atom.empty()) {
            if (curr_count.empty()) {
                curr_map[curr_atom] += 1;

            } else {
                curr_map[curr_atom] += std::stoi(curr_count);
            }
        }

        return curr_map;
    }
public:
    string countOfAtoms(string formula) {
        std::unordered_map<std::string, int> final_map = parse_formula(formula);

        std::map<std::string, int> sorted_map(final_map.begin(), final_map.end());

        std::string ans;
        for (auto& [atom, cnt] : sorted_map) {
            ans += atom;

            if (cnt > 1) {
                ans += std::to_string(cnt);
            }
        }

        return ans;
    }
};