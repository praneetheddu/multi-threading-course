#include <iostream>
#include <mutex>
#include <random>
#include <thread>

thread_local std::mt19937 mt;
std::mutex mutex;

void generate_rands() {

  {
    std::lock_guard<std::mutex> lock(mutex);
    std::uniform_real_distribution<float> randos;
    for (int i = 0; i < 5; i++) {
      std::cout << randos(mt) << ", ";
    }
  }

  std::cout << "\nMT addr = " << &mt << std::endl;
  std::cout << std::endl;
}

int main() {

  std::thread t1(generate_rands);

  std::thread t2(generate_rands);

  t1.join();
  t2.join();

  return 0;
}