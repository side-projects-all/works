#include <functional>
#include <iostream>
#include <latch>
#include <string>
#include <thread>

struct Job {
  const std::string name;
  std::string product{ "not worked" };
  std::thread action{};
};

class Test_latch {
private:
public:
  Test_latch() {

  }

  void run_jobs() {
    Job jobs[]{ {"Annika"}, {"Buru"}, {"Chuck"} };
    std::latch work_done{std::size(jobs)};
    std::latch start_clean_up{1};

    auto work = [&](Job& job_now) {
      job_now.product = job_now.name + " worked";

      work_done.count_down();
      //the thread with work function will be blocked here!
      start_clean_up.wait();  

      job_now.product = job_now.name + " cleaned";
    };

    std::cout << "Work is starting...\n";

    for (auto& job : jobs) {
      job.action = std::thread{work, std::ref(job)};
    }

    work_done.wait();
    std::cout << "done: \n";

    for (const auto& job : jobs) {
      std::cout << " " << job.product << '\n';
    }

    std::cout << "workers are cleaning up...";
    start_clean_up.count_down();

    for (auto& job : jobs) {
      job.action.join();
    }

    std::cout << "done\n";
    for (const auto& job : jobs) {
      std::cout << " " << job.product << '\n';
    }
  }
};
