/*

*/

class Solution {
private:
    bool is_strobo(string& s) {
        for (int i = 0, j = s.size() - 1; i <= j; ++i, --j) {
            if ((s[i] == '6' && s[j] == '9') || 
                (s[i] == '9' && s[j] == '6') || 
                (s[i] == '0' && s[j] == '0') || 
                (s[i] == '1' && s[j] == '1') || 
                (s[i] == '8' && s[j] == '8')) {

                continue;

            } else {
                return false;
            }
        }

        return true;
    }

    int recursive_cnt(int len, std::vector<std::string>& rotate, int target_len) {
        if (len == 0) {
            return 1;
        }

        if (len == 1) {
            return 3;
        }

        int prev_len_cnt = recursive_cnt(len - 2, rotate, target_len);
        int curr_len_cnt = 0;
        for (int i = 0; i < rotate.size(); ++i) {
            if (rotate[i][0] != '0' || len != target_len) {
                curr_len_cnt += prev_len_cnt;
            }
        }

        return curr_len_cnt;
    }

    std::vector<std::string> recursive_vec(int len, std::vector<std::string>& rotate, int target_len, 
                                                                            long long low, long long high) {
        if (len == 0) {
            return { "" };
        }

        if (len == 1) {
            return { "0", "1", "8" };
        }

        std::vector<std::string> prev = recursive_vec(len - 2, rotate, target_len, low, high);
        std::vector<std::string> curr;
        for (int j = 0; j < prev.size(); ++j) {
            for (int i = 0; i < rotate.size(); ++i) {
                if (rotate[i][0] != '0' || len != target_len) {

                    std::string str = rotate[i][0] + prev[j] + rotate[i][1];
                    long long val = std::stol(str);
                    if (str.size() < target_len || (str.size() == target_len && val >= low && val <= high)) {
                        curr.push_back(str);
                    } 
                    
                }
            }
        }
        
        return curr;
    }

    vector<string> iterative(int n, std::vector<std::string>& revisible, int targetLen, 
                                                                    long long low, long long high) {
        std::queue<std::string> q;
        int curr_len = 0;

        if (n % 2 == 0) {
            curr_len = 0;
            q.push("");
        } else {
            curr_len = 1;
            q.push("0");
            q.push("1");
            q.push("8");
        }

        while (curr_len < n) {
            curr_len += 2;

            for (int i = q.size(); i > 0; --i) {
                std::string num = q.front();
                q.pop();

                for (std::string& r : revisible) {
                    if (curr_len != n || r[0] != '0') {

                        std::string str = r[0]  + num + r[1];
                        long long val = std::stol(str);
                        if (str.size() < targetLen || (str.size() == targetLen && val >= low && val <= high)) {
                            q.push(str);
                        }
                    }
                }
            }
        }

        std::vector<std::string> ans;
        while (!q.empty()) {
            ans.push_back(q.front());
            q.pop();
        }

        return ans;
    }
public:
    int strobogrammaticInRange(string low, string high) {
        
        std::vector<std::string> rotate{ "00", "11", "88", "69", "96" };
        long long low_val = std::stol(low);
        int low_len = low.size();
        long long high_val = std::stol(high);
        int high_len = high.size();

        std::vector<std::string> low_cnt;
        std::vector<std::string> high_cnt;

        //corner case
        if (high_len == 1) {
            int cnt = 0;
            for (std::string s : { "0", "1", "8" } ) {

                if (s >= low && s <= high) {
                    ++cnt;
                }
            }

            return cnt;
        }

        //corner case
        if (low_len == 1) {
            for (std::string s : { "0", "1", "8" } ) {

                if (s >= low) {
                    low_cnt.push_back(s);
                }
            }
        } else {
            //low_cnt = recursive_vec(low_len, rotate, low_len, low_val, high_val);

            low_cnt = iterative(low_len, rotate, low_len, low_val, high_val);
        }

        //corner case
        if (low_len == high_len) {
            return low_cnt.size();
        }

        //high_cnt = recursive_vec(high_len, rotate, high_len, low_val, high_val);
        high_cnt = iterative(high_len, rotate, high_len, low_val, high_val);

        int between_cnt = 0;

        for (int len = low_len + 1; len < high_len; ++len) {
            between_cnt += recursive_cnt(len, rotate, len);
        }
        
        return low_cnt.size() + between_cnt + high_cnt.size();
    }
};