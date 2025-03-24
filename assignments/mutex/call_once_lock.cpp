#include <cstddef>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

class Sample {

public:
  explicit Sample() { std::cout << "Constructing Sample \n"; }

  inline void call_this() { std::cout << " Func called \n"; }
};

Sample *samp1 = NULL;
std::once_flag once_flag;

// Call once function
void init_sample() {
  std::call_once(once_flag, []() {
    std::cout << "Calling the lambda here \n";
    samp1 = new Sample();
    std::cout << "pSamp created here \n";
  });
  samp1->call_this();
}

// Meyers singleton
void myers_singleton() {
  static Sample samp2;
  samp2.call_this();
}

int main() {

  std::vector<std::thread> threads;
  for (int i = 0; i < 10; i++) {
    threads.push_back(std::thread(myers_singleton));
  }

  for (auto &thr : threads) {
    thr.join();
  }
}