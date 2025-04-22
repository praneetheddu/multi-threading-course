#include <algorithm>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

std::mutex mut;
std::condition_variable cv;
bool is_ready{false};
std::queue<int> queue;

void producer(int val) {
  {
    std::lock_guard<std::mutex> lock(mut);
    queue.push(val);
    is_ready = true;
  }
  cv.notify_one();
}

void consumer() {

  std::unique_lock<std::mutex> lock(mut);
  cv.wait(lock, [] { return is_ready; });
  queue.pop();
}