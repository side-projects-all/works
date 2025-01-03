class Solution {
public:
    int countPrimes(int n) {
        if (n <= 2) {
            return 0;
        }

        std::vector<bool> numbers(n);
        int sqrt = std::sqrt(n);
        for (int p = 2; p <= sqrt; ++p) {
            if (numbers[p] == false) {
                for (int index = p * p; index < n; index += p) {
                    numbers[j] = true;
                }
            }
        }

        int numOfPrimes = 0;
        for (int i = 2; i < n; ++i) {
            if (numbers[i] == false) {
                ++numOfPrimes;
            }
        }

        return numOfPrimes;
    }
};