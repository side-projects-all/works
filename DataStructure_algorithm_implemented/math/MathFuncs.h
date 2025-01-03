#include <vector>
#include <cmath>

class MathFuncs {
private:
  bool by_Sieve_of_Eratosthenes(int val);
  bool by_divisible_factors(int val);

public:
  MathFuncs() {

  }

  ~MathFuncs() {

  }

  int gcd_it(int a, int b);  //gcd_iterative
  int gcd_re(int a, int b);  //gcd_recursive
  int lcm_it(int a, int b);  //lcm_iterative
  int lcm_re(int a, int b);  //lcm_recursive
  bool is_prime(int val);
  bool only_has_3_factors(int val);
};