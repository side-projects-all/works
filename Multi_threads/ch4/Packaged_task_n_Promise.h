#include <iostream>
#include <deque>
#include <future>

int factorial(int n) {
  int ans = 1;
  for (int i = n; i > 1; --i) {
    ans *= i;
  }

  std::cout << "ans is: " << ans << "\n";
  return ans;
}

std::deque<std::packaged_task<int()>> task_dq;
std::mutex m;
std::condition_variable cv;

void work1() {
  std::packaged_task<int()> t;
  {
    std::unique_lock<std::mutex> lock(m);
    cv.wait(lock, []() {
      return !task_dq.empty();
    });

    t = std::move(task_dq.front());
    task_dq.pop_front();
  }

  t();
}

void ans_val(std::promise<int>& ans) {
  try {
    ans.set_value(9199944);
  } catch (...) {
    ans.set_exception(std::current_exception());
  }
}
