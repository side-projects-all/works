#include <iostream>
#include <vector>
#include <array>

class Solution {
private:
    
public:
    Solution() {}
    ~Solution() {}

    void sol() {
        std::ios::sync_with_stdio(false);
        std::cin.tie(nullptr);

        int t; 
        if (!(std::cin >> t)) return;
        while (t--) {
            int n; 
            std::cin >> n;
            std::vector<int> a(n);
            for (int i = 0; i < n; ++i) std::cin >> a[i];

            std::array<int, 101> freq{}; 
            bool ok = false;
            for (int x : a) {
                if (++freq[x] >= 2) { ok = true; break; }
            }

            std::cout << (ok ? "YES\n" : "NO\n");
        }
    }
};