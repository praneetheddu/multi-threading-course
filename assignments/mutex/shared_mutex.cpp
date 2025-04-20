#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <vector>

std::shared_mutex shmut;
using namespace std::chrono_literals;

void read_thread(const int &val) {

  std::this_thread::sleep_for(100ms);
  std::shared_lock<std::shared_mutex> lck(shmut);
  std::cout << "val = " << val << "\n";
  std::this_thread::sleep_for(2000ms);


}

void write_thread(int &val) {
  std::lock_guard<std::shared_mutex> lck(shmut);
  std::this_thread::sleep_for(5000ms);
  val++;

}

int main() {

  int val = 0;

  std::vector<std::thread> threads;
  threads.push_back(std::thread(write_thread, std::ref(val)));
  threads.push_back(std::thread(write_thread, std::ref(val)));

  for (int i = 0; i < 20; i++) {

    threads.push_back(std::thread(read_thread, std::ref(val)));
  }

  threads.push_back(std::thread(write_thread, std::ref(val)));
  threads.push_back(std::thread(write_thread, std::ref(val)));

  for (int i = 0; i < 20; i++) {

    threads.push_back(std::thread(read_thread, std::ref(val)));
  }

  for (auto& thr: threads) {
    thr.join();
  }

}
