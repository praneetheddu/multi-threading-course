#include <iostream>
#include <mutex>
#include <thread>

std::mutex mutex;

using namespace std::chrono_literals;

// Unique lock function example
void unique_lock_example(int &value, const int&& n) {

  for (int i = 0; i < n; i++) {
    std::unique_lock<std::mutex> unique_lock(mutex);
    std::cout << "value = " << value << "\n";
    value++;
    unique_lock.unlock();
    std::this_thread::sleep_for(20ms);
  }
}

int main() {
  int value = 0;

  std::thread t1(unique_lock_example, std::ref(value), 30);

  std::thread t2(unique_lock_example, std::ref(value), 10);

  t1.join();
  t2.join();

  return 0;
}