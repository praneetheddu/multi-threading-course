#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

std::string shared{};
std::mutex m{};
std::condition_variable cond;

using namespace std::chrono_literals;

// Readinfg the
void read() {

  std::cout << "Calling Read thrread \n";
  std::unique_lock<std::mutex> uniq(m);
  std::cout << "Waiting for write thread to compelete ..\n";
  cond.wait(uniq);
  std::cout << "Unlocked 😎!, Reading ...\n";
  std::cout << "Shared string = " << shared << std::endl;
}

void write() {

  std::this_thread::sleep_for(1ms);

  std::cout << "Calling Write...\n";
  {
    std::lock_guard<std::mutex> lock(m);
    std::this_thread::sleep_for(100ms);
    shared = "Finished";
    std::cout << "Shared resouce = " << shared << std::endl;
  }
  cond.notify_one();

  std::cout << "Unlocking Shared Resouce  ...\n";
}

int main() {

  std::thread t1(read);
  std::thread t2(write);

  t1.join();
  t2.join();
}