#include "MathFuncs.h"

int MathFuncs::gcd_re(int a, int b) {
  if (a == 0) {
    return b;
  }

  if (b == 0) {
    return a;
  }

  if (a == b) {
    return a;
  }

  if (a < 0) {
    a = -a;
  }

  if (b < 0) {
    b = -b;
  }
  return gcd_re(b, a % b);
}

int MathFuncs::lcm_re(int a, int b) {
  if (a < 0) {
    a = -a;
  }

  if (b < 0) {
    b = -b;
  }

  return a * b / gcd_re(a, b);
}

int MathFuncs::gcd_it(int a, int b) {
  if (a == 0) {
    return b;
  }

  if (b == 0) {
    return a;
  }

  if (a < 0) {
    a = -a;
  }

  if (b < 0) {
    b = -b;
  }
  int r = 0;
  do {
    r = a % b;
    a = b;
    b = r;

  } while (b != 0);

  return a;
}

int MathFuncs::lcm_it(int a, int b) {
  if (a < 0) {
    a = -a;
  }

  if (b < 0) {
    b = -b;
  }
  
  return a * b / gcd_it(a, b);
}

bool MathFuncs::only_has_3_factors(int val) {
  int sqrt = static_cast<int>(std::sqrt(val));

  return (sqrt * sqrt == val) && (is_prime(sqrt));
}

bool MathFuncs::is_prime(int val) {
  return by_Sieve_of_Eratosthenes(val);
  //return by_divisible_factors(val);
}
bool MathFuncs::by_Sieve_of_Eratosthenes(int val) {
  std::vector<bool> primes(val * 2, true);
  primes[0] = false;
  primes[1] = false;

  for (int i = 2; i * i <= val * 2; ++i) {

    if (primes[i]) {
      for (int j = i * i; j < val * 2; j += i) {
        primes[j] = false;
      }
    }
  }

  return primes[val];
}
bool MathFuncs::by_divisible_factors(int val) {
  if (val <= 1) {
    return false;
  }

  if (val <= 3) {
    return true;
  }

  if (val % 2 || val % 3) {
    return false;
  }

  for (int i = 5; i * i <= val; i += 6) {
    if (val % i == 0 || val % (i + 2) == 0) {
      return false;
    }
  }

  return true;
}