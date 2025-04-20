#include <atomic>
#include <iostream>
#include <thread>

std::atomic<int> count;

void increment_count() {
  for (int i = 0; i < 200000; i++) {
    count++;
  }
}

int main() { 
    std::thread t1(increment_count);
    std::thread t2(increment_count);

    t1.join();
    t2.join();

    std::cout << "Count = " << count << std::endl;
    return 0; 

}