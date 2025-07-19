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
    vector<string> by_sort(vector<string>& folder) {
        std::sort(folder.begin(), folder.end());

        std::vector<std::string> ans;
        ans.push_back(folder[0]);

        for (int i = 1; i < folder.size(); ++i) {
            std::string last_folder = ans.back();
            last_folder += '/';

            if (folder[i].compare(0, last_folder.size(), last_folder) != 0) {
                ans.push_back(folder[i]);
            }
        }
        return ans;
    }
    vector<string> by_set(vector<string>& folder) {
        int n = folder.size();
        if (n == 1) {
            return {folder[0]};
        }

        std::unordered_set<std::string> set{folder.begin(), folder.end()};
        std::vector<std::string> ans;
        for (std::string& s : folder) {
            
            std::string prefix = s;
            bool not_sub = true;
            while (!prefix.empty()) {
                int pos = prefix.find_last_of('/');
                if (pos == std::string::npos) {
                    break;
                }

                prefix = prefix.substr(0, pos);

                if (set.count(prefix)) {
                    not_sub = false;
                    break;
                }
            }

            if (not_sub) {
                ans.push_back(s);
            }
        }

        return ans;
    }
public:
    vector<string> removeSubfolders(vector<string>& folder) {
        return by_sort(folder);
        //return by_set(folder);
    }
};