#include <chrono>
#include <iostream>
#include <thread>

inline void sample() { std::cout << "Hello from sample! \n"; }

void sleep_in_thread() {

  std::this_thread::sleep_for(std::chrono::seconds(5));
  std::cout << "Slept for 5 seconds \n";
}

int main() {

  std::thread thr(sample);
  std::cout << "Native handle : " << thr.native_handle() << std::endl;
  std::cout << thr.get_id() << std::endl;
  thr.join();

  std::cout << std::this_thread::get_id() << std::endl;

  std::thread thr2(sleep_in_thread);
  thr2.join();
  return 0;
}