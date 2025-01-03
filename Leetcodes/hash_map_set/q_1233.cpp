/*
Given a list of folders folder, return the folders after removing all sub-folders in those folders. You may return the answer in any order.

If a folder[i] is located within another folder[j], it is called a sub-folder of it. A sub-folder of folder[j] must start with folder[j], followed by a "/". For example, "/a/b" is a sub-folder of "/a", but "/b" is not a sub-folder of "/a/b/c".

The format of a path is one or more concatenated strings of the form: '/' followed by one or more lowercase English letters.

    For example, "/leetcode" and "/leetcode/problems" are valid paths while an empty string and "/" are not.

 

Example 1:

Input: folder = ["/a","/a/b","/c/d","/c/d/e","/c/f"]
Output: ["/a","/c/d","/c/f"]
Explanation: Folders "/a/b" is a subfolder of "/a" and "/c/d/e" is inside of folder "/c/d" in our filesystem.

Example 2:

Input: folder = ["/a","/a/b/c","/a/b/d"]
Output: ["/a"]
Explanation: Folders "/a/b/c" and "/a/b/d" will be removed because they are subfolders of "/a".

Example 3:

Input: folder = ["/a/b/c","/a/b/ca","/a/b/d"]
Output: ["/a/b/c","/a/b/ca","/a/b/d"]

 

Constraints:

    1 <= folder.length <= 4 * 10^4
    2 <= folder[i].length <= 100
    folder[i] contains only lowercase letters and '/'.
    folder[i] always starts with the character '/'.
    Each folder name is unique.


*/

class Solution {
private:
    /*
    struct Node {
        bool is_end;
        std::unordered_map<std::string, Node*> children;
        Node() : is_end{ false } {

        }
    };

    Node* root;

    //prevent memory leak
    void del_trie(Node* node) {
        if (node == nullptr) {
            return;
        }

        for (auto& p : node->children) {
            del_trie(p.second);
        }

        delete node;
    }
    */
public:
    Solution() {

    }
    ~Solution() {
        
    }

    vector<string> removeSubfolders(vector<string>& folder) {
        //return by_trie(folder);
        return by_set(folder);
    }

    std::vector<std::string> by_set(vector<string>& folder) {
        // Create a set to store all folder paths for fast lookup
        std::unordered_set<std::string> set(folder.begin(), folder.end());
        std::vector<std::string> ans;

        // Iterate through each folder to check if it's a sub-folder
        for (std::string& f : folder) {
            bool isSubFolder = false;
            std::string prefix = f;

            // Check all prefixes of the current folder path
            while (!prefix.empty()) {
                size_t pos = prefix.find_last_of('/');
                if (pos == string::npos) break;

                // Reduce the prefix to its parent folder
                prefix = prefix.substr(0, pos);

                // If the parent folder exists in the set, mark as sub-folder
                if (set.count(prefix)) {
                    isSubFolder = true;
                    break;
                }
            }

            // If not a sub-folder, add it to the result
            if (!isSubFolder) {
                ans.push_back(f);
            }
        }

        return ans;
    }
    /*
    vector<string> by_trie(vector<string>& folder) {
        root = new Node();

        for (std::string& path : folder) {
            Node* curr = root;
            std::istringstream iss(path);
            std::string folder_name;

            while (std::getline(iss, folder_name, '/')) {

                if (folder_name.empty()) {
                    continue;
                }

                if (curr->children.find(folder_name) == curr->children.end()) {
                    curr->children[folder_name] = new Node();
                }

                curr = curr->children[folder_name];
            }

            curr->is_end = true;
        }

        std::vector<std::string> ans;
        for (std::string& path : folder) {
            Node* curr = root;
            std::istringstream iss(path);
            std::string folder_name;
            bool is_sub_folder = false;

            while (std::getline(iss, folder_name, '/')) {
                if (folder_name.empty()) {
                    continue;
                }

                Node* next_node = curr->children[folder_name];

                if (next_node->is_end && iss.rdbuf()->in_avail() != 0) {
                    is_sub_folder = true;
                    break;
                }

                curr = next_node;
            }

            if (!is_sub_folder) {
                ans.push_back(path);
            }
        }

        del_trie(root);

        return ans;
    }
    */
};