/*

*/

#include <cctype>

class Solution {
public:
    string validIPAddress(string queryIP) {
        //return by_regex(queryIP);
        
        return by_str_compare(queryIP);
    }

private:
    std::string by_str_compare(string& query) {

        if (query.find('.') != string::npos) {  //ipv4 check

            // Check for leading/trailing dots
            if (query.front() == '.' || query.back() == '.') {
                return "Neither";
            }

            std::istringstream ss(query);
            std::string word;
            int cnt = 0;
            while (std::getline(ss, word, '.')) {

                ++cnt;
                // Check if the segment is non-empty and contains only digits
                //::isdigit from <cctype>
                if (word.empty() || word.size() > 3 || !std::all_of(word.begin(), word.end(), ::isdigit)) {
                    return "Neither";
                }
                // Check if the segment is valid (between 0 and 255) and does not have leading zeros
                if (word[0] == '0' && word.size() > 1) {
                    return "Neither"; // Leading zeros are not allowed
                }

                int num = std::stoi(word);
                if (num < 0 || num > 255) {
                    return "Neither";
                }
            }
            // IPv4 must have exactly 4 segments
            if (cnt != 4) {
                return "Neither";
            }

            return "IPv4";

        } else if (query.find(':') != string::npos) { //ipv6 check
            // Check for leading/trailing colons
            if (query.front() == ':' || query.back() == ':') {
                return "Neither";
            }

            std::istringstream ss(query);
            std::string word;
            int cnt = 0;
            while (std::getline(ss, word, ':')) {

                ++cnt;
                // Each segment must be 1 to 4 hex digits
                if (word.empty() || word.size() > 4) {
                    return "Neither";
                }
                // Check if the segment contains only valid hexadecimal characters
                for (char c : word) {
                    if (!std::isxdigit(c)) {
                        return "Neither";
                    }
                }
            }
            // IPv6 must have exactly 8 segments
            if (cnt != 8) {
                return "Neither";
            } 
            return "IPv6";
        }

        // If neither IPv4 nor IPv6 conditions are met
        return "Neither";
    }
    
    std::string by_regex(string& queryIP) {
        // create regex object for regulare expression
        std::regex ipv4("(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])");
        std::regex ipv6("((([0-9a-fA-F]){1,4})\\:){7}([0-9a-fA-F]){1,4}");

        // match regex expression IPv4
        if(std::regex_match(queryIP, ipv4)) {
            return "IPv4";
        }

        // match regex expression IPv6
        if(std::regex_match(queryIP, ipv6)) {
            return "IPv6";
        }
            
        return "Neither";
    }
};