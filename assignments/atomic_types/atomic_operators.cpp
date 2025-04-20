#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

// store() Atomically replace the object's value with its argument

// load() Atomically return the object's value

// exchange() Atomically replace the object's value and return the previous
// value

std::atomic<int> my_val{0};

std::vector<std::atomic<int>> vals;

void increment_val() {
    my_val = 5;

    std::cout << "My val = " << my_val << "\n";

    my_val.store(7);

    std::cout << "My val after store = " << my_val << "\n";

    std::cout << "My val after load = " << my_val.load() << "\n";

  for (int i = 0; i < 100'000; i++) {
    my_val.fetch_add(1);
    // my_val++;
  }
}

std::vector<int> get_my_val() {
  std::vector<int> some_vec;

  for (const auto &val : vals) {
    some_vec.push_back(val);
  }

  return some_vec;
}

int main() {

  std::vector<std::thread> threads{};

  for (int i = 0; i < 5; i++) {
    threads.push_back(std::thread{increment_val});
  }

  for (auto &thr : threads) {
    thr.join();
  }

  // std::cout << "value of my_val = " << get_my_val() << std::endl;

  return 0;
}