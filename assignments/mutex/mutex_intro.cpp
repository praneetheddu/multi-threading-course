#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std::chrono_literals;
std::mutex mutex;

// Function with mutex lock and unlock
void mutex_func(const char *str, int size) {
  mutex.lock();
  for (int i = 0; i < size; i++) {
    std::cout << str[i];
  }
  std::cout << std::endl;
  mutex.unlock();
}

// Functions with try lock example to show waiting to unlock mutex
std::mutex mutex_2;

void task_1() {
  std::cout << "Locking the mutex \n";
  mutex_2.lock();
  std::cout << "Sleeping for 4 seconds ... \n";
  std::this_thread::sleep_for(4s);
  mutex_2.unlock();
}

void task_2() {

  std::this_thread::sleep_for(100ms);
  while (!mutex_2.try_lock()) {
    std::this_thread::sleep_for(500ms);
    std::cout << "Cannot acquire mutex lock, sleeping ...\n";
  }
  std::cout << "lock acquired, now we release ! \n";
  mutex_2.unlock();
}

int main() {

  std::thread t1(mutex_func, "abc", 3);

  std::thread t2(mutex_func, "def", 3);

  std::thread t3(mutex_func, "ghi", 3);

  t1.join();
  t2.join();
  t3.join();

  // Try lock example
  std::thread task1_thr(task_1);
  std::thread task2_thr(task_2);

  task1_thr.join();
  task2_thr.join();

  return 0;
}