/*
A gene string can be represented by an 8-character long string, with choices from 'A', 'C', 'G', and 'T'.

Suppose we need to investigate a mutation from a gene string startGene to a gene string endGene where one mutation is defined as one single character changed in the gene string.

    For example, "AACCGGTT" --> "AACCGGTA" is one mutation.

There is also a gene bank bank that records all the valid gene mutations. A gene must be in bank to make it a valid gene string.

Given the two gene strings startGene and endGene and the gene bank bank, return the minimum number of mutations needed to mutate from startGene to endGene. If there is no such a mutation, return -1.

Note that the starting point is assumed to be valid, so it might not be included in the bank.

 

Example 1:

Input: startGene = "AACCGGTT", endGene = "AACCGGTA", bank = ["AACCGGTA"]
Output: 1

Example 2:

Input: startGene = "AACCGGTT", endGene = "AAACGGTA", bank = ["AACCGGTA","AACCGCTA","AAACGGTA"]
Output: 2

 

Constraints:

    0 <= bank.length <= 10
    startGene.length == endGene.length == bank[i].length == 8
    startGene, endGene, and bank[i] consist of only the characters ['A', 'C', 'G', 'T']
*/

class Solution {
private:
    int bfs(string& s, string& e, vector<string>& bank) {
        std::queue<std::string> q;
        std::unordered_set<std::string> seen;
        q.push(s);
        seen.insert(s);

        int steps = 0;
        while (!q.empty()) {
            int nodesInQ = q.size();

            for (int n = 0; n < nodesInQ; ++n) {
                std::string node = q.front();
                q.pop();

                if (node == e) {
                    return steps;
                }

                //like four directions
                for (char c : "ACGT") {

                    //iterate all possibility
                    for (int i = 0; i < node.size(); ++i) {
                        std::string neighbor = node;

                        //change one character to neighbor
                        neighbor[i] = c;

                        if (!seen.count(neighbor) && 
                                std::find(bank.begin(), bank.end(), neighbor) != bank.end()) {
                            
                            q.push(neighbor);
                            seen.insert(neighbor);
                        }

                    }
                }
            }

            ++steps;
        }

        return -1;
    }
public:
    int minMutation(string startGene, string endGene, vector<string>& bank) {
        return bfs(startGene, endGene, bank);
    }
};