#include <atomic>
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

std::mutex writer_mutex;
std::condition_variable cv;

std::vector<std::string> messages{};
std::atomic<int> count = 0;
std::atomic<bool> stop_flag{false};

using namespace std::chrono_literals;

void writer() {
  while (!stop_flag) {
    {
      std::lock_guard<std::mutex> lock(writer_mutex);
      messages.push_back("message " + std::to_string(count.load()) + ", ");
      count++;
    }
    std::this_thread::sleep_for(100ms);
    cv.notify_one();
  }
}

void logger() {
  // Log every 10 messages or 2 seconds

  while (!stop_flag) {
    std::unique_lock<std::mutex> u_lock(writer_mutex);
    cv.wait_for(u_lock, 2s, [&] { return messages.size() >= 10 || stop_flag; });
    if (!messages.empty()) {
      for (const auto &msg : messages) {
        std::cout << msg;
      }
      messages.clear();
      std::cout << std::endl;
    } 
  }
}

int main() {
  std::vector<std::thread> writer_threads;
  for (int i = 0; i < 10; i++) {
    writer_threads.emplace_back(writer);
  }

  std::thread log_thread(logger);

  std::this_thread::sleep_for(5s);
  stop_flag.store(true);
  cv.notify_all();

  for (auto &thr : writer_threads) {
    thr.join();
  }
  log_thread.join();

  return 0;
}