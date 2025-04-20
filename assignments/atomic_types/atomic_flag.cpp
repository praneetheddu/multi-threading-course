#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

std::atomic_flag a_flag = ATOMIC_FLAG_INIT;

void print_atomic_flag_value() {

  if (a_flag.test_and_set()) {
    std::cout << "a_flag is set to true \n";
  } else {
    std::cout << "a_flag is set to false \n";
  }
}

int main() {
  print_atomic_flag_value();
  a_flag.test_and_set();
  print_atomic_flag_value();
  a_flag.clear();
  print_atomic_flag_value();

  return 0;
}