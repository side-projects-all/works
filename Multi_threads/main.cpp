#include <chrono>
#include <iostream>
#include <thread>
#include "Threadsafe_stack.h"
#include "Unique_lock_swap.h"
#include "Conn_works.h"
#include "Cache_data.h"
#include "Threadsafe_queue.h"
#include <vector>
#include "Async_n_Future.h"
#include "Packaged_task_n_Promise.h"
#include <functional>
#include "Latch_example.h"


int main(int argc, char *argv[]) {

  //std::time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  //std::cout << std::ctime(&t) << '\n';
  Test_latch tl;
  tl.run_jobs();

  //example using std::promise
  /*
  std::promise<int> mp;
  std::future<int> mf = mp.get_future();
  std::thread compute_t(ans_val, std::ref(mp));

  try {
    int ans = mf.get();
    std::cout << "ans: " << ans << "\n";
    
  } catch (const std::exception& e) {
    std::cerr << "Exception is: " << e.what() << "\n";
  }
  */

  /* cool example using std::packaged_task and condition_variable
  std::thread t1(work1);
  std::packaged_task<int()> t(std::bind(factorial, 6));
  std::future<int> fu = t.get_future();

  //using curly parenthesis for lock_guard RAII
  {
    std::lock_guard<std::mutex> locker(m);
    task_dq.push_back(std::move(t));
  }

  cv.notify_one();
  std::cout << "fu: " << fu.get() << "\n";

  t1.join();
  */

  /*
  std::vector<int> v(10000, 1);
  std::cout << "The sum is " << parallel_sum(v.begin(), v.end()) << '\n';

  Async_X asyncX;
  
  std::future<void> a2 = std::async(std::launch::deferred, &Async_X::only_str, &asyncX, "world");
  std::future<int> a3 = std::async(std::launch::async, Async_X(), 43);
  std::future<void> a1 = std::async(&Async_X::show_val, &asyncX, 42, "hello");

  a2.wait();
  std::cout << a3.get() << '\n';
  */

  /*
  Threadsafe_queue<int> tq;
  auto fun = [&tq](int i) {
    tq.push(i);
    std::cout << "pushed: " << i << " \n";
  };

  auto fun_pop = [&tq]() {
    if (!tq.empty()) {
      std::shared_ptr<int> ptr = tq.wait_n_pop();
      std::cout << "poped: " << *ptr << " \n";

    } else {
      std::cout << "empty\n";
    }
  };

  std::vector<std::thread> threads(10);
  std::vector<std::thread> threads_pop(10);

  for (int i = 0; i < 10; ++i) {
    threads[i] = std::thread(fun, i);
  }

  for (int i = 0; i < 10; ++i) {
    threads_pop[i] = std::thread(fun_pop);
  }

  for (int i = 0; i < 10; ++i) {
    threads[i].join();
    threads_pop[i].join();
  }
  */
  
  /*
  Cache_data cd;
  std::thread t1([&cd]() {
    std::string ans = cd.find_entry("abc.com");
    std::cout << "in t1, find abc.com: " << ans << "\n";
  });

  std::thread t2([&cd]() {
    cd.update_entry("gnc.gov.tw", "1.1.1.1");
    std::string ans = cd.find_entry("gnc.gov.tw");

    std::cout << "in t2 complete update, gnc.gov.tw: " << ans << "\n";
  });

  std::thread t3([&cd]() {
    std::string ans = cd.find_entry("gnc.gov.tw");
    std::cout << "in t3 gnc.gov.tw: " << ans << "\n";
  });

  t1.join();
  t2.join();
  t3.join();
  */

  /*
  Conn_works cw(8888);
  std::thread t1([&cw]() {
    cw.receive_data();
  });

  std::thread t2([&cw]() {
    cw.send_data();
  });
  */

  /*
  X xa(15);
  X xb(40);
  std::thread t1([&xa, &xb]() {

    std::cout << "in t1 before swap xa: " << xa.get_val() << " xb: " << xb.get_val() << "\n";
    swap(xa, xb);
    std::cout << "in t1 after swap xa: " << xa.get_val() << " xb: " << xb.get_val() << "\n";
  });

  std::thread t2([&xa, &xb]() {

    std::cout << "in t2 before swap xa: " << xa.get_val() << " xb: " << xb.get_val() << "\n";
    swap(xa, xb);
    std::cout << "in t2 after swap xa: " << xa.get_val() << " xb: " << xb.get_val() << "\n";
  });
  */

  /*
  Threadsafe_stack<int> ts_stack;
  
  std::thread t1([&ts_stack]() {
    
    for (int i = 1; i <= 10; ++i) {
      ts_stack.push(i);
      std::cout << "t1 pushed: " << i << "\n";
    }

  });

  std::thread t2([&ts_stack]() {
    std::shared_ptr<int> ptr;
    while (!ts_stack.empty()) {
      std::shared_ptr<int> ptr = ts_stack.pop();
      std::cout << "t2 poped: " << *ptr << "\n";
    }
  });
  */

  std::cout << "end\n";
  return 0;
}