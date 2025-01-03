/*
Given a list of accounts where each element accounts[i] is a list of strings, where the first element accounts[i][0] is a name, and the rest of the elements are emails representing emails of the account.

Now, we would like to merge these accounts. Two accounts definitely belong to the same person if there is some common email to both accounts. Note that even if two accounts have the same name, they may belong to different people as people could have the same name. A person can have any number of accounts initially, but all of their accounts definitely have the same name.

After merging the accounts, return the accounts in the following format: the first element of each account is the name, and the rest of the elements are emails in sorted order. The accounts themselves can be returned in any order.

 

Example 1:

Input: accounts = [["John","johnsmith@mail.com","john_newyork@mail.com"],["John","johnsmith@mail.com","john00@mail.com"],["Mary","mary@mail.com"],["John","johnnybravo@mail.com"]]
Output: [["John","john00@mail.com","john_newyork@mail.com","johnsmith@mail.com"],["Mary","mary@mail.com"],["John","johnnybravo@mail.com"]]
Explanation:
The first and second John's are the same person as they have the common email "johnsmith@mail.com".
The third John and Mary are different people as none of their email addresses are used by other accounts.
We could return these lists in any order, for example the answer [['Mary', 'mary@mail.com'], ['John', 'johnnybravo@mail.com'], 
['John', 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com']] would still be accepted.

Example 2:

Input: accounts = [["Gabe","Gabe0@m.co","Gabe3@m.co","Gabe1@m.co"],["Kevin","Kevin3@m.co","Kevin5@m.co","Kevin0@m.co"],["Ethan","Ethan5@m.co","Ethan4@m.co","Ethan0@m.co"],["Hanzo","Hanzo3@m.co","Hanzo1@m.co","Hanzo0@m.co"],["Fern","Fern5@m.co","Fern1@m.co","Fern0@m.co"]]
Output: [["Ethan","Ethan0@m.co","Ethan4@m.co","Ethan5@m.co"],["Gabe","Gabe0@m.co","Gabe1@m.co","Gabe3@m.co"],["Hanzo","Hanzo0@m.co","Hanzo1@m.co","Hanzo3@m.co"],["Kevin","Kevin0@m.co","Kevin3@m.co","Kevin5@m.co"],["Fern","Fern0@m.co","Fern1@m.co","Fern5@m.co"]]

 

Constraints:

    1 <= accounts.length <= 1000
    2 <= accounts[i].length <= 10
    1 <= accounts[i][j].length <= 30
    accounts[i][0] consists of English letters.
    accounts[i][j] (for j > 0) is a valid email.


*/

class Solution {
private:
    int findRepresentative(int x, std::vector<int>& representative) {
        if (x == representative[x]) {
            return x;
        }

        //path compression
        return representative[x] = findRepresentative(representative[x], representative);
    }

    void unionBySize(int a, int b, std::vector<int>& size, std::vector<int>& representative) {
        int representativeA = findRepresentative(a, representative);
        int representativeB = findRepresentative(b, representative);

        if (representativeA == representativeB) {
            return;
        }

        if (size[representativeA] >= size[representativeB]) {

            size[representativeA] += size[representativeB];
            representative[representativeB] = representativeA;

        } else {

            size[representativeB] += size[representativeA];
            representative[representativeA] = representativeB;
        }
    }

    vector<vector<string>> byDSU(vector<vector<string>>& accounts) {
        int N = accounts.size();

        std::vector<int> representative(N, 0);
        std::iota(representative.begin(), representative.end(), 0);
        std::vector<int> size(N, 1);

        std::unordered_map<std::string, int> mailGroup;

        for (int i = 0; i < accounts.size(); ++i) {
            int n = accounts[i].size();

            for (int j = 1; j < n; ++j) {
                std::string mail = accounts[i][j];
                std::string name = accounts[i][0];

                if (mailGroup.find(mail) == mailGroup.end()) {
                    mailGroup[mail] = i;
                } else {
                    unionBySize(i, mailGroup[mail], size, representative);
                }
            }
        }

        std::unordered_map<int, std::vector<std::string>> components;
        for (auto& p : mailGroup) {
            std::string mail = p.first;
            int group = p.second;

            components[findRepresentative(group, representative)].push_back(mail);
        }

        std::vector<std::vector<std::string>> result;
        for (auto& p : components) {
            int group = p.first;
            std::vector<std::string> component = { accounts[group][0] };
            component.insert(component.end(), p.second.begin(), p.second.end());

            std::sort(component.begin() + 1, component.end());
            result.push_back(component);
        }

        return result;
    }
    
    void dfs(std::unordered_map<std::string, std::vector<std::string>>& adj, 
                                    std::unordered_set<std::string>& visited, 
                                        std::vector<std::string>& relatedMails, std::string& mail) {

        visited.insert(mail);
        relatedMails.push_back(mail);

        for (std::string& neighbor : adj[mail]) {
            if (visited.find(neighbor) == visited.end()) {
                dfs(adj, visited, relatedMails, neighbor);
            }
        }
    }

    vector<vector<string>> byDfs(vector<vector<string>>& accounts) {
        int N = accounts.size();

        std::unordered_set<std::string> visited;
        std::unordered_map<std::string, std::vector<std::string>> adj;
        
        //create adjacent list
        for (std::vector<std::string>& a : accounts) {
            int n = a.size();

            std::string firstMail = a[1];
            for (int j = 2; j < n; ++j) {

                std::string mail = a[j];
                adj[firstMail].push_back(mail);
                adj[mail].push_back(firstMail);
            }
        }

        std::vector<std::vector<std::string>> result;
        for (std::vector<std::string>& a : accounts) {
            std::string name = a[0];
            std::string firstMail = a[1];

            if (visited.find(firstMail) == visited.end()) {
                std::vector<std::string> relatedMails;
                relatedMails.push_back(name);

                dfs(adj, visited, relatedMails, firstMail);

                std::sort(relatedMails.begin() + 1, relatedMails.end());
                result.push_back(relatedMails);
            }
        }

        return result;
    }

public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        //return byDfs(accounts);

        //by union find
        return byDSU(accounts);
    }
};